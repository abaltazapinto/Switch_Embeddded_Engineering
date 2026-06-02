| Tópico | O que devo saber antes?                      | Conceito central      | Ferramenta provável          | Evidência prática              |
| ------ | -------------------------------------------- | --------------------- | ---------------------------- | ------------------------------ |
| PO1    | Threads, memória partilhada, race conditions | Concorrência          | C / POSIX threads            | pequeno programa com 2 threads |
| PO2    | Funções puras, imutabilidade                 | Programação funcional | Rust / Haskell-like concepts | função sem estado global       |
| PO3    | Loops paralelos, granularidade               | OpenMP                | C/C++ + OpenMP               | paralelizar um `for`           |
| PO4    | Ownership, borrowing, lifetimes              | Rust funcional        | Rust                         | programa sem data races        |
| PO5    | Threads/tasks em Rust                        | Concorrência segura   | Rust threads / channels      | producer-consumer              |
| PO6    | Deadlines, scheduling, prioridade            | Tempo-real            | RTOS / Linux RT / theory     | analisar latência              |
