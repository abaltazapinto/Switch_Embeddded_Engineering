# OSTEP — Parte II: Concurrency

## Cap. 26 — Concurrency: An Introduction


"In this note, we intriduce a new abstraction for a single running process: that of a thread. 
- the context switch between threads is quite similar to the context switch between processes, as the register state of T2 must be saved and the register state of T2 restored before running T2.Wit h processe, we saved state to a process control block (PCB); now, we ll need one or more thread control blocks (TCBs) to store the state of each thread of a process. There is one major difference though, in tee context switch we perform between threads as compared to processes: the address space remains the same (i.e there is no need to switch we perform between threads as compared to processes: the address space remains the same (i.e., there is no need to switch wich page table we are using). One other major difference between threads and processes concerns the stack.
![alt text](image.png)

A critical section is a piece of code that acesses a shared variable (or more gerally a shared resour ce)

### Pergunta central
O que muda quando duas ou mais threads executam dentro do mesmo processo?

### Hipótese inicial
Threads tornam o programa mais poderoso, mas introduzem bugs porque partilham memória e o scheduler pode interromper a execução em pontos imprevisíveis.

### Conceitos a extrair
- thread
- shared data
- uncontrolled scheduling
- atomicity
- waiting / synchronization

### Frase de engenharia
Se duas threads podem aceder ao mesmo estado, tenho de perguntar:
1. Quem lê?
2. Quem escreve?
3. Em que ordem?
4. Essa ordem é garantida?