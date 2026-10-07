abaltaza@raspberrypi:~ $ hostname;  printf 'Model'; tr -d '\0' </proc/device-tree/model; echo; uname -m; python3 --version
raspberrypi
ModelRaspberry Pi 5 Model B Rev 1.1
aarch64
Python 3.13.5
abaltaza@raspberrypi:~ $


---

O aarch64 e especialmente importante porque o PL3 espera um Linux 64-bit para instalar o LiteRT.

Neste PL3 nao estamos a treinar redes no Raspberry Pi. Estamos a pegar nos .tflite ja treinados e a fazer:

modelo treinado -> LiteRT Interpreter -> inference no Raspberry Pi -> medir accuracy/latency/RAM/Storage

Depois vamos comparar:

	Width: d1w32 -> d1w64 -> d1w128

	depth: d1w64 -> d2w64 -> d3w64

	quantizacao: FP32 -> FP16 -> INT8

Timing diferente de Deployement e diferente de Inference!!!


Na PL3 estamos dete lado:

.keras -> conversao -> .tflite -> LiteRT Interpretar no Raspberry Pi -> INFERENCE -> prediction

O raspberryPOI esta a fazer inference sobre imagens do dataset Fashion-MNIST usando o modelo .tflite ja treinado !!!

>  Os Pesos ja foram aprendidos anrtes, no treino.  NO PI, esses pesos ficam fixos.
>
>

*Training* -> alterar os pesos para aprender 

*Inference* -> usar pesos ja aprendidps para produzir uma previsao!
