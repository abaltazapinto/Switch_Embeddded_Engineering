Ação (1 passo): Criar uma **exam cheat-sheet de 1 página sobre Interrupts, ISR e Stack no AVR (ATmega / Arduino Uno)** baseada na aula.

Objetivo: Consolidar rapidamente os conceitos essenciais da aula para estudo e preparação de exame, garantindo que entendes **interrupções, vetores de interrupção, ISR e o papel da stack** no microcontrolador.

Output gerado: **Cheat-sheet técnico resumido** + **problema prático em Arduino** para testar compreensão.

---

# AVR Interrupts – One-Page Exam Cheat Sheet (ATmega / Arduino Uno)

## 1️⃣ Key Concepts

### Interrupt

Evento **assíncrono** que interrompe o fluxo normal do programa.

Fluxo normal:

```
main() loop
   ↓
evento ocorre
   ↓
CPU pausa execução
   ↓
salta para ISR
   ↓
ISR termina
   ↓
CPU retorna ao ponto anterior
```

Usado para responder rapidamente a eventos como:

* botão pressionado
* timer overflow
* comunicação serial
* ADC ready

---

### Interrupt Vector Table

Cada interrupção está associada a um **endereço fixo de memória**.

Quando ocorre uma interrupção:

```
CPU → consulta vector table
    → salta para ISR correspondente
```

Exemplo conceptual:

```
0x0000 RESET
0x0002 INT0
0x0004 INT1
0x0006 TIMER0_OVF
...
```

---

### ISR (Interrupt Service Routine)

Função executada quando ocorre a interrupção.

Exemplo Arduino:

```cpp
ISR(INT0_vect)
{
    // código executado quando INT0 dispara
}
```

Regras importantes:

* deve ser **curta**
* **não usar delays**
* **evitar cálculos pesados**

---

### Stack (fundamental para interrupts)

Quando uma interrupção ocorre:

CPU automaticamente:

```
1 push PC (Program Counter) na stack
2 salta para ISR
```

Quando ISR termina:

```
reti
↓
pop PC da stack
↓
continua execução
```

Se a stack estiver corrompida → crash do programa.

---

### Enabling interrupts

Para que as interrupções funcionem:

1️⃣ habilitar global interrupts

```
sei();
```

2️⃣ habilitar interrupt específico

```
EIMSK |= (1 << INT0);
```

---

### External Interrupt Example

Arduino UNO (ATmega328P):

```
INT0 → pin 2
INT1 → pin 3
```

Trigger types:

```
LOW level
any change
falling edge
rising edge
```

---

## 2️⃣ Key Terminology

| Term            | Meaning                             |
| --------------- | ----------------------------------- |
| Interrupt       | evento assíncrono                   |
| ISR             | Interrupt Service Routine           |
| Vector Table    | tabela de saltos para ISR           |
| Stack           | memória usada para guardar contexto |
| Program Counter | endereço da próxima instrução       |
| sei()           | enable global interrupts            |
| cli()           | disable global interrupts           |
| reti            | return from interrupt               |

---

## 3️⃣ Typical Exam Traps ⚠️

### Trap 1

Pensar que ISR é chamada como função normal.

❌ errado
ISR é chamada **automaticamente pelo hardware**

---

### Trap 2

Usar delay dentro de ISR

```
delay()
Serial.print()
```

❌ pode bloquear o sistema

---

### Trap 3

Esquecer `volatile`

Variáveis partilhadas entre ISR e main:

```cpp
volatile int counter;
```

---

### Trap 4

Stack overflow

ISR profunda + recursão → corrupção da stack.

---

## 4️⃣ Real World Examples

### Debouncing buttons

Em vez de polling:

```
loop() {
   check_button();
}
```

usar interrupt.

---

### Motor control

Encoder gera interrupt a cada pulso.

---

### Real-time systems

Timer interrupt executa código:

```
1ms scheduler
```

---

### Communication

UART receive interrupt.

---

# Arduino Problem (Test your understanding)

Arduino UNO + botão no pin 2.

Objetivo:

Cada vez que pressionares o botão:

* ISR incrementa contador
* loop imprime contador

### Incomplete code

Completa:

```cpp
volatile int counter = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(2, INPUT_PULLUP);

    // attach interrupt
    attachInterrupt(_____, isr_button, _____);
}

void loop()
{
    Serial.println(counter);
    delay(500);
}

void isr_button()
{
    counter++;
}
```

Perguntas:

1️⃣ Qual interrupt number corresponde ao **pin 2** no Arduino UNO?
2️⃣ Qual trigger usar para evitar múltiplos triggers?
3️⃣ Porque `counter` precisa de `volatile`?
4️⃣ O que acontece na **stack** quando ocorre a interrupção?
5️⃣ Porque ISR deve ser curta?

---

## 🎓 Oral Exam Questions (Professor Style)

1️⃣ Explique a diferença entre **polling e interrupt driven programming**.

2️⃣ O que acontece internamente na CPU quando ocorre uma interrupção?

3️⃣ Qual o papel da **stack numa ISR**?

4️⃣ Porque não devemos usar `delay()` numa ISR?

5️⃣ O que acontece se ocorrer uma interrupção enquanto outra ISR está a correr?

---

## 💡 Quick Mental Model

```
Evento → Interrupt → Vector table → ISR → RETI → programa continua
```

---

Pitfalls & troubleshooting:

* ISR longa causa **latência em outras interrupções**
* esquecer `volatile` causa **bugs difíceis**
* uso excessivo de interrupts pode degradar desempenho
* stack pequena em microcontroladores pode causar **crash**

---

Alternativas / tradeoffs:

Interrupts vs polling:

| Polling    | Interrupt      |
| ---------- | -------------- |
| simple     | mais eficiente |
| CPU waste  | event-driven   |
| previsível | mais complexo  |

---

Pergunta de decisão (1):

Queres que eu também crie **um exercício realista de exame com debugging de ISR (tipo problema clássico de embedded systems)** usando **ATmega registers em vez de Arduino abstractions**? Isso normalmente aparece muito em exames.



## Perfeito — os slides ajudam bastante. Vou condensar **toda a aula** para estudo rápido e depois testar-te como num exame. Tudo baseado no PDF que enviaste.
### (Referência ao documento: )

---

# 📚 Aula – Embedded Systems (ATmega / AVR) — Resumo completo

## 1️⃣ Key Concepts

### Microcontroller Architecture

O **ATmega (AVR)** é um microcontrolador de **8 bits com arquitetura Harvard**.

Características principais:

* CPU RISC
* 32 registers de propósito geral
* Program Counter (PC)
* Stack Pointer (SP)
* memória separada para **programa e dados**

Harvard architecture:

```
Program Memory (Flash)
        │
        │
       CPU
        │
        │
Data Memory (SRAM / IO / EEPROM)
```

---

# 2️⃣ Memory Types

### Program Memory

* Flash
* instruções de **16 ou 32 bits**
* cada endereço = **word de 16 bits**

---

### Data Memory

Endereçamento:

```
16 bits address space
→ 64 KB
```

Contém:

```
Registers
I/O registers
Internal SRAM
External SRAM
```

Se a **stack estiver em external SRAM** → cada acesso custa mais ciclos.

---

### EEPROM

Memória não volátil:

* 4 KB
* ~100000 write cycles

Usada para:

* configurações
* calibração
* parâmetros persistentes

---

# 3️⃣ I/O Ports

ATmega128 tem **53 pinos I/O** organizados em ports.

Exemplo:

```
PORTA
PORTB
PORTC
PORTD
PORTE
PORTF
PORTG
```

Cada pin pode ser:

```
INPUT
OUTPUT
ALTERNATE FUNCTION
```

---

# 4️⃣ I/O Registers

Cada port tem **3 registers**:

| Register | Função                          |
| -------- | ------------------------------- |
| DDRx     | define input/output             |
| PORTx    | escreve output ou ativa pull-up |
| PINx     | lê estado do pin                |



---

### Exemplo

Output:

```
DDRB |= (1 << PB0);
PORTB |= (1 << PB0);
```

Input com pull-up:

```
DDRB &= ~(1 << PB0);
PORTB |= (1 << PB0);
```

---

# 5️⃣ Pull-Up Resistor

Problema:

```
floating input
```

Sem resistor → ruído elétrico.

Pull-up:

```
Vcc
 │
 R
 │
 PIN
 │
Switch
 │
GND
```

Se botão aberto → 1
Se botão fechado → 0

---

# 6️⃣ Bitwise Operations (ESSENCIAL PARA EXAME)

Set bit:

```
a |= (1 << n)
```

Clear bit:

```
a &= ~(1 << n)
```

Toggle bit:

```
a ^= (1 << n)
```



---

# 7️⃣ Interrupts

Interrupt = evento que interrompe o fluxo normal.

Fontes possíveis:

* external interrupts
* timers
* USART
* ADC
* SPI
* I2C
* EEPROM



---

### Interrupt Vector Table

Cada interrupt tem um **endereço fixo**.

CPU faz:

```
interrupt
↓
vector table
↓
ISR
```

Se dois interrupts ocorrem:

```
menor endereço → maior prioridade
```



---

# 8️⃣ External Interrupts

Exemplo:

```
INT0
INT1
INT2
...
```

Trigger types:

```
LOW level
Rising edge
Falling edge
```



---

# 9️⃣ Interrupt Service Routine

Definida em C:

```c
#include <avr/interrupt.h>

ISR(INT0_vect)
{
}
```



---

# 🔟 Global Interrupt Enable

Bit **GIE** no **SREG**.

Funções da AVR libc:

```
sei()  → enable interrupts
cli()  → disable interrupts
```

Quando interrupt ocorre:

```
GIE = 0
```

Quando ISR termina (`RETI`):

```
GIE = 1
```



---

# 11️⃣ volatile (muito importante)

Sem `volatile`, o compilador pode otimizar.

Exemplo:

```
while(!flag);
```

Se `flag` for alterado na ISR → programa pode não ver.

Correção:

```c
volatile int flag;
```



---

# 12️⃣ Timers

Tipos no ATmega128:

```
Timer0 → 8-bit
Timer1 → 16-bit
Timer2 → 8-bit
Timer3 → 16-bit
```



---

# 13️⃣ Timer Registers

Principais:

```
TCNTx → counter
TCCRx → configuration
OCRx → compare register
```

---

# 14️⃣ Timer Modes

### Normal Mode

Counter:

```
0 → 255 → overflow
```

Overflow gera:

```
TOV0 flag
```



---

### CTC Mode

Clear Timer on Compare.

```
TCNT == OCR
↓
reset counter
```



---

### PWM

Geração de waveform.

Usado para:

```
motor control
LED brightness
servo control
```

---

# ⚠️ Typical Exam Traps

### Trap 1

Confundir:

```
PORTx
DDRx
PINx
```

---

### Trap 2

Usar:

```
counter++
```

sem proteger contra interrupt.

Porque **não é atomic**.

---

### Trap 3

Esquecer `volatile`.

---

### Trap 4

Não limpar interrupt flag.

---

### Trap 5

Usar delay em sistemas real-time.

---

# 🌍 Real World Examples

### Encoder

Interrupt a cada pulso.

---

### PWM motor control

Timer gera PWM.

---

### Serial communication

USART interrupt.

---

### Periodic tasks

Timer interrupt:

```
1ms scheduler
```

---

# 🎓 Teste de compreensão (tipo exame)

### Pergunta 1

Qual a diferença entre:

```
DDRx
PORTx
PINx
```

---

### Pergunta 2

O que faz esta instrução?

```
PORTB |= (1 << PB3);
```

---

### Pergunta 3

Porque variáveis usadas numa ISR devem ser `volatile`?

---

### Pergunta 4

Explique a diferença entre:

```
Timer normal mode
CTC mode
```

---

### Pergunta 5

Porque `counter++` não é atomic num microcontrolador AVR?

---

# 🧠 Exercício Arduino (nível exame)

Implementar:

```
Botão → PD2
LED → PB0
```

Requisitos:

Sempre que houver **falling edge no botão**:

```
LED toggle
```

Usar **interrupt INT2**.

Completa o código:

```c
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
    DDRB |= (1 << PB0);

    PORTD |= (1 << PD2);

    EICRA |= (1 << ______);

    EIMSK |= (1 << ______);

    sei();

    while(1)
    {

    }
}

ISR(_______)
{
    PORTB ^= (1 << PB0);
}
```

---

# Pergunta rápida para testar se percebeste a aula

Se o professor perguntar:

> "Why should Interrupt Service Routines be short?"

Qual seria a tua resposta?

---

Se quiseres, no próximo passo posso também fazer algo **extremamente útil para o teu curso**:

1️⃣ **explicar visualmente stack + ISR no AVR (muito perguntado em exames)**
2️⃣ **dar-te 3 problemas reais de exame de embedded systems**
3️⃣ **ensinar a ler o disassembly de ISR (aparece nos slides no final)**

Qual queres?
