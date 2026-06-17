# Resumo Final — PRASIE LAB1: POSIX Threads 🧵

## Ação — 1 passo

Copia este resumo para o teu caderno como **mapa mental do LAB1**. Não é só para entregar; é para conseguires explicar o laboratório oralmente.

---

# 1. Ideia central do LAB

O LAB1 introduz programação com **POSIX Threads**. O objetivo é perceber como várias threads executam dentro do mesmo processo, como se criam, como se espera por elas, como se passam argumentos, e o que acontece quando várias threads acedem à mesma memória sem sincronização. O guia apresenta as funções principais: `pthread_create()`, `pthread_exit()`, `pthread_join()`, `pthread_self()` e `pthread_equal()`. 

Modelo mental:

```text
Processo
│
├── main thread
├── worker thread 1
├── worker thread 2
└── worker thread 3
```

As threads têm fluxos de execução diferentes, mas partilham o mesmo espaço de memória.

---

# 2. Funções principais

## `pthread_create()`

Cria uma nova thread.

```c
pthread_create(&thread_id, NULL, worker_function, arg);
```

Pensar assim:

```text
Cria uma nova linha de execução.
Guarda o identificador em thread_id.
Começa a executar em worker_function.
Passa arg como argumento.
```

Importante:

```text
pthread_create() cria a thread, mas não espera por ela.
```

---

## `pthread_join()`

Espera que uma thread termine.

```c
pthread_join(thread_id, NULL);
```

Pensar assim:

```text
Main, fica parada aqui até esta thread acabar.
```

Importante:

```text
pthread_join() não protege dados.
pthread_join() só espera pelo fim da thread.
```

---

## `pthread_self()`

A thread pergunta:

```text
Qual é o meu identificador?
```

Usaste isto para imprimir o ID da worker.

---

## `pthread_exit(NULL)`

Termina apenas a thread chamadora.

No exercício 3.4, isto foi importante porque a `main` devia terminar imediatamente sem matar as outras threads.

```c
pthread_exit(NULL);
```

Diferença crítica:

```text
return 0 na main      → pode terminar o processo inteiro
pthread_exit(NULL)    → termina só a main thread
```

---

# 3. Exercício 3.1 — Thread Identification

O enunciado pediu criar 5 worker threads, cada uma imprimindo `"hello"` com `pthread_self()`, enquanto a main imprimia o ID da thread criada e depois esperava por todas antes de imprimir `"goodbye"`. 

## Descoberta principal

```text
Ordem de criação ≠ ordem de execução
```

A main cria as threads numa ordem, mas o scheduler decide quando cada thread corre.

Exemplo observado:

```text
hello from worker thread: X
main created thread: X
```

Isto é válido porque, logo após `pthread_create()`, a worker pode correr antes da main fazer o próximo `printf()`.

## Conclusão

```text
The output order is not deterministic because thread scheduling is controlled by the operating system.
pthread_join() ensures that main waits for all worker threads before printing goodbye.
Without pthread_join(), main can finish before all workers complete.
```

---

# 4. Exercício 3.2 — Loop Index Pitfall

O enunciado pediu primeiro passar `&i` diretamente, depois corrigir com um array local, e finalmente usar um array `static global`. 

---

## 3.2.1 — Versão errada: passar `&i`

Código perigoso:

```c
pthread_create(&threads[i], NULL, worker, &i);
```

Problema:

```text
Todas as threads recebem o mesmo endereço: &i.
```

Logo:

```text
worker 0 → &i
worker 1 → &i
worker 2 → &i
worker 3 → &i
worker 4 → &i
```

Como a main continua a alterar `i`, cada worker pode ler valores repetidos ou inesperados.

Conclusão:

```text
Passing &i is unsafe because all worker threads share the same memory location.
The value read depends on when the scheduler allows each worker to run.
```

---

## 3.2.2 — Correção com array local

Código correto:

```c
int values[NTHREADS];

values[i] = i;
pthread_create(&threads[i], NULL, worker, &values[i]);
```

Agora:

```text
worker 0 → &values[0]
worker 1 → &values[1]
worker 2 → &values[2]
worker 3 → &values[3]
worker 4 → &values[4]
```

Conclusão:

```text
Each thread receives a different memory address, so each worker reads a stable value.
The order may still change, but the values should be 0, 1, 2, 3, and 4.
```

Importante:

```text
O array local é seguro aqui porque a main faz pthread_join() antes de terminar.
```

---

## 3.2.3 — Array `static global`

Código:

```c
static int values[NTHREADS];
```

Vantagem:

```text
A memória existe durante toda a vida do programa.
Não depende da stack da main.
```

Desvantagem:

```text
Reduz isolamento de dados.
Mais funções/threads podem aceder ao mesmo estado global.
Pode facilitar race conditions se houver escrita concorrente.
```

Conclusão:

```text
Static global improves lifetime, but weakens data isolation.
In embedded systems, globals can be acceptable, but should be justified and controlled.
```

---

# 5. Exercício 3.3 — Structure Encapsulation

O enunciado pediu passar vários parâmetros para cada thread usando uma `struct`: índice de entrada, índice de saída, valor a somar e delay. Também pediu um `shared_array` global de 3 inteiros iniciado a zero. 

## Struct usada

```c
typedef struct s_thread_config
{
    int input_index;
    int output_index;
    int value_to_add;
    int delay_seconds;
} t_thread_config;
```

Modelo mental:

```text
A struct é a configuração da thread.
```

Cada worker sabe:

```text
De onde lê?
Para onde escreve?
Quanto soma?
Quanto tempo espera?
```

---

## Shared state

```c
static int shared_array[3] = {0, 0, 0};
```

Cada worker faz em loop:

```text
1. lê shared_array[input_index]
2. mete shared_array[input_index] = 0
3. escreve shared_array[output_index] = valor_lido + constante
4. espera delay_seconds
```

A main imprime o array a cada segundo.

Conclusão:

```text
This exercise shows how to pass multiple arguments to a thread using a struct.
It also introduces shared state between periodic worker threads.
The output changes over time because workers concurrently read and write the same shared array.
```

---

# 6. Exercício 3.4 — Monitoring and Alert Systems

O enunciado pediu duas threads: uma sensor thread que altera um valor global e uma monitor thread que observa esse valor. O valor inicial devia ser `20`. O sensor soma um valor aleatório entre `-3` e `3` e dorme entre 1 e 5 segundos. O monitor verifica o valor a cada segundo e imprime alertas se sair da gama segura. 

## Arquitetura

```text
sensor thread  → modifica system_value
monitor thread → observa system_value
main thread    → cria as duas e termina com pthread_exit(NULL)
```

## Sensor

```text
delta = -3..+3
system_value += delta
sleep = 1..5 seconds
```

## Monitor

```text
system_value > 35 → WARNING: OVERHEATING DETECTED
system_value < 0  → ALERT: FREEZING HAZARD
3 consecutive alerts → CRITICAL SYSTEM FAILURE
safe range 0..35 → reset alert counter
```

Conclusão:

```text
The sensor modifies shared state.
The monitor observes shared state and keeps internal memory using a consecutive alert counter.
The critical alert persists while the system remains outside the safe range.
```

Importante:

```text
pthread_exit(NULL) na main permite que sensor e monitor continuem vivos.
```

---

# 7. Section 4 — Race Conditions

Esta secção mostrou o problema central de concorrência:

```text
Shared memory + unsynchronised access = non-deterministic behaviour/data corruption
```

O guia pede investigar corrupção de dados quando múltiplas threads acedem à mesma memória sem sincronização. 

---

## Problem 1 — Counter Race Condition

Código perigoso:

```c
counter++;
```

Parece uma operação simples, mas na prática é:

```text
1. read counter
2. add 1
3. write counter
```

Com 3 threads, cada uma a incrementar 100000 vezes:

```text
expected = 3 * 100000 = 300000
```

Mas sem mutex obtiveste valores menores, como:

```text
111618
112988
140408
109531
```

Isto aconteceu por **lost updates**.

Exemplo:

```text
counter = 10

thread A lê 10
thread B lê 10
thread A escreve 11
thread B escreve 11

Resultado: 11
Devia ser: 12
```

---

## Correção com mutex

```c
pthread_mutex_lock(&counter_mutex);
counter++;
pthread_mutex_unlock(&counter_mutex);
```

Conclusão:

```text
The mutex protects the critical section.
Only one thread can execute counter++ at a time.
The final counter becomes deterministic and consistently reaches 300000.
```

---

# 8. Problem 2 — Lost Update com `balance`

O enunciado pediu:

```text
balance = 1000
depositor: +100, 500 times
withdrawer: -100, 500 times
usleep(100) between read and write
```

Valor esperado:

```text
1000 + 50000 - 50000 = 1000
```

Sem mutex, observaste:

```text
51000
-49000
-49000
```

Isto mostra que uma thread estava a sobrescrever o trabalho da outra.

---

## Zona perigosa

```c
local_balance = balance;
usleep(100);
balance = local_balance + AMOUNT;
```

Problema:

```text
A thread lê o saldo.
Depois dorme.
Durante esse tempo, outra thread altera o saldo.
Quando a primeira acorda, escreve com base num valor antigo.
```

Isto é **lost update**.

---

## Correção com mutex

A zona inteira tem de ser protegida:

```c
pthread_mutex_lock(&balance_mutex);

local_balance = balance;
usleep(100);
balance = local_balance + AMOUNT;

pthread_mutex_unlock(&balance_mutex);
```

Conclusão:

```text
The mutex protects the full read → delay → write sequence.
No updates are lost.
The final balance consistently returns to 1000.
```

---

# 9. Diferença entre `join` e `mutex`

Isto é fundamental:

| Conceito               | Serve para quê?               | Não faz o quê?               |
| ---------------------- | ----------------------------- | ---------------------------- |
| `pthread_join()`       | Esperar uma thread terminar   | Não protege dados            |
| `pthread_mutex_lock()` | Proteger uma critical section | Não espera a thread terminar |
| `pthread_exit()`       | Terminar só a thread atual    | Não sincroniza dados         |
| `sleep/usleep()`       | Simular tempo/delay           | Não sincroniza corretamente  |

Resumo forte:

```text
join controla lifetime.
mutex controla acesso a shared state.
```

---

# 10. Conceitos finais que tens de saber explicar

## Thread

```text
Fluxo de execução dentro de um processo.
```

## Shared memory

```text
Memória visível por várias threads do mesmo processo.
```

## Scheduler

```text
Componente do sistema operativo que decide que thread corre em cada momento.
```

## Non-determinism

```text
O mesmo programa pode produzir outputs diferentes entre execuções.
```

## Race condition

```text
Bug em que o resultado depende da ordem/timing de execução das threads.
```

## Critical section

```text
Região do código que acede a dados partilhados e precisa de proteção.
```

## Mutex

```text
Mecanismo que garante exclusão mútua: só uma thread entra na critical section de cada vez.
```

---

# 11. Pitfalls gerais do LAB

1. **Passar `&i` para threads**

   ```text
   Todas recebem o mesmo endereço.
   ```

2. **Achar que `pthread_join()` resolve race conditions**

   ```text
   Não resolve. Só espera pelo fim.
   ```

3. **Achar que `counter++` é atómico**

   ```text
   Não é. É read-modify-write.
   ```

4. **Usar global state sem pensar**

   ```text
   Facilita partilha, mas reduz isolamento.
   ```

5. **Comentar o bloco errado**

   ```text
   Exemplo: comentar pthread_create e deixar pthread_join ativo causou bloqueio.
   ```

6. **Esquecer que `while(1)` nunca termina**

   ```text
   Se fizeres join numa thread infinita, a main bloqueia para sempre.
   ```

---

# 12. Resumo final em inglês para relatório

```text
In this lab, I learned how to create and manage POSIX threads using pthread_create(),
pthread_join(), pthread_self(), and pthread_exit().

I observed that thread execution order is non-deterministic because scheduling is controlled
by the operating system. Creating threads in a given order does not guarantee that they will
execute or print in that same order.

I also studied a common argument-passing bug: passing &i to multiple threads. Since all
threads receive the same memory address, they may read unexpected or repeated values.
Using an array fixes this by giving each thread a different memory location. A static global
array increases lifetime but reduces data isolation.

Using structures, I passed multiple parameters to each thread, including input index, output
index, value to add, and delay. This allowed each thread to behave like a configurable
periodic task operating on shared state.

The monitoring exercise showed a sensor thread modifying a global value and a monitor
thread observing it and raising warnings, alerts, and critical messages based on thresholds
and consecutive unsafe readings.

Finally, I investigated race conditions. The counter example showed that counter++ is not
atomic and can lose updates when accessed by multiple threads. The balance example showed
a lost update caused by context switches between read and write operations. Protecting the
critical sections with pthread_mutex_t made the results deterministic and correct.
```

---

## Pergunta de decisão

Queres transformar este resumo numa versão **mais curta para entregar como relatório**, ou numa versão **tipo folha de estudo para o teste/quizz**?
