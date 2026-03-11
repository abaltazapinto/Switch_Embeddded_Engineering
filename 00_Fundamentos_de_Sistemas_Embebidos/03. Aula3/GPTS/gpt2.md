Vou transformar as tuas **slides + notas da Aula 3** num conjunto de **notas estruturadas de estudo**, como se estivesses a preparar-te para exame de sistemas embebidos. 📘

---

# Study Notes — Aula 3 (Embedded Systems Pipeline)

## 1. Signal Acquisition from Sensors

Embedded systems começam quase sempre com **sensores** que capturam fenómenos físicos.

Exemplos:

* temperatura
* aceleração
* campo magnético
* pressão
* luz

O sinal vindo do sensor **raramente está pronto para ser usado**.

Por isso existe uma etapa chamada:

### Signal Conditioning

Operações típicas:

**1. Offset correction**

* Corrigir deslocamentos do sinal.
* Exemplo: sensor devia dar 0 mas dá 0.2.

**2. Linearization**

* Alguns sensores não têm resposta linear.
* É necessário transformar o sinal para algo proporcional.

**3. Protection circuits**

* Proteger o microcontrolador de:

  * sobretensão
  * ruído
  * correntes excessivas.

---

# 2. Signal Filtering

Sensores reais têm **ruído elétrico**.

Para remover ruído usamos **filtros**.

Tipos comuns:

* **Low-pass filter** → remove ruído de alta frequência
* **High-pass filter** → remove drift
* **Band-pass filter** → mantém apenas certas frequências

Objetivo:

Remover **componentes indesejadas** antes da conversão digital.

---

# 3. Analog to Digital Conversion (ADC)

Microcontroladores trabalham com **dados digitais**.

Por isso o sinal analógico precisa ser convertido.

### Resolution

Se o ADC tiver:

* **8 bits** → 256 níveis
* **10 bits** → 1024 níveis
* **12 bits** → 4096 níveis

Quanto maior a resolução:

→ **maior precisão**

---

### Quantization Error

Erro introduzido pela discretização.

Exemplo:

Range = 0–5V
ADC = 8 bits

[
Step = 5V / 256
]

Cada nível representa um pequeno intervalo.

Resultado:

Nunca sabemos o valor **exato**, apenas o intervalo.

---

### Sampling Rate

Define **quantas vezes por segundo o sinal é medido**.

Problema clássico:

**aliasing**

Se a taxa de amostragem for muito baixa, o sinal digital pode representar algo errado.

Regra conhecida:

**Nyquist theorem**

[
Sampling\ Rate > 2 × Highest\ Signal\ Frequency
]

---

# 4. Sensor Fusion

Combinar dados de **múltiplos sensores**.

Exemplo clássico:

Para saber a **orientação de um objeto**:

Usamos:

* acelerómetro
* giroscópio
* magnetómetro

Com algoritmos matemáticos podemos determinar:

* posição
* orientação
* movimento

Aplicação real:

* drones
* smartphones
* navegação militar sem GPS (quando há **GPS jamming**)

---

# 5. Control Algorithms

Depois de ler sensores, o sistema toma decisões.

Algoritmo clássico:

## PID Controller

Controla sistemas físicos como:

* temperatura
* velocidade
* posição

PID significa:

**P — Proportional**
→ reage ao erro atual

**I — Integral**
→ corrige erros acumulados

**D — Derivative**
→ prevê comportamento futuro

Exemplo:

Controlar temperatura:

Se T < Target → aquecer
Se T > Target → desligar

Mas o PID evita oscilações.

---

# 6. Communication Interfaces

Sistemas embebidos comunicam com periféricos ou outros sistemas.

Interfaces comuns:

### UART

* comunicação serial simples
* envia **1 byte de cada vez**

Usado em:

* debug
* comunicação simples

---

### SPI

* comunicação rápida
* clock + data lines
* usado para sensores e memória

---

### I2C

* dois fios
* permite vários dispositivos no mesmo barramento

---

### CAN

Muito usado em **automóveis**.

Características:

* robusto
* até ~1 Mbps
* mensagens pequenas (~8–9 bytes)

Usado para comunicação entre:

* ECU
* sensores
* sistemas do carro

---

### Ethernet

Comunicação de rede.

Mais pesado para microcontroladores porque:

* exige memória
* stack TCP/IP complexo.

---

### WiFi

Versão sem fios do Ethernet.

---

### Bluetooth / BLE

Alcance curto (~10 m)

Muito usado em:

* wearables
* sensores IoT
* dispositivos médicos

---

# 7. Actuators

Depois de processar informação o sistema **atua no mundo físico**.

Exemplos:

* válvulas
* motores
* relés
* aquecedores

Relé:

Interruptor elétrico controlado eletricamente.

---

# 8. Energy Constraints

Energia é um dos maiores desafios.

## Cenários

### Energia ilimitada

* ligado à rede elétrica
* geradores

### Energia limitada

* baterias
* dispositivos móveis
* sensores remotos

Problema:

Baterias grandes → peso elevado.

---

## Energy Harvesting

Captar energia do ambiente.

Exemplos:

* painéis solares
* vibração
* calor
* vento

Aplicações:

* sensores agrícolas
* sensores ambientais

Objetivo:

Sistemas que **funcionam indefinidamente**.

---

## Low Power Design

Técnicas:

* sleep modes
* duty cycling
* algoritmos eficientes
* desligar periféricos

---

# 9. Software Architecture in Embedded Systems

Camadas típicas:

### Firmware

Código executado diretamente no microcontrolador.

---

### Device Drivers

Software que controla hardware específico.

Permite abstração.

Exemplo:

Driver para:

* UART
* SPI
* sensor específico

---

### Operating System

Alguns sistemas usam:

**RTOS — Real Time Operating System**

Exemplos:

* FreeRTOS
* Zephyr
* RT Linux

Mas:

Sistemas embebidos com controlo **microsegundos** muitas vezes **não usam OS**.

---

# 10. Embedded System Development Process

Etapas típicas:

### 1. Requirements

Identificar:

* stakeholders
* funcionalidades
* restrições

Exemplo:

"valores devem aparecer a verde"

---

### 2. System Design

Arquitetura do sistema:

* sensores
* microcontrolador
* comunicação
* atuadores

---

### 3. Hardware Design

Se necessário:

* PCB
* circuitos específicos

---

### 4. Implementation

Desenvolvimento de:

* firmware
* drivers
* algoritmos

---

### 5. Testing and Validation

Muito crítico em sistemas embebidos.

Porque erros podem causar:

* falhas físicas
* riscos de segurança
* instabilidade

Exemplo real citado na aula:

Sistema de disjuntores com **oscilações de potência**.

Foi necessário redesenhar o controlo.

---

### 6. Deployment

Implementação final do sistema.

---

# Mind Map — Aula 3

```
Embedded System Pipeline
│
├── Sensors
│     ├ signal conditioning
│     ├ offset correction
│     └ linearization
│
├── Filtering
│     └ noise removal
│
├── ADC
│     ├ resolution
│     ├ quantization error
│     └ sampling rate
│
├── Sensor Fusion
│     └ accelerometer + gyro + magnetometer
│
├── Control Algorithms
│     └ PID
│
├── Communication
│     ├ UART
│     ├ SPI
│     ├ I2C
│     ├ CAN
│     ├ Ethernet
│     └ Bluetooth
│
├── Actuators
│     ├ valves
│     └ relays
│
├── Energy
│     ├ batteries
│     ├ energy harvesting
│     └ low power design
│
└── Development Process
      ├ requirements
      ├ design
      ├ implementation
      ├ testing
      └ deployment
```

---

# Typical Exam Questions

### Conceptual

1. Explain the role of **signal conditioning** in embedded systems.
2. What is **quantization error** and why does it occur?
3. What is the difference between **SPI and I2C**?
4. Explain the concept of **sensor fusion** with an example.
5. Why are **low power techniques** critical in embedded systems?

---

### Applied

6. If an ADC has **10 bits resolution**, how many levels exist?
7. Why is **sampling rate important**?
8. Describe the architecture layers of an embedded system.

---

# Typical Exam Traps

Students often confuse:

**Sampling rate vs resolution**

* Resolution → precision
* Sampling rate → temporal frequency

---

Confusing:

**UART vs SPI vs I2C**

UART:

* asynchronous

SPI:

* fastest
* multiple wires

I2C:

* two wires
* addressing

---

Thinking embedded systems always run an OS.

Many **do not**.

---

# Real-World Examples

### Smartphones

Sensor fusion:

* accelerometer
* gyro
* magnetometer

→ orientation detection.

---

### Automotive

CAN bus:

ECUs communicate:

* engine
* braking
* steering

---

### Agriculture IoT

Sensors:

* soil moisture
* solar powered

→ energy harvesting.

---

# After Class — Test Your Understanding

### Question 1

Why do embedded systems use **signal filtering** before ADC?

---

### Question 2

What determines the **precision** of an ADC?

---

### Question 3

Why is **sensor fusion** useful in navigation systems?

---

### Question 4

Explain the difference between **actuators and sensors**.

---

### Question 5

Why are **low-power algorithms** important in IoT devices?

---

# One-Page Exam Cheat Sheet

**Pipeline**

Sensor → Conditioning → Filtering → ADC → Processing → Communication → Actuation

---

**ADC**

Resolution:

[
2^{bits}
]

Quantization:

[
Error = Range / Levels
]

---

**Communication**

UART → simple serial
SPI → fast
I2C → multi-device bus
CAN → automotive

---

**Control**

PID:

P → current error
I → accumulated error
D → predicted error

---

**Energy**

Battery constraints
Energy harvesting
Sleep modes

---

**Development**

Requirements → Design → Implementation → Testing → Deployment

---

# Ação (1 passo)

Criar um **flashcard deck (20 perguntas)** desta aula no Anki/RemNote para consolidar memória de longo prazo.

**Objetivo:**
Transformar os conceitos da aula em **recall ativo**, que é a forma mais eficiente de estudar engenharia.

**Output gerado:**
Deck de **20 flashcards de embedded systems fundamentals**.

---

## Como pensar (como um engenheiro)

Para aprofundar esta aula, consulta fontes clássicas:

* **Embedded Systems: Real-Time Interfacing — Jonathan Valvano**
* **Making Embedded Systems — Elecia White**
* **Sensors and Signal Conditioning — Ramon Pallás-Areny**
* IEEE papers sobre **sensor fusion** e **low-power embedded design**

---

## Pitfalls

* estudar embedded só ao nível de software
* ignorar **hardware constraints**
* esquecer **energia e ruído**
* confundir **ADC resolution vs sampling rate**

---

## Alternativas / tradeoffs

Estudar a matéria com duas abordagens:

**Approach A — Hardware-first**

* entender sensores
* ADC
* eletrónica

**Approach B — Systems-first**

* arquitetura
* comunicação
* software stack

Ambos são válidos.

---

## Pergunta de decisão

Queres que eu também gere **o que normalmente sai no exame desta matéria (top 10 perguntas mais prováveis)**? Isso costuma acelerar muito a preparação.
