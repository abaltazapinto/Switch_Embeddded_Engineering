
> whoami
hostname
pwd
uname -m
python3 --version

mkdir -p ~/ai-embedded/pl1
cd ~/ai-embedded/pl1

pwd
ls -lah
---

User:         abaltaza
Hostname:     raspberrypi
Architecture: aarch64
Python:       3.13.5
Workspace:    /home/abaltaza/ai-embedded/pl1

Distinguir:

aarch64 → arquitetura/instruction set
nproc → CPUs lógicas disponíveis ao Linux
Model name → CPU que o kernel identifica
CPU max MHz → frequência máxima reportada

i-embedded/pl1 $ uname -m
nproc

# Raspberrypi5 

> 3.2

---
uname -m
nproc

lscpu | egrep 'Architecture|Model name|CPU\(s\)' || true
lscpu | grep 'CPU max MHz' || true

---

lscpu | egrep 'Architecture|Model name|CPU\(s\)' || true
lscpu | grep 'CPU max MHz' || true
aarch64
4
Architecture:                            aarch64
CPU(s):                                  4
On-line CPU(s) list:                     0-3
Model name:                              Cortex-A76
CPU(s) scaling MHz:                      62%
NUMA node0 CPU(s):                       0-3
NUMA node1 CPU(s):                       0-3
NUMA node2 CPU(s):                       0-3
NUMA node3 CPU(s):                       0-3
NUMA node4 CPU(s):                       0-3
NUMA node5 CPU(s):                       0-3
NUMA node6 CPU(s):                       0-3
NUMA node7 CPU(s):                       0-3
CPU max MHz:                             2400.0000


# Pergunta rápida: qual destes dois achas que limita diretamente os tensores durante a execução: RAM ou espaço livre no cartão/disco?

A distinção importante para o caderno: RAM é o recurso diretamente usado durante a inferência para runtime, tensores e dados intermédios; o df mede armazenamento persistente para modelos, datasets, logs e ambiente Python. O guião trata estes dois budgets separadamente.

> Corre

free -h
df -h /
python3 --version

deu: 

CPU max MHz:                             2400.0000
abaltaza@raspberrypi:~/ai-embedded/pl1 $ free -h
df -h /
python3 --version
               total        used        free      shared  buff/cache   available
Mem:           7.9Gi       3.0Gi       1.3Gi       263Mi       4.3Gi       4.9Gi
Swap:          2.0Gi       242Mi       1.8Gi
Filesystem      Size  Used Avail Use% Mounted on
/dev/nvme0n1p2  234G  165G   57G  75% /
Python 3.13.5

- Ainda no 3.2. Agora medimos a temperatrura baseline do CPU, porque e estado dinamico do sistema e podera ser comparada com a temperatura sob carga de inferencia. 

> Corre:

if command -v vcgencmd >/dev/null 2>&1; then
  vcgencmd measure_temp
elif [ -r /sys/class/thermal/thermal_zone0/temp ]; then
  awk '{printf "temp=%.1f C\n", $1/1000}' \
  /sys/class/thermal/thermal_zone0/temp
else
  echo 'CPU temperature: not available'
fi

**Objectivo**

guardar a temperatura do Raspberry Pi antes de executarmos inferencia

Sim. No teu Raspberry Pi 5, basta:

> vcgencmd measure_temp

E obtiveste:

temp=43.3'C


# Exercício 3.3 — Fashion-MNIST: acquire the data

rrypi:~/ai-embedded/pl1 $ cd ~/ai-embedded/pl1
mkdir -p data

> corre :
python3 - <<'PY'
from urllib.request import urlretrieve

host = "https://raw.githubusercontent.com"
repo = "/zalandoresearch/fashion-mnist"
folder = "/master/data/fashion"

files = [
    "t10k-images-idx3-ubyte.gz",
    "t10k-labels-idx1-ubyte.gz",
]

for name in files:
    url = host + repo + folder + "/" + name
    urlretrieve(url, "data/" + name)
    print("Downloaded:", name)
PY
Downloaded: t10k-images-idx3-ubyte.gz
Downloaded: t10k-labels-idx1-ubyte.gz
abaltaza@raspberrypi:~/ai-embedded

Downloads feitos ✅ Vamos fechar o 3.3 num único bloco para chegar já ao 3.4.

PL1 — Exercício 3.3 — Fashion-MNIST

Concluído ✅


Os resultados batem com o guião:

Images MD5: bef4ecab320f06d8554ea6380940ec79
Labels MD5: bb300cfdad3c16e7a12a480ee83cd310
Image shape: (10000, 28, 28)
dtype: uint8
range: 0..255
Classes: 10 × 1000 exemplos

# PL1 — Exercício 3.4 — LiteRT and the reference model

Agora criamos o virtual environment. O guião exige ambiente isolado e diz explicitamente para não instalar isto no Python global.

> Corre:

cd ~/ai-embedded/pl1

sudo apt-get install -y python3-venv python3-pip

python3 -m venv .venv
source .venv/bin/activate

python -m pip --version

Hipótese rápida: se isto falhar, o primeiro suspeito será compatibilidade do pacote com Python 3.13 / aarch64.

Corre:

python -m pip install --disable-pip-version-check \
  'ai-edge-litert==2.2.0' \
  'numpy<3'

  PL1 — Exercício 3.4 — LiteRT + reference model

Runtime instalado e import verificado ✅

ai-edge-litert: 2.2.0
NumPy:          2.5.3
Interpreter:    OK

Agora ainda no 3.4, falta adquirir o modelo .tflite de referência. O guião usa um commit fixo para garantir que todos avaliam exatamente o mesmo artefacto.

Corre:

mkdir -p model

python - <<'PY'
from urllib.request import urlretrieve

host = "https://raw.githubusercontent.com"
repo = "/LycusCoder/Mini-Vision_System-_Fashion-MNIST_Classifier"
commit = "/8e480da0b55b286fbb7dd48201c7bcb660e6bb70"
file = "/models/fashion_mnist_mlp.tflite"

target = "model/fashion_mnist_mlp.tflite"
url = host + repo + commit + file

urlretrieve(url, target)
print("Model downloaded to:", target)
PY

ls -lh model/fashion_mnist_mlp.tflite
sha256sum model/fashion_mnist_mlp.tflite

---

Guardar duas evidências:

Model size: ...
SHA-256:    ...

O hash serve para provar que estás a executar o mesmo modelo que o resto da experiência, não apenas um ficheiro com o mesmo nome.

---

PL1 — Exercício 3.4 — LiteRT + reference model

Modelo adquirido e fingerprint registada ✅

Model size: 1.6 MB
SHA-256:
9bdcd2b767536f03c21fab6660f4e829d9a2c4404bc5c4881f4fdf4040d6978b

Agora vem a parte central do 3.4: carregar o .tflite, alocar os tensors e descobrir o contrato real do modelo — shape, dtype e quantização de input/output. O PL1 pede explicitamente que não adivinhemos esta interface.

---
> Corre

python - <<'PY'
from ai_edge_litert.interpreter import Interpreter

model = "model/fashion_mnist_mlp.tflite"

interpreter = Interpreter(model_path=model)
interpreter.allocate_tensors()

input_info = interpreter.get_input_details()[0]
output_info = interpreter.get_output_details()[0]

print("Model loaded and tensors allocated")

print("\nINPUT")
print(" name:", input_info["name"])
print(" shape:", input_info["shape"])
print(" dtype:", input_info["dtype"])
print(" quantization:", input_info.get("quantization"))

print("\nOUTPUT")
print(" name:", output_info["name"])
print(" shape:", output_info["shape"])
print(" dtype:", output_info["dtype"])
print(" quantization:", output_info.get("quantization"))
PY

---

PL1 — Exercício 3.4 — LiteRT + reference model

3.4 concluído ✅

O contrato real do modelo ficou confirmado:

INPUT
shape:        [1, 28, 28]
dtype:        float32
quantization: (0.0, 0)

OUTPUT
shape:        [1, 10]
dtype:        float32
quantization: (0.0, 0)

Interpretação curta para guardares no caderno:

[1, 28, 28]
 │   │   │
 │   │   └─ 28 colunas
 │   └───── 28 linhas
 └───────── batch de 1 imagem

[1, 10]
 │   └───── 10 scores/classes
 └───────── batch de 1


 # PL1 — Exercício 3.5 — Run your first local inference

Agora vamos construir infer_one.py. O objetivo é fazer o pipeline completo:

Fashion-MNIST
     ↓
uint8 0..255
     ↓
float32
     ↓
/ 255.0
     ↓
[1,28,28]
     ↓
LiteRT
     ↓
[1,10] scores
     ↓
classe prevista

Isto é exatamente o pipeline que o 3.5 quer tornar explícito.

Ação — primeiro bloco do 3.5

> Corre:

cat > infer_one.py <<'PY'
import gzip
import struct
import sys
import numpy as np
from ai_edge_litert.interpreter import Interpreter

LABELS = [
    "T-shirt/top", "Trouser", "Pullover", "Dress", "Coat",
    "Sandal", "Shirt", "Sneaker", "Bag", "Ankle boot",
]

def load_images(path):
    f = gzip.open(path, "rb")
    _, n, rows, cols = struct.unpack(">IIII", f.read(16))
    data = np.frombuffer(f.read(), dtype=np.uint8)
    f.close()
    return data.reshape(n, rows, cols)

def load_labels(path):
    f = gzip.open(path, "rb")
    f.read(8)
    data = np.frombuffer(f.read(), dtype=np.uint8)
    f.close()
    return data
PY

# 

# PL1 — Exercício 3.5 — First local inference

Ótimo. O ficheiro está sintaticamente correto ✅

Agora adicionamos só a função predict(), que faz o pipeline completo de inferência para uma imagem. O guião usa exatamente esta sequência: carregar dados, converter uint8 → float32, normalizar por 255.0, adaptar ao input shape, invocar LiteRT e ordenar os 3 maiores scores.

> AFTER === python infer_one.py 25 

ython infer_one.py ^C
(.venv) abaltaza@raspberrypi:~/ai-embedded/pl1 $ python infer_one.py 25
INFO: Created TensorFlow Lite XNNPACK delegate for CPU.
true: 4 Coat
1 2 Pullover 0.7970833778381348
2 4 Coat 0.11705663800239563
3 6 Shirt 0.08160335570573807
(.venv) abaltaza@raspberrypi:~/ai-embedded/pl1 $ 


prediction scor diferent from guaranteed probbility of correctness. 

python infer_one.py 0
python infer_one.py 1
python infer_one.py 42

deu 

(.venv) abaltaza@raspberrypi:~/ai-embedded/pl1 $ python infer_one.py 0
python infer_one.py 1
python infer_one.py 42
INFO: Created TensorFlow Lite XNNPACK delegate for CPU.
true: 9 Ankle boot
1 9 Ankle boot 0.9811438322067261
2 7 Sneaker 0.016606630757451057
3 5 Sandal 0.002239250810816884
INFO: Created TensorFlow Lite XNNPACK delegate for CPU.
true: 2 Pullover
1 2 Pullover 0.997886598110199
2 4 Coat 0.0014460566453635693
3 0 T-shirt/top 0.0003556701703928411
INFO: Created TensorFlow Lite XNNPACK delegate for CPU.
true: 3 Dress
1 3 Dress 0.48964568972587585
2 0 T-shirt/top 0.29810091853141785
3 6 Shirt 0.13333779573440552
(.venv) abaltaza@raspberrypi:~/ai-embedded/pl1 $ 


o idx 42 e interessante: acertou mesmo com score bastante inderior aos outros. E o idx 25 mostrou o contrario: score alto e previsao jerrada. O PL1 usa precisamente estes exemplos para mostrar algumas inferencias isoladas nao bastam para avaliar o modelo...

# PL1 — Exercício 3.6 — Evaluate beyond isolated examples

Agora vamos avaliar 500 imagens fixas e obter:

accuracy
confusion matrix
highest-confidence errors

PL1 — Exercício 3.6 — Evaluate beyond isolated examples

3.6 concluído ✅

Resultado principal:

accuracy = 0.872 = 87.2%

As confusões mais visíveis foram:

Shirt      → T-shirt/top : 11
Coat       → Pullover    : 9
Pullover   → Shirt       : 5
Ankle boot → Sneaker     : 4

E há um resultado especialmente importante:

sample 441
true = Ankle boot
pred = Sneaker
score = 0.9983 ❌

Ou seja: um score de 99.8% não garante que a previsão esteja correta. É precisamente por isso que o PL1 pede para analisar a estrutura dos erros e não apenas a accuracy.

---

PL1 — Exercício 3.7 — Break the preprocessing contract deliberately

Agora vamos fazer uma experiência muito importante para Embedded AI: manter modelo, runtime e dados iguais e mudar apenas o preprocessing.

Antes de executar, quero só a tua hipótese:

A) correto:        pixel / 255       → 0..1
B) raw:            pixel             → 0..255
C) double divide:  pixel / 255 / 255 → ~0..0.0039

Qual achas que vai dar maior accuracy?

A > B > C
A > C > B
ou outra?

Responde só com a tua hipótese e passamos imediatamente ao código do 3.7.

acho que a 1.

PL1 — Exercício 3.7 — Break the preprocessing contract deliberately

Hipótese registada:

A > B > C

ou seja:

correct 0..1  >  raw 0..255  >  double divide

Agora criamos o teste controlado. O PL1 pede manter modelo, dados e runtime fixos e alterar apenas a escala de entrada.

Ação
cat > preprocessing_test.py <<'PY'
import numpy as np
from ai_edge_litert.interpreter import Interpreter
from infer_one import load_images, load_labels

X = load_images("data/t10k-images-idx3-ubyte.gz")
y = load_labels("data/t10k-labels-idx1-ubyte.gz")

runtime = Interpreter(model_path="model/fashion_mnist_mlp.tflite")
runtime.allocate_tensors()

input_info = runtime.get_input_details()[0]
output_info = runtime.get_output_details()[0]

shape = tuple(int(v) for v in input_info["shape"])

def infer_class(x):
    runtime.set_tensor(input_info["index"], x.reshape(shape))
    runtime.invoke()
    return int(np.argmax(runtime.get_tensor(output_info["index"])[0]))
PY
> Resposta

print("raw", evaluate(1.0))
print("double", evaluate(1.0 / (255.0 * 255.0)))
PY
(.venv) abaltaza@raspberrypi:~/ai-embedded/pl1 $ python preprocessing_test.py 
INFO: Created TensorFlow Lite XNNPACK delegate for CPU.
correct 0.8766666666666667
raw 0.88
double 0.09
(.venv) abaltaza@raspberrypi:~/ai-embedded/pl1 $ 

# GPT

7 — Break the preprocessing contract deliberately

3.7 concluído ✅

A tua hipótese era:

correct > raw > double

Mas medimos:

correct  0.8767  → 87.67%
raw      0.8800  → 88.00%
double   0.0900  →  9.00%


Portanto a hipotese foi parcialmente falsificada. O resultado mais importante nao e o raw ter ficado 0.33 pontos percentuais acima; e perceber que um preprocessing errado pode parecer funcionar perfeitamente. O proprio enunciado alerta para isto: uma pipeline incorrecta que ibtem accuracy semelhante neste subset nao prova equivalencia semantica nem validade de depoloyment. 

> Para o caderno : 

Model contract ≠ apenas shape + dtype.

Training preprocessing:
uint8 0..255
      ↓
float32
      ↓
/255
      ↓
0..1

Uma violação do preprocessing pode ser SILENCIOSA:
accuracy semelhante não significa pipeline correta.


O double = 9% praticamente destruiu a informação útil para um problema de 10 classes. Já o raw = 88% é precisamente o caso perigoso: está errado segundo o contrato de treino, mas olhando apenas para top-1 accuracy poderíamos não perceber.

# PL1 — Exercício 3.8 — Close the laboratory with an evidence record

Chegámos ao último exercício. 🎯

O PL1 agora quer consolidar as evidências do deployment: board, dataset, modelo, tensor contract, preprocessing e avaliação.


> Faz

cat > evidence.txt <<'EOF'
PL1 - Evidence Record

Board:
Raspberry Pi 5
Architecture: aarch64
CPU: Cortex-A76
Logical CPUs: 4
CPU max: 2400 MHz
RAM: 7.9 GiB
Python: 3.13.5
Baseline CPU temperature: 43.3 C

Dataset:
Fashion-MNIST test set
Images shape: (10000, 28, 28)
dtype: uint8
range: 0..255
Images MD5: bef4ecab320f06d8554ea6380940ec79
Labels MD5: bb300cfdad3c16e7a12a480ee83cd310

Model:
fashion_mnist_mlp.tflite
SHA256: 9bdcd2b767536f03c21fab6660f4e829d9a2c4404bc5c4881f4fdf4040d6978b
EOF


Agora fechamos o registo com aquilo que o enunciado pede explicitamente: tensor contract, preprocessing, avaliação, erro/confusão relevante e efeito do preprocessing incorreto.

