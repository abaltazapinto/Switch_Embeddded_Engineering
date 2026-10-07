# PL3 model package v3

Use this package with **PL3_AI_Embedded_Systems_Student_v3.pdf**.

PL3 has its own folder and Python environment. The lecturer supplies the trained models, test data and inference tool. Follow Chapter 3 from the beginning on the Raspberry Pi desktop. All experiments are for practice and discussion. No upload or formal submission is required.

Version 3 changes the setup and folder layout. The model files, dataset and inference code are identical to the earlier releases; the networks have not been retrained. The ZIP contains the files directly at its root, ready to extract into your new `~/PL3` folder.

## Contents

- `models/`: five FP32 architectures and two additional exports of the same d1w64 checkpoint.
- `data/test_images.npy`: all 10,000 official Fashion-MNIST test images in original order, uint8, shape (10000, 28, 28).
- `data/test_labels.npy`: corresponding class labels, uint8.
- `lab.py`: checks, tensor inspection, prediction, evaluation, benchmarking and reports.
- `manifest.json`: model/data hashes, shapes, dtypes, training settings and local reference predictions. Reference accuracy is from Linux x86_64, not Raspberry Pi measurements.
- `model_catalog.csv`: model names, architecture, parameters, Dense MACs and artifact sizes.
- `requirements.txt`: inference dependencies only. TensorFlow/Keras is not needed.
- `FASHION_MNIST_LICENSE.txt`: the source dataset licence.

`d2w64` means two hidden Dense layers of 64 ReLU units each. Every architecture has an input (28, 28), Flatten and a final ten-unit Softmax layer. The suffix is `fp32`, `fp16` or `int8`. FP16 weight storage keeps a Float32 input/output interface. INT8 uses integer input and output interfaces, handled automatically by the tool.

The `validation_accuracy` and `validation_loss` fields describe the selected Keras checkpoint **before** conversion. They are shared by its numerical-format variants. The `local_accuracy_500` and `local_accuracy_10000` fields describe actual inference with each converted artifact on the named test subset.

## Download and create the PL3 workspace

Open Moodle in the Raspberry Pi browser and download `PL3_Model_Pack_v3.zip` to Downloads. Wait for the download to finish and use **Show in folder** to confirm the location. The commands assume `~/Downloads/PL3_Model_Pack_v3.zip`. If your folder has a different name, replace `Downloads` below. If the browser added `(1)` to the ZIP name, rename the completed download to the name above.

Open a new terminal on the Pi. If `~/PL3` already exists, stop and rename that previous folder before continuing. The `&&` runs extraction only if the new folder was successfully created.

```bash
ls ~/Downloads/PL3_Model_Pack_v3.zip
mkdir ~/PL3 && \
  python3 -m zipfile -e ~/Downloads/PL3_Model_Pack_v3.zip ~/PL3
cd ~/PL3
ls
ls models
```

You should see `lab.py`, `requirements.txt`, `models` and `data` directly inside `~/PL3`, with seven `.tflite` files in `models`.

## Create the PL3 Python environment

Use 64-bit Raspberry Pi OS, a supported Python version and internet access. Prepare the system tool for creating virtual environments; sudo may ask for your Pi account password:

```bash
sudo apt update
sudo apt install -y python3-venv
```

Create the environment inside this laboratory's folder:

```bash
cd ~/PL3
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --only-binary=:all: -r requirements.txt
which python
python -c "from ai_edge_litert.interpreter import Interpreter"
```

The Python path should end in `/PL3/.venv/bin/python`. This environment uses its own installed packages. No folder, script or environment from another laboratory is needed.

Then run:

```bash
python lab.py check --output device_check.json
python lab.py catalog
python lab.py inspect --model d1w64_fp32
python lab.py predict --model d1w64_fp32 --index 0
```

Follow the handout for the remaining comparisons. The pinned LiteRT 2.2.0 release provides ARM64 Linux wheels for CPython 3.10–3.14; installation and behaviour still require verification on the classroom image.

## Keep and revisit your results

The experiments save CSV and JSON files in `~/PL3/results`. The package check stays in `~/PL3/device_check.json`. Keep these files for your own learning and discussion. No results ZIP or Moodle submission is needed.

After completing the handout, you can reopen the reports in a new terminal:

```bash
cd ~/PL3
source .venv/bin/activate
python lab.py report --run architecture_cost
python lab.py report --run formats_quality
```

These commands read saved results. To run an experiment again, choose a new `--run` name. Close the terminal when finished and use the same activation commands when returning to PL3.

## Results and measurement scope

Commands use a unique `--run` name and refuse to overwrite previous results. The default benchmark uses batch 1, one inference thread, 20 warm-up calls after the separately recorded first call, 500 measured invocations and three independent process trials. It varies the order of models between trials.

Timing covers `Interpreter.invoke()` only. It excludes model setup, input encoding, tensor copies and output interpretation. RSS and peak RSS are Linux `/proc/self/status` VmRSS and VmHWM values for the entire fresh process, including Python, libraries, dataset mapping and a common pool of 500 normalized images. These kernel-reported counters are not exact tensor-memory measurements. All measured times and memory values must be associated with the device and protocol that produced them.

The CSV summary reports the median of trial medians, the range of trial medians, the median of trial p95 values and the maximum trial peak RSS. The median of p95 values is not a pooled p95. Raw trial times and device-state observations remain in the JSON files. Missing telemetry is `null`, not zero.

The runtime uses default LiteRT CPU delegates with the requested thread count. It does not force every model to use an identical kernel implementation. Different representations may select different eligible kernels. Do not infer GPU, NPU or energy measurements from this CPU experiment.

## Data attribution

Fashion-MNIST by Zalando Research: https://github.com/zalandoresearch/fashion-mnist

The images and labels retain their official test order and values. They are repackaged as NumPy arrays for offline classroom use. The source MIT licence accompanies this package. Training uses the official training split; calibration uses 500 examples from the 54,000-image training partition only.

All models and labels are intended for the Fashion-MNIST teaching task. Scores are not calibrated guarantees of correctness.
