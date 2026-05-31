# Teste 2 - Sistemas Operativos de Tempo-Real (PGSCE-SIOPTR)

**Aluno:** Paulo Baltarejo Pinto  
**Instituição:** ISEP - Instituto Superior de Engenharia do Porto  
**Unidade:** Sistemas Operativos de Tempo-Real  
**Tipo:** Exercício individual  
**Duração:** 1h00m  
**Data:** 30/05/2026  
**Versão:** A

> Documento reconstruído a partir de fotografias. Algumas zonas estavam inclinadas, desfocadas ou parcialmente cortadas; nesses casos marquei como **[confirmar]**.

---

## Regras visíveis no enunciado

- Responda somente a uma única opção por pergunta.
- Escolha a opção mais completa e adequada conforme os conteúdos/discussão das aulas.
- Caso se engane no preenchimento da tabela, indique por extenso a opção que considera correta.
- Se a resposta assinalada for incorreta, sofre penalização de 1/3 da cotação da pergunta.
- Apenas as respostas assinaladas nesta página serão consideradas.
- É obrigatória a entrega de todas as folhas do exame.

---

## Respostas assinaladas na folha

| Pergunta | Opção assinalada |
|---:|:---:|
| 1 | A |
| 2 | C |
| 3 | B |
| 4 | C |
| 5 | B |
| 6 | B |
| 7 | B |
| 8 | C |
| 9 | B |
| 10 | A |
| 11 | A/B - rasurado, confirmar |
| 12 | A |
| 13 | A |
| 14 | D |
| 15 | B |
| 16 | B |
| 17 | B |
| 18 | C |
| 19 | D |
| 20 | C |

---

# Enunciado limpo por áreas

## Página 1 - Perguntas 1 a 4

### 1. General-Purpose Operating Systems (GPOS)

(a) Usam políticas de escalonamento por forma a evitar *starvation*.  
(b) São usados em sistemas de tempo-real.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 2. Num sistema operativo, uma interrupção

(a) É um evento que altera a sequência de execução das instruções.  
(b) Pode ser gerada por um processador.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 3. Linux Kernel build system

(a) Usa símbolos de configuração para compilar condicionalmente o kernel do Linux.  
(b) Constrói o *object code* iterando de forma recursiva e descendente na estrutura de diretórios de código-fonte.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 4. No kernel do Linux

(a) Uma *system call* é identificada por um número.  
(b) Uma *system call* é identificada por uma interrupção.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

---

## Página 2 - Perguntas 5 a 10

### 5. No kernel do Linux, o escalonamento de tarefas

(a) É organizado por prioridades.  
(b) Usa classes de escalonamento para implementar políticas de escalonamento.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 6. No kernel do Linux

(a) Cria uma instância do tipo `struct rq` por CPU.  
(b) Cria uma instância do tipo `struct rq` para todos os CPUs.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 7. No kernel do Linux, o que é a *idle task*?

(a) Para o sistema.  
(b) É escalonada de acordo com a política de escalonamento identificada por `SCHED_IDLE`.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 8. No kernel do Linux, o *tick rate* é definido por `HZ`

(a) O *tick* é a interrupção temporal.  
(b) A cada *tick*, a função `scheduler_tick()` é invocada.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 9. No kernel do Linux, relativamente aos mecanismos de sincronização

(a) O valor de um *spinlock* pode ser alterado por qualquer processo/*thread*.  
(b) Somente a *thread* que possui/obtém o *lock* pode alterar/libertar o *lock*. **[confirmar texto]**  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 10. No kernel do Linux, relativamente ao mecanismo de sincronização `spinlock`

(a) Uma tarefa que faz `lock` de um *spinlock* indisponível é colocada numa fila de espera. **[confirmar texto]**  
(b) Uma tarefa que faz `lock` de um *spinlock* indisponível é automaticamente removida do processador. **[confirmar texto]**  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

---

## Página 3 - Perguntas 11 a 16

### 11. No kernel do Linux, as operações com variáveis do tipo `atomic_t`

(a) São atómicas.  
(b) O valor definido pela variável está limitado a 24 bits.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 12. No kernel do Linux, as interrupções

(a) Podem ser desabilitadas.  
(b) Não podem ser desabilitadas.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 13. O kernel do Linux disponibiliza a implementação de árvores binárias do tipo Red-black

(a) São adequadas para situações que impliquem ordenação.  
(b) São auto-balanceadas.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 14. No kernel do Linux, a macro `container_of(ptr, type, member)`

(a) Devolve o valor do `member`.  
(b) Devolve o valor de `ptr`.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 15. *Loadable Kernel Modules*

(a) Podem ser inseridos no kernel em tempo de compilação.  
(b) Podem ser inseridos no kernel em tempo de execução.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 16. Processos e *threads*

(a) Quando uma tarefa é criada pela função `fork`, os atributos `tgid` e `pid` associados à nova tarefa são diferentes da tarefa pai. **[confirmar texto]**  
(b) Quando uma tarefa é criada pela função `pthread_create`, o atributo `tgid` é igual ao `tgid` da tarefa pai, mas o atributo `pid` é diferente. **[confirmar texto]**  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

---

## Página 4 - Perguntas 17 a 20

### 17. No contexto de comunicação/sincronização do kernel do Linux **[confirmar enunciado]**

(a) O processo de compilação tem suporte de partilha/funções sobre variáveis. **[confirmar texto]**  
(b) O processo de compilação tem suporte por *spinlocks* ou mutex. **[confirmar texto]**  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 18. No kernel do Linux

(a) A invocação da função `resched_curr()` marca a presença/necessidade de reescalonamento para um processo. **[confirmar texto]**  
(b) A função `schedule_core()` invoca a função `__schedule()`. **[confirmar texto]**  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 19. No kernel do Linux

(a) Para cada semáforo é criada uma instância do tipo `struct rq`. **[confirmar texto]**  
(b) Para cada componente é criada uma instância do tipo `struct task_struct`. **[confirmar texto]**  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

### 20. No kernel do Linux

(a) Para cada processo é criada uma instância do tipo `struct task_struct`.  
(b) Para cada *thread* é criada uma instância do tipo `struct task_struct`.  
(c) Ambas as opções anteriores.  
(d) Nenhuma das opções anteriores.

---

## Checklist para validação manual

- Confirmar a pergunta 11, porque a folha de respostas parece ter rasura entre A e B.
- Confirmar o texto das perguntas 9, 10, 16, 17, 18 e 19, porque a fotografia está com pouca resolução nessa zona.
- Se for para estudar, cruzar os tópicos com documentação oficial do kernel Linux: `scheduler`, `struct rq`, `task_struct`, `atomic_t`, `container_of`, interrupções, *spinlocks*, semáforos e LKMs.
