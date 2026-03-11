Vou resumir **toda a aula sobre interrupções em microcontroladores AVR (ATmega128)** de forma que te ajude a perceber **como se programa numa board real** — porque essa foi exatamente a tua dificuldade.

Vou separar entre:

* **factos visíveis nos screenshots**
* **explicação de engenharia embebida (inferência)**

---

# 🧾 Key Concepts (conceitos principais)

### 1. Interrupções

**From the slides/screenshots**

* Interrupções permitem **resposta assíncrona a eventos**.
* Cada **periférico pode gerar interrupções**.
* Quando ocorre uma condição, **uma função é executada automaticamente**.
* No **ATmega128 existem várias fontes de interrupção**.
* Exemplo mencionado:

  * **Timer overflow**
  * **External interrupts**

**Inference / standard embedded knowledge**

Uma interrupção é um mecanismo onde:

1. Um evento acontece (ex: botão pressionado, timer terminou)
2. O CPU **interrompe o programa atual**
3. Salta para uma **Interrupt Service Routine (ISR)**
4. Executa essa função
5. Volta ao programa principal

---

### 2. Programação Sequencial vs Event-Driven

**From screenshots**

O professor explicou que num programa simples:

* Se fizeres **debouncing de alguns milissegundos**
* o programa pode **ficar bloqueado**

Problema:

```
delay(10ms)
```

Enquanto espera, **nada mais acontece**.

---

**Com interrupções**

O programa pode:

* continuar a executar
* responder a eventos imediatamente

---

### 3. Fontes de interrupção no ATmega128

**From slides**

Existem várias fontes de interrupção:

Exemplos citados:

* Timer overflow
* External interrupts
* Diferentes interrupções para cada periférico

---

### 4. Vetores de interrupção

**From slides**

Cada interrupção está **associada a um endereço de memória**.

Quando a interrupção acontece:

```
CPU → salta para esse endereço
```

Esse endereço contém a **rotina de interrupção**.

---

**Inference (standard AVR)**

Existe uma **Interrupt Vector Table** no início da memória Flash.

Exemplo típico (ATmega128):

```
0x0000 RESET
0x0002 INT0
0x0004 INT1
0x0006 TIMER2 COMP
...
```

Cada posição contém um **jump para a ISR**.

---

# 📚 Key Terminology

Termos que provavelmente aparecem no exame:

| Termo                           | Significado                                |
| ------------------------------- | ------------------------------------------ |
| Interrupt                       | evento assíncrono que interrompe o CPU     |
| ISR (Interrupt Service Routine) | função executada quando ocorre interrupção |
| Interrupt Vector                | endereço de memória da ISR                 |
| Timer Overflow                  | quando contador chega ao máximo            |
| External Interrupt              | interrupção causada por pino externo       |
| Peripheral                      | hardware interno (timer, UART, ADC)        |
| Event-driven programming        | programação baseada em eventos             |

---

# ⚠️ Typical Exam Traps

Professores adoram estas perguntas.

### 1️⃣ "Interrupções são síncronas ou assíncronas?"

Resposta correta:

➡️ **assíncronas**

---

### 2️⃣ "O que acontece quando ocorre uma interrupção?"

Ordem correta:

1. CPU termina instrução atual
2. Guarda contexto (PC normalmente)
3. Salta para **interrupt vector**
4. Executa ISR
5. Retorna

---

### 3️⃣ "Porque usar interrupções?"

Resposta:

* evita **busy waiting**
* melhora **tempo de resposta**
* permite **concorrência simples**

---

### 4️⃣ "Problema comum nas ISR?"

Resposta clássica:

* ISR muito longas
* usar delays
* usar printf
* acesso a variáveis sem `volatile`

---

### 5️⃣ "Qual é a desvantagem das interrupções?"

* complexidade
* race conditions
* debug difícil

---

# 🧠 Como realmente funciona numa board (modelo mental)

Imagina este programa numa board AVR.

```
main()
{
    init_timer();
    init_button_interrupt();

    while(1)
    {
        control_motor();
        read_sensors();
    }
}
```

Enquanto o programa corre:

```
CPU executa main loop
```

Se o botão for pressionado:

```
Botão → gera interrupção
      → CPU pausa main
      → executa ISR
      → volta ao main
```

Fluxo real:

```
MAIN LOOP
   ↓
   ↓
[interrupt occurs]
   ↓
ISR runs
   ↓
return
   ↓
MAIN LOOP continues
```

---

# 🔧 Exemplo real (ATmega)

Botão que gera interrupção.

```c
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
    PORTB ^= (1<<PB0); // toggle LED
}

int main(void)
{
    DDRB |= (1<<PB0);   // LED output

    EIMSK |= (1<<INT0); // enable INT0
    EICRA |= (1<<ISC01); // falling edge

    sei(); // enable global interrupts

    while(1)
    {
        // main loop
    }
}
```

Quando pressionas o botão:

```
INT0 → ISR → LED muda
```

---

# 🌍 Real World Examples

Interrupções são usadas em:

### Robótica

sensor detecta obstáculo

→ interrupção
→ parar motor imediatamente

---

### Comunicação UART

quando chega um byte

→ interrupção
→ guardar byte no buffer

---

### Sistemas operativos

Linux usa interrupções para:

* teclado
* disco
* rede

---

### Sistemas de tempo real

timer gera interrupção a cada:

```
1 ms
```

para controlar tarefas.

---

# 🎓 5 perguntas tipo professor (oral exam)

Responde sem olhar 👀

---

**1️⃣ O que é uma interrupção num microcontrolador?**

---

**2️⃣ Qual é a diferença entre polling e interrupt driven programming?**

---

**3️⃣ O que acontece dentro do CPU quando ocorre uma interrupção?**

---

**4️⃣ Porque não devemos colocar código longo numa ISR?**

---

**5️⃣ O que é um interrupt vector?**

---

# 🧠 Pergunta importante para perceber se entendeste

Se tens isto:

```
while(1)
{
   read_sensor();
}
```

e um botão com interrupção.

Pergunta:

👉 O que acontece ao `while` quando o botão é pressionado?

---

# 📄 One-page exam cheat sheet

### Interrupt Flow

```
Event
 ↓
Interrupt flag
 ↓
CPU stops main
 ↓
Jump to vector
 ↓
ISR executes
 ↓
Return (RETI)
 ↓
Main continues
```

---

### Program structure

```
init peripherals
enable interrupts
main loop
```

---

### AVR basics

* `sei()` → enable interrupts
* `cli()` → disable interrupts
* `ISR(vector)` → interrupt function

---

### Rules

✔ ISR must be **short**
✔ avoid delays
✔ shared variables → `volatile`

---

# ❓ Ambiguities / verify

Pelos screenshots não ficou totalmente claro:

* lista completa de **interrupt sources do ATmega128**
* exemplo concreto de **external interrupt configuration**
* diagrama completo da **interrupt vector table**

Algumas imagens parecem conter isso mas **o texto não está legível**.

---

✅ **Boa notícia:**
Se achaste esta aula confusa, é **normal**. Interrupções são normalmente o **primeiro grande salto mental em embedded**.

---

Se quiseres, posso também explicar:

1️⃣ **Como se programa uma board AVR do zero (passo-a-passo)**
2️⃣ **O que realmente acontece dentro do microcontrolador quando uma interrupção dispara**
3️⃣ **O exemplo mais clássico que sai em exames (Timer interrupt)**

Posso também fazer um **guia visual que faz tudo “clicar” em 5 minutos.**



Perfeito — **os slides ajudam muito**. Vou resumir **a aula inteira (microcontroladores + interrupções + timers)** usando **apenas o que está nos slides** e explicando o que precisas para realmente perceber a programação numa board AVR.

Fonte:

---

# 🧾 Extracted from the slides

### Arquitetura ATmega128

* CPU RISC 8-bit
* 133 instruções
* Até **16 MIPS a 16 MHz**
* 32 registos auxiliares
* Registos importantes:

  * STATUS register
  * Program Counter
  * Stack Pointer

---

### Memória

**Program memory**

* 128 KB Flash
* cada endereço = **16 bits word**

**Data memory**

* espaço de **64 KB**
* endereçamento de **16 bits**

**SRAM interna**

* 4 KB

**EEPROM**

* 4 KB
* pelo menos **100000 ciclos write/erase**

---

### Periféricos

* 53 pinos I/O
* 4 timers
* 2 USART
* ADC 10-bit

---

### Arquitetura

ATmega128 usa **Harvard architecture**

Significa:

```
Program memory
     |
     | separate bus
     |
CPU ---- Data memory
```

Código e dados **em memórias separadas**.

---

# I/O PORTS

Cada porto tem **3 registos**

| Register | Função                         |
| -------- | ------------------------------ |
| DDRx     | define input ou output         |
| PORTx    | escreve valor ou ativa pull-up |
| PINx     | lê valor do pino               |

Exemplo:

```
DDRB |= (1<<PB0)
```

→ PB0 passa a **output**.

---

### Pull-up resistor

Problema:

se um pino input não tiver nada ligado → **floating**

ruído elétrico pode mudar o valor.

Solução:

```
pull-up resistor
```

faz o pino assumir **valor lógico 1**.

---

# Bitwise operations

Usadas constantemente em embedded.

| Operador | Uso        |
| -------- | ---------- |
| |        | set bit    |
| &        | clear bit  |
| ^        | toggle bit |

Exemplo:

```
a |= (1 << 2)
```

→ ativa bit 2.

---

# 🧠 INTERRUPTS

## Objetivo das interrupções

Responder a eventos **sem polling constante**.

Em vez de:

```
while(1)
{
  check_button();
}
```

faz:

```
button interrupt
```

CPU reage **automaticamente**.

---

## Interrupt sources

ATmega128 tem muitas fontes:

* 8 external interrupts
* timers
* USART
* ADC
* SPI
* I2C
* EEPROM

---

## Interrupt vectors

Cada interrupção tem **um endereço fixo na memória**.

Quando ocorre:

```
CPU jump → interrupt vector
```

Esse endereço contém:

```
jump → ISR
```

(Interrupt Service Routine)

---

## Se duas interrupções ocorrerem

Prioridade:

```
menor endereço do vetor
```

é executado primeiro.

---

# External interrupts

8 interrupções externas.

Mapeamento:

```
INT3..0 → PORTD
INT7..4 → PORTE
```

Podem disparar em:

* rising edge
* falling edge
* low level

---

# Configurar interrupção

Passos:

1️⃣ Desativar interrupção

```
EIMSK
```

2️⃣ Configurar tipo de trigger

```
EICRA / EICRB
```

3️⃣ Limpar flag

```
EIFR
```

4️⃣ Ativar interrupção

```
EIMSK
```

5️⃣ Ativar global interrupts

```
sei()
```



---

# ISR em C

```c
#include <avr/interrupt.h>

ISR(INT0_vect)
{
}
```

`ISR()` define a rotina de interrupção.

---

# Problema importante: volatile

Se variável for usada em ISR:

```
volatile
```

senão o compilador pode **otimizar errado**.

Exemplo do slide:

```c
volatile int my_flag = 0;

ISR(INT0_vect){
 my_flag = 1;
}

while(!my_flag);
```



---

# Timers

ATmega128 tem:

* Timer0 (8 bit)
* Timer2 (8 bit)
* Timer1 (16 bit)
* Timer3 (16 bit)

---

## Timer0 registers

| Register | Função       |
| -------- | ------------ |
| TCNT0    | contador     |
| OCR0     | comparação   |
| TCCR0    | configuração |

---

## Timer overflow

Quando contador chega ao máximo:

```
0xFF → 0x00
```

flag:

```
TOV0
```

pode gerar interrupção.

---

# CTC Mode

Timer reset quando:

```
TCNT0 == OCR0
```

tempo:

```
T = Prescaler / CLK * (OCR0 + 1)
```



---

# Busy wait delay

```
_delay_ms()
```

Problemas:

* CPU fica bloqueado
* não poupa energia
* depende de `F_CPU`

---

# ⚠️ Typical exam traps

### 1️⃣ int size

No AVR:

```
int = 16 bits
```

não 32.

---

### 2️⃣ double

```
double = 4 bytes
```

igual a float.

---

### 3️⃣ Interrupt variables

Devem ser

```
volatile
```

---

### 4️⃣ ISR

Deve ser **curta**.

---

### 5️⃣ Nem todas as instruções C são atómicas

exemplo:

```
counter++
```

vira várias instruções assembly.

---

# 🌍 Real world examples

### Botão

```
external interrupt
```

---

### Comunicação serial

```
USART interrupt
```

quando chega um byte.

---

### Sistema tempo real

```
timer interrupt
```

executa tarefa a cada:

```
1 ms
```

---

# 🧠 Mental model (o mais importante)

Como tudo se liga:

```
        PROGRAM MEMORY
              |
              |
             CPU
              |
      -----------------
      |       |       |
    TIMER    I/O    USART
      |
      |
   INTERRUPT
      |
      ↓
      ISR
```

---

# 🃏 Flashcards

**1**

Q: O que é uma interrupção?
A: Evento que interrompe o CPU e executa ISR.

---

**2**

Q: O que é ISR?
A: Interrupt Service Routine.

---

**3**

Q: Quantos timers tem o ATmega128?
A: 4 timers.

---

**4**

Q: Para que serve DDRx?
A: Definir input ou output.

---

**5**

Q: Para que serve volatile?
A: Evitar otimizações erradas em variáveis usadas em interrupções.

---

**6**

Q: O que é CTC mode?
A: Timer reset quando TCNT == OCR.

---

**7**

Q: Qual o tamanho de int no AVR?
A: 16 bits.

---

# 🧪 Exercises

### 1️⃣ Conceptual

Qual a vantagem de usar **interrupts em vez de polling**?

---

### 2️⃣ Código

Faz LED PB0 ligar quando botão PD2 é pressionado.

---

### 3️⃣ Debugging

Porque este código não funciona?

```
int flag = 0;

ISR(INT0_vect){
 flag = 1;
}

while(!flag);
```

---

### 4️⃣ Exam question

Explique o funcionamento de um **interrupt vector** na arquitetura AVR.

---

# ✅ Checklist para dominar esta aula

Se consegues explicar:

* Harvard architecture
* DDR / PORT / PIN
* pull-up resistor
* interrupts
* ISR
* volatile
* timers
* prescaler

então já dominas **90% da aula**.

---

💡 Se quiseres, posso ainda mostrar:

* **A forma mais fácil de entender programação AVR (com 1 exemplo real)**
* **o exemplo clássico que sai sempre em exame**
* **como um programa embedded realmente corre dentro do microcontrolador** (isto costuma ser o momento “aha”).
