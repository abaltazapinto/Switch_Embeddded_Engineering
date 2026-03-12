Vou reconstruir a **Aula 3** como se estivéssemos a preparar um aluno para um exame de sistemas embebidos / microcontroladores. As tuas notas têm vários pontos corretos, mas também algumas confusões típicas quando se aprende **ADC + representação digital + hardware do ATmega128**.

---

# 1. Structured Study Notes (Reconstructed Lecture)

## 1️⃣ Analog vs Digital Signals

Microcontroladores trabalham **digitalmente**, mas o mundo real é **analógico**.

Exemplos de sinais analógicos:

* temperatura
* tensão de sensores
* som
* velocidade de motor

Para que o microcontrolador consiga processar estes sinais usamos:

**ADC — Analog to Digital Converter**

Função:

```
tensão analógica → número digital
```

---

# 2️⃣ ADC Resolution

A **resolução** depende do número de bits do conversor.

Se o ADC tem **N bits**:

```
Number of levels = 2^N
```

Exemplo:

ADC de **10 bits (ATmega128)**

```
2^10 = 1024 níveis
```

Se:

```
Vref = 5V
```

então cada passo (LSB) vale:

```
LSB = Vref / 1024
LSB ≈ 4.88 mV
```

Significa:

Cada incremento do ADC representa cerca de **4.88 mV**.

---

# 3️⃣ LSB (Least Significant Bit)

O **LSB** é o menor valor que o ADC consegue distinguir.

Exemplo:

```
0V → ADC = 0
0–4.88mV → ainda ADC = 0
4.88mV → ADC = 1
```

Portanto valores abaixo de **1 LSB** são perdidos.

Este fenómeno chama-se:

**quantization error**

---

# 4️⃣ ADC Accuracy Problems

Na prática um ADC real tem vários erros:

### Offset error

valor diferente de zero quando a entrada é zero.

### Gain error

inclinação errada da curva.

### Non-linearity

curva não perfeitamente linear.

### Noise

ruído elétrico.

Quanto menor estes erros → **mais caro é o ADC**.

---

# 5️⃣ Sampling Rate (Taxa de Amostragem)

O ADC não mede continuamente.

Ele faz **amostras discretas no tempo**.

```
Sampling rate = número de medições por segundo
```

Exemplo:

```
1000 samples/s → 1 kHz
```

Para medir velocidade de motor pode ser necessário:

```
kHz sampling rates
```

### Limitação importante

Se aumentarmos muito a frequência:

```
ADC pode não ter tempo para converter
```

Resultado:

```
perda de precisão
```

Isto acontece no **ATmega128** quando o clock do ADC é demasiado rápido.

---

# 6️⃣ Successive Approximation ADC

O ADC do ATmega128 usa:

**SAR — Successive Approximation Register**

Funcionamento simplificado:

O ADC faz uma **árvore de decisão binária**:

```
Is input > Vref/2 ?
Yes / No
```

Depois:

```
Is input > Vref/4 ?
```

Depois:

```
Is input > Vref/8 ?
```

Até encontrar o valor final.

Vantagens:

* rápido
* eficiente
* comum em microcontroladores

---

# 7️⃣ Differential Signals (Important Concept)

Muito usado em comunicações e sensores.

Em vez de transmitir:

```
signal
```

transmite-se:

```
+signal
-signal
```

O receptor mede:

```
difference = V+ − V-
```

Vantagem:

Ruído externo aparece **igual nos dois fios**.

Então:

```
noise - noise = 0
```

Isto chama-se:

**Common Mode Noise Rejection**

Exemplos reais:

* microphones profissionais
* USB
* PCI Express
* SATA

---

# 8️⃣ ATmega128 ADC Architecture

Componentes principais:

```
Analog Inputs
        ↓
Multiplexer
        ↓
Sample & Hold
        ↓
SAR ADC
        ↓
Data Registers
```

---

# 9️⃣ ADC Multiplexer

Permite escolher qual pino converter.

Exemplo:

```
ADC0
ADC1
ADC2
ADC3
...
```

Mas só **um de cada vez**.

Se converteres 8 canais:

```
sampling rate total / 8
```

---

# 10️⃣ Reference Voltage (Vref)

Define o intervalo máximo de medição.

Exemplo:

```
0 → Vref
```

No ATmega existem três opções:

### 1️⃣ AREF pin

referência externa (mais precisa)

### 2️⃣ AVCC

alimentação do microcontrolador

### 3️⃣ Internal reference

gerada internamente (~1.1V)

Tradeoff:

| opção    | precisão                   | simplicidade  |
| -------- | -------------------------- | ------------- |
| AREF     | melhor                     | menos simples |
| AVCC     | média                      | fácil         |
| Internal | boa para sensores pequenos | fácil         |

---

# 11️⃣ AVCC Pin

AVCC alimenta:

```
parte analógica do microcontrolador
```

Boa prática:

separar alimentação:

```
digital
analog
```

Porque sinais digitais criam:

```
switching noise
```

---

# 12️⃣ ADC Registers

O resultado da conversão fica em **dois registos**:

```
ADCL (low byte)
ADCH (high byte)
```

Resultado total:

```
10 bits
```

Importante:

Primeiro ler:

```
ADCL
```

Depois:

```
ADCH
```

Isto **bloqueia o valor** durante a leitura.

---

# 13️⃣ Left Adjust / Right Adjust

Configuração de alinhamento dos bits.

### Right Adjust (normal)

```
ADCH  [xx xxxx]
ADCL  [xxxx xxxx]
```

### Left Adjust

Útil se quiseres apenas **8 bits**.

---

# 14️⃣ ADC Operating Modes

### Single Conversion

Conversão começa quando software manda.

```
write control register
```

### Free Running Mode

ADC converte continuamente.

---

# 2. Difficult Parts Explained Simply

## Quantization

Converter analógico → digital é como **arredondar números**.

Exemplo:

temperatura:

```
21.34°C
```

ADC pode apenas representar:

```
21.3°C
```

Sempre existe erro.

---

## Successive Approximation

Imagina adivinhar um número entre 0 e 1023.

Perguntas:

```
>512 ?
>256 ?
>128 ?
```

Cada pergunta descobre um bit.

---

## Differential Mode

Em vez de medir:

```
sensor → GND
```

mede-se:

```
sensor+ − sensor-
```

Ruído externo cancela.

---

# 3. Corrections / Inconsistencies in Your Notes

### ❌ "unsigned int vs signed"

ADC normalmente usa:

```
unsigned
```

Porque mede:

```
0 → Vref
```

Não valores negativos.

---

### ❌ "200 vezes a precisão pior"

Provavelmente referia-se a:

```
differential gain modes
```

que reduzem **effective resolution**.

---

### ❌ "ler ADC antes da conversão"

Na verdade:

```
ler antes da conversão terminar = valor antigo
```

Normalmente espera-se:

```
ADC interrupt
ou
conversion flag
```

---

### ❌ Confusão LSB/MSB

```
LSB → bit menos significativo
MSB → bit mais significativo
```

---

# 4. Possible Exam Questions

## Theoretical

1. Explain how an ADC works.
2. What determines ADC resolution?
3. Explain quantization error.
4. What is sampling rate?
5. What is the role of Vref?

---

## Short Answer

1. How many levels does a 10-bit ADC have?
2. What is the LSB size for a 5V reference?
3. What is the function of the ADC multiplexer?
4. Why must ADCL be read before ADCH?

---

## Conceptual Questions

1. Why does increasing sampling rate reduce precision?
2. Why separate analog and digital power supplies?
3. Why do high speed communication systems use differential signals?

---

# 5. Mind Map

```
ADC
│
├── Analog vs Digital
│
├── Resolution
│   ├── bits
│   └── LSB
│
├── Errors
│   ├── offset
│   ├── gain
│   └── noise
│
├── Sampling
│   └── sampling rate
│
├── ADC Architecture
│   ├── multiplexer
│   ├── SAR
│   └── registers
│
├── Reference Voltage
│   ├── AREF
│   ├── AVCC
│   └── internal
│
└── ATmega128 ADC
    ├── ADCL
    ├── ADCH
    ├── prescaler
    └── interrupt
```

---

# 6. Test Your Understanding (5 Questions)

1️⃣ If an ADC has 10 bits and Vref = 5V, what is the LSB voltage?

2️⃣ Why must ADCL be read before ADCH?

3️⃣ What is the purpose of the ADC multiplexer?

4️⃣ Why does increasing sampling frequency reduce ADC accuracy?

5️⃣ Why are differential signals resistant to noise?

---

# 7. Oral Exam Simulation (Professor Style)

Imagine I am the professor.

**Question 1**

Explain the complete process from an analog signal entering the microcontroller until it becomes a digital value.

---

**Question 2**

What factors affect the accuracy of an ADC?

---

**Question 3**

Why is reference voltage stability important?

---

**Question 4**

What would happen if AVCC is noisy?

---

**Question 5**

Explain how a successive approximation ADC works.

---

# 8. One-Page Exam Cheat Sheet

## ADC Basics

```
ADC → converts analog voltage to digital number
```

---

## Resolution

```
levels = 2^N
```

Example:

```
10 bits → 1024 levels
```

---

## LSB

```
LSB = Vref / 2^N
```

Example:

```
5V / 1024 ≈ 4.88mV
```

---

## Sampling Rate

```
samples per second
```

Too fast →

```
conversion incomplete
precision loss
```

---

## ADC Architecture

```
Input
 ↓
Multiplexer
 ↓
Sample & Hold
 ↓
SAR
 ↓
Registers
```

---

## ATmega128 ADC

Resolution:

```
10 bits
```

Registers:

```
ADCL
ADCH
```

Read order:

```
ADCL → ADCH
```

---

## Reference Voltage

Options:

```
AREF
AVCC
Internal 1.1V
```

---

## Errors

```
offset
gain
nonlinearity
noise
quantization
```

---

# 9. Final Summary

## Key Concepts

* Analog to Digital Conversion
* Resolution and LSB
* Sampling rate
* Successive Approximation ADC
* Reference voltage
* Differential signals
* ADC registers in ATmega128

---

## Key Terminology

```
ADC
LSB
MSB
Vref
Sampling rate
Quantization
SAR
Multiplexer
Prescaler
```

---

## Typical Exam Traps

❌ Forgetting:

```
levels = 2^N
```

❌ Not reading:

```
ADCL before ADCH
```

❌ Ignoring Vref stability.

❌ Assuming ADC has perfect precision.

---

## Real-World Examples

ADC used in:

* temperature sensors
* motor control
* microphones
* battery monitoring
* biomedical sensors

---

✅ If you want, I can also do something **very useful for embedded exams**:

* build a **visual intuition diagram of the ATmega128 ADC**
* or give you the **10 questions professors love asking about ADCs**.

Both dramatically increase exam performance.
