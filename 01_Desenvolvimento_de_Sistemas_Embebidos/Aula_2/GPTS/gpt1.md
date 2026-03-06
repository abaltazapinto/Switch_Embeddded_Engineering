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
