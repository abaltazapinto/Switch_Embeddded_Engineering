# Scheduling and Synchronization
    
    PL1

| Tarefa | C ms | T ms | D ms | Prioridade RM |
| ------ | ---: | ---: | ---: | ------------: |
| τ1     |    2 |    6 |    5 |             3 |
| τ2     |    3 |   12 |   12 |             2 |
| τ3     |    4 |   15 |   15 |             1 |


    Teoria

    Em RM 
        - Quanto menor o periodo T , maior a prioridade

    Portanto:

        . t1 tem T = 6 ms -> maior prioridade
        . t2 tem T = 12 ms -> prioridade intermedia
        . t3 tem T = 15 -> menor prioridade

    Justificacao

    A prioridade e fixa porque RM e um algoritmo de fixed-priority scheduling.
    Nao depende da deadline absoluta no momento: depende apenas do periodo da tarefa.