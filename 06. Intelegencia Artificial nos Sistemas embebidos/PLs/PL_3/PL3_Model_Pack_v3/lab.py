#!/usr/bin/env python3
"""PL3 student tools. Run with Python, NumPy and ai-edge-litert; no TensorFlow.

All paths resolve relative to this file, so the current directory is irrelevant.
Use --help or COMMAND --help. Results are never silently overwritten.
"""
import argparse
import csv
import hashlib
import importlib.metadata
import json
import os
import platform
import statistics
import subprocess
import sys
import time
import zipfile
from pathlib import Path
import numpy as np
from ai_edge_litert.interpreter import Interpreter

BASE = Path(__file__).resolve().parent
GROUPS = {
    'width':['d1w32_fp32','d1w64_fp32','d1w128_fp32'],
    'depth':['d1w64_fp32','d2w64_fp32','d3w64_fp32'],
    'architecture':['d1w32_fp32','d1w64_fp32','d1w128_fp32','d2w64_fp32','d3w64_fp32'],
    'formats':['d1w64_fp32','d1w64_fp16','d1w64_int8'],
}

def read_json(path):
    return json.loads(Path(path).read_text())

def manifest():
    return read_json(BASE/'manifest.json')

def sha(path):
    h=hashlib.sha256()
    with Path(path).open('rb') as f:
        for block in iter(lambda:f.read(1024*1024),b''):h.update(block)
    return h.hexdigest()

def model_record(model_id):
    for item in manifest()['models']:
        if item['id']==model_id:return item
    raise ValueError(f'Unknown model {model_id}. Run: python lab.py catalog')

def checked_model(model_id):
    item=model_record(model_id); path=BASE/item['file']
    if sha(path)!=item['sha256']:raise ValueError(f'Model hash mismatch: {path.name}')
    return item,path

def get_models(value):
    result=GROUPS.get(value, [m['id'] for m in manifest()['models']] if value=='all' else value.split(','))
    if len(result)!=len(set(result)):raise ValueError('Duplicate model IDs')
    for model_id in result:model_record(model_id)
    return result

def load_data():
    x=np.load(BASE/'data/test_images.npy',mmap_mode='r',allow_pickle=False)
    y=np.load(BASE/'data/test_labels.npy',mmap_mode='r',allow_pickle=False)
    if x.shape!=(10000,28,28) or x.dtype!=np.uint8:raise ValueError('Unexpected image dataset')
    if y.shape!=(10000,) or y.dtype!=np.uint8:raise ValueError('Unexpected label dataset')
    return x,y

def tensor_info(t):
    return {'shape':t['shape'].tolist(),'dtype':np.dtype(t['dtype']).name,
            'scale':float(t['quantization'][0]),'zero_point':int(t['quantization'][1])}

def create_runtime(model_id,threads=1):
    item,path=checked_model(model_id)
    runtime=Interpreter(model_path=str(path),num_threads=threads)
    runtime.allocate_tensors()
    ins,outs=runtime.get_input_details(),runtime.get_output_details()
    if len(ins)!=1 or len(outs)!=1:raise ValueError('Expected exactly one input and one output')
    inp,out=ins[0],outs[0]
    for t,key in [(inp,'input'),(out,'output')]:
        if tensor_info(t)!=item[key]:raise ValueError(f'{model_id}: {key} contract differs from manifest')
    return runtime,inp,out

def encode(raw, inp):
    """Raw uint8 image -> normalized batch -> optional integer encoding."""
    if raw.shape!=(28,28) or raw.dtype!=np.uint8:raise ValueError('Expected one raw uint8 28x28 image')
    real=raw[None].astype(np.float32)/255.0
    if np.issubdtype(inp['dtype'],np.integer):
        scale,zero=inp['quantization']
        if scale<=0:raise ValueError('Invalid input scale')
        bounds=np.iinfo(inp['dtype'])
        return np.clip(np.rint(real/scale)+zero,bounds.min,bounds.max).astype(inp['dtype'])
    return real.astype(inp['dtype'])

def decode(raw, out):
    if np.issubdtype(out['dtype'],np.integer):
        scale,zero=out['quantization']
        if scale<=0:raise ValueError('Invalid output scale')
        return (raw.astype(np.float32)-zero)*scale
    return raw.astype(np.float32)

def run_one(runtime,inp,out,raw):
    runtime.set_tensor(inp['index'],encode(raw,inp))
    runtime.invoke()
    scores=decode(runtime.get_tensor(out['index'])[0],out)
    if not np.isfinite(scores).all():raise ValueError('Non-finite output')
    return scores

def environment():
    model_file=Path('/proc/device-tree/model')
    info={'platform':platform.platform(),'machine':platform.machine(),
          'hostname':platform.node(),'python':sys.version.split()[0],
          'numpy':np.__version__,'ai_edge_litert':importlib.metadata.version('ai-edge-litert'),
          'board':model_file.read_text().strip('\x00') if model_file.exists() else 'not identified as Raspberry Pi',
          'cpu_count':os.cpu_count(),'backend':'CPU, default LiteRT delegates; runtime chooses eligible kernels'}
    return info

def device_state():
    result={'temperature_c':None,'throttled':None}
    p=Path('/sys/class/thermal/thermal_zone0/temp')
    try:result['temperature_c']=float(p.read_text())/1000.0
    except (OSError,ValueError):pass
    try:
        r=subprocess.run(['vcgencmd','get_throttled'],capture_output=True,text=True,timeout=3)
        if r.returncode==0:result['throttled']=r.stdout.strip()
    except (OSError,subprocess.TimeoutExpired):pass
    return result

def memory_mib():
    # Read current and high-water RSS from the same Linux status snapshot.
    # Mixing /proc VmRSS with getrusage ru_maxrss can yield inconsistent counters.
    values={}
    for line in Path('/proc/self/status').read_text().splitlines():
        if line.startswith(('VmRSS:','VmHWM:')):
            values[line.split(':',1)[0]]=int(line.split()[1])/1024.0
    if set(values)!={'VmRSS','VmHWM'}:raise ValueError('Linux RSS counters are unavailable')
    return values

def write_json(path,data):
    with Path(path).open('x') as f:json.dump(data,f,indent=2);f.write('\n')

def save_csv(path,rows,fields):
    with Path(path).open('x',newline='') as f:
        w=csv.DictWriter(f,fieldnames=fields,extrasaction='ignore');w.writeheader();w.writerows(rows)

def result_dir(name):
    if not name or not all(c.isalnum() or c in '_-' for c in name):
        raise ValueError('Run name may contain only letters, numbers, underscore and hyphen')
    path=BASE/'results'/name
    path.mkdir(parents=True,exist_ok=False)
    return path

def check(args):
    m=manifest();x,y=load_data()
    if int(y.min())<0 or int(y.max())>9:raise ValueError('Invalid class labels')
    for filename,expected in m['data']['files'].items():
        if sha(BASE/filename)!=expected:raise ValueError(f'Data hash mismatch: {filename}')
    checks=[]
    for item in m['models']:
        rt,inp,out=create_runtime(item['id'])
        scores=np.asarray([run_one(rt,inp,out,x[j]) for j in range(10)])
        reference=np.asarray(item['reference_scores_first_10'])
        diff=float(np.max(np.abs(scores-reference)))
        disagreements=int(np.sum(scores.argmax(1)!=reference.argmax(1)))
        # Quantized kernels may differ by small rounding amounts across platforms.
        tol=1e-4 if item['format']!='int8' else 2*item['output']['scale']+1e-6
        status='PASS' if diff<=tol else 'REVIEW'
        checks.append({'id':item['id'],'max_score_difference':diff,
                       'class_disagreements_first_10':disagreements,'tolerance':tol,'status':status})
        print(item['id'],status,f'max score difference={diff:.7g}, changed classes={disagreements}')
    report={'environment':environment(),'data_hashes':'PASS','model_hashes_and_contracts':'PASS','reference_comparison':checks}
    print(json.dumps(report,indent=2))
    if args.output:write_json(args.output,report)
    if any(c['status']!='PASS' for c in checks):raise ValueError('Reference scores need review before benchmarking')

def catalog(args):
    print('ID                 depth width parameters Dense_MACs file_KiB')
    for m in manifest()['models']:
        print(f"{m['id']:19} {m['depth']:5} {m['width']:5} {m['parameters']:10} {m['dense_macs']:10} {m['file_bytes']/1024:8.2f}")
    print('Depth counts hidden Dense layers. MAC count excludes activation and data movement.')

def inspect(args):
    m,path=checked_model(args.model);rt,inp,out=create_runtime(args.model,args.threads)
    print(json.dumps({'id':m['id'],'file':str(path),'bytes':path.stat().st_size,'sha256':m['sha256'],
                      'input':tensor_info(inp),'output':tensor_info(out)},indent=2))

def predict(args):
    if not 0<=args.index<10000:raise ValueError('Index must be in 0..9999')
    x,y=load_data();rt,inp,out=create_runtime(args.model,args.threads)
    raw=encode(x[args.index],inp);scores=run_one(rt,inp,out,x[args.index])
    labels=manifest()['labels'];top=np.argsort(-scores,kind='stable')[:3]
    print(f'Image index {args.index}; true class {int(y[args.index])}: {labels[int(y[args.index])]}')
    print('Input shape',raw.shape,'dtype',raw.dtype,'range',raw.min(),raw.max())
    print('Top 3 (score is not a guarantee of correctness):')
    for j in top:print(int(j),labels[j],f'{scores[j]:.6f}')

def evaluate(args):
    if not 1<=args.limit<=10000:raise ValueError('Limit must be in 1..10000')
    ids=get_models(args.models); folder=result_dir(args.run);x,y=load_data()
    rows=[]
    for model_id in ids:
        rt,inp,out=create_runtime(model_id,args.threads)
        scores=np.asarray([run_one(rt,inp,out,x[j]) for j in range(args.limit)])
        pred=scores.argmax(1);cm=np.zeros((10,10),dtype=int)
        np.add.at(cm,(y[:args.limit],pred),1)
        record={'id':model_id,'examples':args.limit,'correct':int(np.sum(pred==y[:args.limit])),
                'accuracy_pct':float(np.mean(pred==y[:args.limit])*100),
                'reference_changed_classes':int(np.sum(pred[:min(args.limit,500)]!=np.asarray(model_record(model_id)['reference_classes_500'])[:min(args.limit,500)]))}
        rows.append(record)
        save_csv(folder/f'{model_id}_predictions.csv',
                 [{'index':j,'label':int(y[j]),'prediction':int(pred[j]),'top_score':float(scores[j,pred[j]])} for j in range(args.limit)],
                 ['index','label','prediction','top_score'])
        np.save(folder/f'{model_id}_confusion.npy',cm,allow_pickle=False)
        print(model_id,f"{record['accuracy_pct']:.2f}%",f"({record['correct']}/{args.limit})")
    save_csv(folder/'accuracy.csv',rows,list(rows[0]))
    write_json(folder/'protocol.json',{'environment':environment(),'limit':args.limit,'indices':f'0..{args.limit-1}',
                'threads':args.threads,'manifest_sha256':sha(BASE/'manifest.json'),'models':ids,
                'reference_changed_classes_scope':f'first {min(args.limit,500)} examples versus same artifact on lecturer x86_64'})
    if set(GROUPS['formats']).issubset(ids):
        def preds(n):
            with (folder/f'{n}_predictions.csv').open() as f:return np.array([int(r['prediction']) for r in csv.DictReader(f)])
        baseline=preds('d1w64_fp32'); comparisons=[]; changed=[]
        for name in ['d1w64_fp16','d1w64_int8']:
            other=preds(name); delta=np.flatnonzero(other!=baseline)
            comparisons.append({'id':name,'reference':'d1w64_fp32','changed_count':int(len(delta)),
                                'changed_pct':len(delta)/args.limit*100})
            for j in delta:changed.append({'id':name,'index':int(j),'label':int(y[j]),'fp32_prediction':int(baseline[j]),'variant_prediction':int(other[j])})
        save_csv(folder/'format_agreement.csv',comparisons,['id','reference','changed_count','changed_pct'])
        save_csv(folder/'changed_predictions.csv',changed,['id','index','label','fp32_prediction','variant_prediction'])
    print('Saved',folder)

def worker(args):
    # New Python process per model and trial. Linux memory values are process-wide.
    # Data and 500 normalized float inputs are identical across variants.
    x,_=load_data(); pool=x[:500].astype(np.float32)/255.0
    before=memory_mib()['VmRSS']; t0=time.perf_counter_ns()
    rt,inp,out=create_runtime(args.model,args.threads)
    init_ms=(time.perf_counter_ns()-t0)/1e6
    allocated=memory_mib()['VmRSS']
    def set_input(j):
        real=pool[j%len(pool):j%len(pool)+1]
        if np.issubdtype(inp['dtype'],np.integer):
            s,z=inp['quantization'];b=np.iinfo(inp['dtype'])
            real=np.clip(np.rint(real/s)+z,b.min,b.max).astype(inp['dtype'])
        rt.set_tensor(inp['index'],real)
    set_input(0);t0=time.perf_counter_ns();rt.invoke();first_ms=(time.perf_counter_ns()-t0)/1e6
    for j in range(args.warmup):set_input(j);rt.invoke()
    latencies=[]
    for j in range(args.calls):
        set_input(j)
        t0=time.perf_counter_ns();rt.invoke();latencies.append((time.perf_counter_ns()-t0)/1e6)
    memory=memory_mib();after=memory['VmRSS'];peak=memory['VmHWM']
    m=model_record(args.model)
    data={'id':args.model,'file_kib':m['file_bytes']/1024,'model_sha256':m['sha256'],
          'threads':args.threads,'warmup_calls':args.warmup,'measured_calls':args.calls,
          'init_check_allocate_ms':init_ms,'first_invoke_ms':first_ms,
          'mean_ms':float(np.mean(latencies)),'median_ms':float(np.median(latencies)),
          'p95_ms':float(np.percentile(latencies,95)), 'max_ms':float(np.max(latencies)),
          'rss_before_model_mib':before,'rss_allocated_mib':allocated,'rss_after_mib':after,
          'peak_process_rss_mib':peak,'latencies_ms':latencies}
    # stdout contains only this machine-readable JSON; LiteRT notices go to stderr.
    print(json.dumps(data))

def benchmark(args):
    if platform.system()!='Linux':raise ValueError('Memory measurements require Linux, including Raspberry Pi OS')
    if args.calls<20 or args.warmup<1 or args.repeats<1:raise ValueError('Use calls >=20, warmup >=1 and repeats >=1')
    ids=get_models(args.models);folder=result_dir(args.run);rows=[];sequence=[]
    # Verify all artifacts before any timing begins.
    for model_id in ids:checked_model(model_id)
    rng=np.random.default_rng(2026)
    for repeat in range(1,args.repeats+1):
        for model_id in rng.permutation(ids).tolist():
            state_before=device_state()
            cmd=[sys.executable,str(Path(__file__).resolve()),'_worker','--model',model_id,
                 '--threads',str(args.threads),'--warmup',str(args.warmup),'--calls',str(args.calls)]
            env=os.environ.copy()
            # Keep incidental BLAS pools from changing the requested CPU protocol.
            env.update(OPENBLAS_NUM_THREADS='1',OMP_NUM_THREADS='1',MKL_NUM_THREADS='1')
            proc=subprocess.run(cmd,capture_output=True,text=True,check=False,env=env)
            (folder/f'{model_id}_trial{repeat}_runtime.log').write_text(proc.stderr)
            if proc.returncode:raise RuntimeError(f'{model_id} failed: {proc.stderr[-2000:]}')
            data=json.loads(proc.stdout);data.update(trial=repeat,state_before=state_before,state_after=device_state())
            write_json(folder/f'{model_id}_trial{repeat}.json',data)
            rows.append(data);sequence.append({'trial':repeat,'id':model_id})
            print(model_id,f"trial {repeat}: median {data['median_ms']:.4f} ms, p95 {data['p95_ms']:.4f} ms, peak RSS {data['peak_process_rss_mib']:.2f} MiB",flush=True)
    fields=['id','trial','file_kib','threads','warmup_calls','measured_calls','init_check_allocate_ms','first_invoke_ms',
            'mean_ms','median_ms','p95_ms','max_ms','rss_before_model_mib','rss_allocated_mib','rss_after_mib','peak_process_rss_mib']
    save_csv(folder/'trials.csv',rows,fields)
    summary=[]
    for model_id in ids:
        group=[r for r in rows if r['id']==model_id]
        summary.append({'id':model_id,'file_kib':group[0]['file_kib'],'trials':len(group),
                        'median_of_trial_medians_ms':statistics.median(r['median_ms'] for r in group),
                        'min_trial_median_ms':min(r['median_ms'] for r in group),
                        'max_trial_median_ms':max(r['median_ms'] for r in group),
                        'median_of_trial_p95_ms':statistics.median(r['p95_ms'] for r in group),
                        'max_peak_process_rss_mib':max(r['peak_process_rss_mib'] for r in group)})
    save_csv(folder/'summary.csv',summary,list(summary[0]))
    write_json(folder/'protocol.json',{'environment':environment(),'models':ids,'order':sequence,'order_seed':2026,
                'threads':args.threads,'warmup_calls':args.warmup,'calls_per_trial':args.calls,'repeats':args.repeats,
                'workload':'first 500 official test images, cycled if calls >500, batch 1',
                'latency_scope':'invoke() only; excludes encoding, set_tensor, get_tensor, model loading and allocation',
                'initialization_scope':'model lookup and hash verification, Interpreter construction and allocate_tensors',
                'memory_scope':'entire fresh Linux process, including imports, mapped dataset and 500 normalized images; /proc/self/status VmRSS and VmHWM, peak from process start through final inference',
                'summary_p95':'median of per-trial p95; not a pooled percentile',
                'manifest_sha256':sha(BASE/'manifest.json')})
    print('Saved',folder)

def collect(args):
    result=BASE/'results'
    files=[p for p in result.rglob('*') if p.is_file()] if result.exists() else []
    if not files:raise ValueError('No results to collect')
    with zipfile.ZipFile(args.output,'x',zipfile.ZIP_DEFLATED) as z:
        for p in files:z.write(p,p.relative_to(BASE))
        for name in ['manifest.json','model_catalog.csv']:z.write(BASE/name,name)
    print('Created',args.output,'with',len(files),'result files')

def report(args):
    if not args.run or not all(c.isalnum() or c in '_-' for c in args.run):
        raise ValueError('Invalid run name')
    folder=BASE/'results'/args.run
    if not folder.is_dir():raise ValueError('Run folder does not exist')
    for filename in ['accuracy.csv','format_agreement.csv','summary.csv']:
        p=folder/filename
        if not p.exists():continue
        print('\n'+filename)
        with p.open() as f:
            for row in csv.DictReader(f):
                print(row.pop('id'))
                for key,value in row.items():print(' ',key,'=',value)
    p=folder/'changed_predictions.csv'
    if p.exists():
        print('\nFirst five changed predictions (same inputs, FP32 versus variant):')
        with p.open() as f:
            rows=list(csv.DictReader(f))
        if not rows:print('No changed predicted classes in this subset.')
        for row in rows[:5]:print(row)
    p=folder/'protocol.json'
    if p.exists():print('\nProtocol file:',p)

def positive(value):
    number=int(value)
    if number<1:raise argparse.ArgumentTypeError('must be positive')
    return number

def main():
    parser=argparse.ArgumentParser(description=__doc__,formatter_class=argparse.RawDescriptionHelpFormatter)
    sub=parser.add_subparsers(dest='command',required=True)
    p=sub.add_parser('check',help='Verify model/data hashes, contracts and reference predictions');p.add_argument('--output')
    sub.add_parser('catalog',help='List supplied models')
    for name in ['inspect','predict','_worker']:
        p=sub.add_parser(name);p.add_argument('--model',required=True);p.add_argument('--threads',type=positive,default=1)
        if name=='predict':p.add_argument('--index',type=int,default=0)
        if name=='_worker':p.add_argument('--warmup',type=positive,default=20);p.add_argument('--calls',type=positive,default=500)
    p=sub.add_parser('evaluate',help='Evaluate a fixed prefix of the official test data')
    p.add_argument('--models',default='architecture');p.add_argument('--limit',type=positive,default=500)
    p.add_argument('--threads',type=positive,default=1);p.add_argument('--run',required=True)
    p=sub.add_parser('benchmark',help='Measure each model in fresh processes')
    p.add_argument('--models',default='architecture');p.add_argument('--threads',type=positive,default=1)
    p.add_argument('--warmup',type=positive,default=20);p.add_argument('--calls',type=positive,default=500)
    p.add_argument('--repeats',type=positive,default=3);p.add_argument('--run',required=True)
    p=sub.add_parser('collect',help='Create a ZIP containing your evidence');p.add_argument('--output',required=True)
    p=sub.add_parser('report',help='Read saved CSV results and show changed predictions');p.add_argument('--run',required=True)
    args=parser.parse_args()
    try:globals()[args.command if args.command!='_worker' else 'worker'](args)
    except (ValueError,OSError,RuntimeError) as exc:
        print(f'ERROR: {exc}',file=sys.stderr);return 1
    return 0

if __name__=='__main__':raise SystemExit(main())
