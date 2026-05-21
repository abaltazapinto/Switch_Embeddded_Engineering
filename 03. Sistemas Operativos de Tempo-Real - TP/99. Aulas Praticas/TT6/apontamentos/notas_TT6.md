Ação (1 passo)

No terminal da VM, confirma se tens algum ficheiro TT6 ou Aula 06 extraído/disponível:

find ~ -iname "*TT6*" -o -iname "*Aula*06*" -o -iname "*kernel*"
Objetivo

Perceber se o TT6 já está na tua VM. Nos ficheiros que tenho aqui, encontrei TT4, TP6/LKM, mas não encontrei o enunciado TT6. O curso usa TT para autoestudo e TP/PL para aulas práticas , e o tema atual encaixa em kernel development / LKM, que é parte da cadeira . O TP6 mostra que LKMs permitem adicionar código ao kernel sem recompilar/reiniciar, mas com risco de crash se houver bug .

Como pensar

Se o TT5 foi compilar/integrar o MOKER no kernel, o TT6 provavelmente continua numa destas linhas:

mexer no kernel source tree, ou
usar LKMs / /proc / scheduler / estruturas internas.

Mas antes de tocar em código kernel, precisamos identificar o enunciado certo. Kernel work sem enunciado = risco alto de fazer trabalho errado. ⚙️

---


MOKER — Framework Tracing Mechanism
Objetivo: criar um mecanismo de tracing no kernel para registar eventos de escalonamento:

SCHED_TICK
SWITCH_TO
SWITCH_AWAY
MISC_EVT

O enunciado diz que o mecanismo cria /proc/moker_trace para passar informação do kernel para user space e guarda eventos num ring buffer .

Como pensar

O TT6 não é “procurar kernel”. É instrumentar o scheduler.

A lógica é:

scheduler event acontece
        ↓
moker_trace(...)
        ↓
evento guardado num ring buffer
        ↓
cat /proc/moker_trace
        ↓
trace.csv em user space

Estamos a transformar o kernel num “osciloscópio” do scheduler. ⚙️📈

---

menu "MOKER framework"

config MOKER_FRAMEWORK
        bool "My Own KERnel Framework"
        default y

config MOKER_TRACING
        bool "MOKER tracing"
        default y
        depends on MOKER_FRAMEWORK

endmenu



Objetivo

Preparar a opção de configuração CONFIG_MOKER_TRACING. O TT6 pede criar a entrada MOKER_TRACING, dependente de MOKER_FRAMEWORK, para ativar o tracing no build do kernel .

Como pensar

O Kconfig é o “menu elétrico” do kernel: define que features existem e se entram ou não na compilação.

Neste TT6:

MOKER_FRAMEWORK
        ↓
MOKER_TRACING
        ↓
trace.o
        ↓
/proc/moker_trace

---

# Fazer o trace.h

nano trace.h


#ifndef __TRACE_H_
#define __TRACE_H_

#define TRACE_ENTRY_NAME "moker_trace"
#define TRACE_BUFFER_SIZE 1000
#define TRACE_STRING_BUFFER_SIZE 200
#define TRACE_TASK_COMM_LEN 16

enum evt{
        MISC_EVT = 0,
        SCHED_TICK,
        SWITCH_AWAY,
        SWITCH_TO,
};

struct trace_evt{
        enum evt event;
        unsigned long long time;
        int number;
        pid_t pid;
        int state;
        int prio;
        int policy;
        char comm[TRACE_TASK_COMM_LEN];
};

struct trace_evt_buffer{
        struct trace_evt events[TRACE_BUFFER_SIZE];
        int write_item;
        int read_item;
        spinlock_t lock;
};

ssize_t trace_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);
void moker_trace(enum evt event, int number, struct task_struct *p);

#endif

---

Objetivo

Criar a interface do mecanismo de tracing. O TT6 pede dois ficheiros novos em kernel/moker: trace.h e trace.c; o trace.h define os eventos, a estrutura do ring buffer e a função moker_trace() que depois será chamada pelo scheduler .

Como pensar

Este header é o contrato entre:

kernel/sched/core.c
        ↓ chama
moker_trace(...)
        ↓ usa
trace.h + trace.c

Ou seja, o scheduler não precisa saber como o ring buffer funciona. Só precisa conhecer a função moker_trace().

---

Agora tenho de criar o trace.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include "trace.h"

struct trace_evt_buffer trace;

static void increment(int *item)
{
        *item = *item + 1;
        if (*item >= TRACE_BUFFER_SIZE) {
                *item = 0;
        }
}

static int is_empty(int r, int w)
{
        /* empty if r == w */
        return !(r ^ w);
}

static int is_full(int r, int w)
{
        int write = w;

        increment(&write);
        return write == r;
}

# Objetivo

Começar a implementação do ring buffer que vai guardar eventos do scheduler. O TT6 define que o tracing deve guardar eventos como SCHED_TICK, SWITCH_TO e SWITCH_AWAY num buffer circular, depois exposto por /proc/moker_trace .

# Como pensar

Esta parte ainda não escreve no /proc; só prepara a estrutura base:

        write_item → próxima posição para escrever
        read_item  → próxima posição para ler
        increment  → anda no buffer e volta a zero no fim

Isto é literalmente uma fila circular dentro do kernel. ⚙️

---

## Ação (1 passo)

No mesmo `trace.c`, acrescenta agora a função `dequeue()` **logo abaixo de `is_full()`**:

```c
static int dequeue(char *buffer)
{
        int ret = 0, len;
        char evt[10];

        spin_lock(&trace.lock);

        if (!is_empty(trace.read_item, trace.write_item)) {
                switch ((int)trace.events[trace.read_item].event) {
                case MISC_EVT:
                        strcpy(evt, "MC_EVT");
                        break;
                case SCHED_TICK:
                        strcpy(evt, "SCH_TK");
                        break;
                case SWITCH_AWAY:
                        strcpy(evt, "SWT_AY");
                        break;
                case SWITCH_TO:
                        strcpy(evt, "SWT_TO");
                        break;
                default:
                        strcpy(evt, "UK_EVT");
                }

                len = sprintf(buffer, "%llu,", trace.events[trace.read_item].time);
                len += sprintf(buffer + len, "%s,", evt);
                len += sprintf(buffer + len, "*%d*,", (int)trace.events[trace.read_item].number);
                len += sprintf(buffer + len, "%d,", (int)trace.events[trace.read_item].policy);
                len += sprintf(buffer + len, "%d,", (int)trace.events[trace.read_item].prio);
                len += sprintf(buffer + len, "%d,", (int)trace.events[trace.read_item].pid);
                len += sprintf(buffer + len, "%d,", (int)trace.events[trace.read_item].state);
                len += sprintf(buffer + len, "%s\n", trace.events[trace.read_item].comm);

                increment(&trace.read_item);
                ret = 1;
        }

        spin_unlock(&trace.lock);

        return ret;
}
```

Guarda:

```text
Ctrl + O → Enter
```

## Objetivo

Implementar a leitura de **um evento do ring buffer** e convertê-lo numa linha CSV. O TT6 define que cada linha deve sair como:

```text
<timestamp>,<event>,<*number*>,<policy>,<prio>,<pid>,<state>,<comm>
```

Isto corresponde ao formato descrito no enunciado para `/proc/moker_trace` .

## Como pensar

Esta função faz três coisas:

```text
ring buffer interno
        ↓
traduz enum para texto: SWT_TO, SWT_AY, SCH_TK
        ↓
linha CSV para user space
```

Isto é importante porque o kernel guarda estruturas C, mas o utilizador precisa de texto legível.

## Pitfalls & troubleshooting

* Não remover `spin_lock()` / `spin_unlock()`; o scheduler pode escrever enquanto lês.
* Não trocar `read_item` por `write_item`.
* `SWT_AY` e `SWT_TO` são nomes curtos, não erros.
* `sprintf()` aqui é usado dentro do kernel; não é o `printf()` de user space.

---
## Ação (1 passo)

Acrescenta agora a função `enqueue()` **logo abaixo de `dequeue()`** em `trace.c`:

```c id="dtxals"
static int enqueue(enum evt event, unsigned long long time, int number, struct task_struct *p)
{
        spin_lock(&trace.lock);

        if (is_full(trace.read_item, trace.write_item))
                increment(&trace.read_item);

        trace.events[trace.write_item].number = number;
        trace.events[trace.write_item].event = event;
        trace.events[trace.write_item].time = time;
        trace.events[trace.write_item].pid = p->pid;
        trace.events[trace.write_item].state = p->__state;
        trace.events[trace.write_item].prio = p->prio;
        trace.events[trace.write_item].policy = p->policy;
        strcpy(trace.events[trace.write_item].comm, p->comm);

        increment(&trace.write_item);

        spin_unlock(&trace.lock);

        return 1;
}
```

Guarda:

```text id="7v6tmx"
Ctrl + O → Enter
```

## Objetivo

Implementar a escrita de eventos no ring buffer. O TT6 quer guardar tipo de evento, timestamp, número, política, prioridade, PID, estado e nome do processo .

## Como pensar

Agora estás a construir o lado “producer”:

```text id="a8zg1c"
scheduler chama moker_trace()
        ↓
enqueue(...)
        ↓
guarda snapshot da task no ring buffer
```

Se o buffer estiver cheio, o código descarta o evento mais antigo ao avançar `read_item`.

## Pitfalls & troubleshooting

* `p->__state` depende da versão do kernel; no teu TT6 é esse campo.
* Não trocar `write_item` por `read_item`.
* Não retirar o `spin_lock`, porque eventos podem chegar de contexto concorrente.
* `comm` tem limite de 16 chars; é normal nomes longos aparecerem truncados.

## Alternativas / tradeoffs

* **Overwrite do evento antigo:** simples e evita bloquear o kernel.
* **Bloquear quando cheio:** mau para scheduler; podia introduzir latência.
* **Aumentar buffer:** guarda mais eventos, mas consome mais memória kernel.

---
Acrescenta agora a função trace_read() logo abaixo de enqueue():

ssize_t trace_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
        char buffer[TRACE_STRING_BUFFER_SIZE];
        int ret = 0, len = 0;

        if (!dequeue(buffer))
                return 0;

        len = strlen(buffer);
        if (len <= 0)
                return -EFAULT;

        if (count < len)
                return -EFAULT;

        ret = copy_to_user(buf, buffer, len);
        if (ret != 0)
                return -EFAULT;

        return len;
}

Objetivo

Criar a função que entrega os dados do kernel para user space quando fizeres:

cat /proc/moker_trace

O TT6 usa /proc/moker_trace como interface para exportar os eventos do scheduler guardados no ring buffer .

Como pensar

trace_read() é a ponte:

ring buffer kernel
        ↓ dequeue()
linha CSV em buffer local
        ↓ copy_to_user()
terminal / ficheiro trace.csv

O kernel não pode escrever diretamente para memória de user space; por isso usa copy_to_user().

---

## Ação (1 passo)

Ainda é normal dar:

```bash
cat: /proc/moker_trace: No such file or directory
```

porque **ainda não compilaste, instalaste e arrancaste o kernel novo com o tracing**. Primeiro acaba o `trace.c`: abre-o de novo e acrescenta o bloco final **no fim do ficheiro**.

```bash
nano trace.c
```

Cola no fim:

```c
static const struct proc_ops trace_ops = {
        .proc_read = trace_read,
};

static int __init proc_trace_init(void)
{
        proc_create(TRACE_ENTRY_NAME, 0444, NULL, &trace_ops);
        printk("MOKER:/proc/%s created\n", TRACE_ENTRY_NAME);

        spin_lock_init(&trace.lock);
        trace.write_item = 0;
        trace.read_item = 0;

        return 0;
}

module_init(proc_trace_init);

void moker_trace(enum evt event, int number, struct task_struct *p)
{
        unsigned long long time;

        time = ktime_to_ns(ktime_get());
        enqueue(event, time, number, p);
}
```

Guarda e sai:

```text
Ctrl + O → Enter → Ctrl + X
```

## Objetivo

Este bloco cria a entrada `/proc/moker_trace` quando o código for inicializado no kernel. O TT6 diz que a feature interage com user space através de uma entrada `/proc/moker_trace` e que só depois do reboot de kernel instalado deves fazer `cat /proc/moker_trace > trace.csv`  .

## Como pensar

Neste momento tens ficheiros fonte, mas o kernel em execução ainda não conhece esse código:

```text
trace.c escrito no disco
        ≠
trace.c compilado no kernel a correr
```

Só depois de:

```text
Makefile + menuconfig + compile + install + reboot
```

é que `/proc/moker_trace` pode existir.

## Pitfalls & troubleshooting

* Não testar `/proc/moker_trace` antes do reboot do kernel novo.
* `module_init(proc_trace_init)` aqui será chamado quando o código entrar no kernel build.
* Se faltares este bloco, compila mas não cria `/proc/moker_trace`.
* Se `proc_create()` falhar, não haverá ficheiro em `/proc`.

## Alternativas / tradeoffs

* **Continuar por blocos:** menos risco.
* **Compilar já:** prematuro; ainda falta ligar o tracing ao scheduler e ao `Makefile`.

## Pergunta de decisão

Conseguiste acrescentar este bloco final ao `trace.c` e guardar?

---

Agora liga o trace.o ao build do MOKER. Abre o Makefile dentro de kernel/moker:

nano Makefile

Acrescenta esta linha:

obj-$(CONFIG_MOKER_TRACING) += trace.o

Guarda e sai:

Ctrl + O → Enter → Ctrl + X
Objetivo

Dizer ao sistema de build do kernel: “quando CONFIG_MOKER_TRACING=y, compila trace.c como trace.o”. O TT6 pede esta alteração no Makefile de linux-6.19.9-moker/kernel/moker antes de compilar .

Como pensar

Kconfig cria a opção.
Makefile usa a opção.

Kconfig:
CONFIG_MOKER_TRACING=y

Makefile:
obj-y += trace.o

Resultado:
trace.c entra no kernel

---


cat Makefile

Deve aparecer pelo menos isto:

# MOKER framework makefile
obj-$(CONFIG_MOKER_TRACING) += trace.o
Objetivo

Confirmar que trace.c vai entrar na compilação quando CONFIG_MOKER_TRACING=y. O TT6 pede exatamente esta ligação no Makefile do diretório kernel/moker .

Como pensar

O facto de estar quase vazio não é problema. O diretório kernel/moker é teu, criado no TT5 para a framework MOKER. Agora o TT6 adiciona o primeiro ficheiro funcional sério: trace.o.

kernel/moker/Makefile
        ↓
trace.c → trace.o
        ↓
kernel image


---

Como pensar

Ainda falta o kernel chamar moker_trace(). Por enquanto tens o “gravador”, mas ainda não ligaste os sensores:

trace.c existe
        ↓
mas sched_tick / __schedule ainda não chamam moker_trace()
        ↓
logo /proc/moker_trace ainda não terá eventos

---

# tracing completo

trace.c completo
        ↓
scheduler pode chamar moker_trace()
        ↓
eventos entram no ring buffer
        ↓
/proc/moker_trace exporta CSV

---

Mas esta política LIFO faz quase o contrário:

última task pronta → prioridade máxima

Isso é útil para laboratório porque cria preempções com frequência:

Task 3 corre
Task 2 chega → preempta task 3
Task 1 chega → preempta task 2

Depois entra o mutex:

task mais recente ganha CPU
mas pode bloquear no mutex
vai para wait queue
outra task volta a correr

Este é o ponto didático: o scheduler decide quem corre, mas o mutex pode impedir uma task de progredir.

Devemos tentar implementar?

Sim — mas com o mindset correto:

não implementar para “fazer RT”
implementar para aprender scheduler internals

O valor está em veres na prática:

Conceito	Onde aparece
preempção	SWT_AY / SWT_TO
ready queue	ENQ_RQ / DEQ_RQ
bloqueio por mutex	ENQ_WQ
lock/unlock	MUT_LK / MUT_UL
atraso temporal	sleeps absolutos no passado
não-determinismo	VM, interrupções, scheduler real

---

## Ação (1 passo)

Perfeito — o `trace.c` está completo. Agora abre o header do scheduler:

```bash
cd ~/linux-kernel/linux-6.19.9-moker
nano kernel/sched/sched.h
```

Procura a zona dos includes. No nano podes usar:

```text
Ctrl + W
#include "cpupri.h"
Enter
```

E logo **depois** destes includes:

```c
#include "cpupri.h"
#include "cpudeadline.h"
```

adiciona:

```c
#ifdef CONFIG_MOKER_TRACING
#include "../moker/trace.h"
#endif
```

Guarda e sai:

```text
Ctrl + O → Enter → Ctrl + X
```

## Objetivo

Tornar `moker_trace()` visível para o código do scheduler. O TT6 pede incluir `../moker/trace.h` em `kernel/sched/sched.h` quando `CONFIG_MOKER_TRACING` estiver ativo .

## Como pensar

Agora estás a criar a ligação entre dois subsistemas:

```text
kernel/moker/trace.h
        ↓
kernel/sched/sched.h
        ↓
kernel/sched/core.c
```

Sem isto, quando `core.c` chamar `moker_trace(...)`, o compilador não conhece a função nem o `enum evt`.

## Pitfalls & troubleshooting

* Não colocar o include fora do `#ifdef`; queremos que só exista se `CONFIG_MOKER_TRACING=y`.
* Não usar caminho absoluto.
* Não escrever `../../moker/trace.h`; a partir de `kernel/sched`, o caminho correto é `../moker/trace.h`.
* Não editar ainda `core.c`; primeiro esta ponte.

## Alternativas / tradeoffs

* **Incluir em `sched.h`:** segue o TT6 e torna visível em ficheiros do scheduler.
* **Incluir diretamente em `core.c`:** poderia funcionar, mas foge ao enunciado.

## Pergunta de decisão

Conseguiste adicionar o include em `kernel/sched/sched.h`?


SIM

---