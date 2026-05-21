# Starvation

## Ação — 1 passo

Escreve esta definição no caderno:

> **Starvation** acontece quando uma tarefa, interrupção, thread ou periférico **fica indefinidamente sem CPU ou sem acesso a um recurso**, porque outras partes do sistema têm sempre prioridade maior.

## Objetivo

Perceber que starvation **não é simplesmente “esperar”**.
É esperar **sem garantia de progresso**.

Em embedded systems isto é crítico porque muitos sistemas precisam de comportamento **determinístico** ou **real-time**, ou seja, reagir dentro de um tempo máximo aceitável. O livro *Making Embedded Systems* destaca precisamente que alguns sistemas embebidos têm de agir de forma determinística ou em tempo real, apesar de restrições de CPU, memória e energia. 

## Como pensar

Imagina um microcontrolador com:

```text
Task A: lê sensor crítico        prioridade alta
Task B: atualiza LCD             prioridade baixa
Task C: envia dados por UART     prioridade média
```

Se a **Task A** está sempre pronta a correr, o scheduler pode nunca escolher a **Task B**.

Resultado:

```text
LCD nunca atualiza
mas o sistema "não crashou"
```

Isto é starvation.

Em sistemas com interrupções também pode acontecer. No ATmega128, as interrupções têm prioridade conforme a posição no vetor: menor endereço significa maior prioridade. 
Se uma interrupção de alta prioridade dispara constantemente, código de menor prioridade pode ficar sem executar.

## Exemplo mental simples

```c
while (1)
{
    read_sensor();     // demora muito ou corre sempre
    control_motor();   // prioridade funcional alta
    update_display();  // quase nunca chega aqui
}
```

Se `read_sensor()` ou `control_motor()` bloquearem demasiado tempo, `update_display()` sofre starvation.

## Pitfalls & troubleshooting

* **Confundir starvation com deadlock**: deadlock é bloqueio circular; starvation é falta contínua de oportunidade.
* **ISRs longas** podem causar starvation do `main()` ou de tarefas RTOS.
* **Prioridades fixas mal escolhidas** podem fazer tarefas baixas nunca correrem.
* **Loops sem timeout** podem impedir progresso do resto do sistema.

## Alternativas / tradeoffs

| Abordagem         | Vantagem                              | Risco                   |
| ----------------- | ------------------------------------- | ----------------------- |
| Prioridades fixas | Simples e previsível                  | Pode causar starvation  |
| Round-robin       | Mais justo                            | Menos controlo temporal |
| Aging             | Tarefas que esperam ganham prioridade | Mais complexo           |
| Time slicing      | Evita monopolização da CPU            | Overhead de contexto    |

## Pergunta de decisão

Queres analisar starvation no contexto de **RTOS/tasks** ou no contexto de **interrupções num AVR/ATmega128**?
