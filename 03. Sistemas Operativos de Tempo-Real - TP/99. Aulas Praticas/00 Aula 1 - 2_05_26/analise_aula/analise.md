Tema	Onde aparece na PL1	Livro/PDF relacionado	O que precisas perceber

    RM scheduling	Exercício 1	Embedded Systems / RTOS	prioridades fixas

    EDF	Exercícios 2–4	RTOS scheduling	deadlines dinâmicas

    PIP / ICPP	Exercício 5	Synchronization	priority inversion
    
    Periodic tasks	Parte OS	Linux scheduling	períodos e deadlines
    
    Semaphores	ex3/ex4/ex5	synchronization	exclusão mútua---

    A PL! estas a ligar tres niveis diferentes. 

        - Teoria do scheduling
        - Implementacao em SO/Linux
        - Problemas reais de concorrencia

A maior dificudade em RTOS normalmente Nao e a matematica.
E perceber:
    - o modelo temporal
    - quando ocorre prempcao. 
    - como recursos partilhados quebram deadlines. 


Algoritmos 

RM -> prioridades fixas
EDF -> prioridades dinamicas

# Importancia de PIP e ICPP ?

Porque o scheduling sozinho nao resolve tudo..

Mesmo com tarefas schedulable: 

    - mutexes
    - semaforos
    - seccoes criticas

    podem destruir deadlines

    Esse e um problema classico de RTOS

# Pitfalls 

1. Confundir periodo com deadline

Nem sempre:

    T = D

2. Ignorar preempcoes intermedias

Erro classico nos diagramas temporais, 

3. Nao identificar blocking time

Em PIP / ICPP isto e critico. 

4. Resolver "mecanicamente"

tens de entende bemm :

    - realease time 
    - execution time
    - deadline
    - prioridade

