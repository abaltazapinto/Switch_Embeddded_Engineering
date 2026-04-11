## Ação (1 passo)

👉 Escreve um **resumo técnico curto (README)** com estes pontos:

```text
PL5 – Exercício II (blinker-rpi4)

Objetivo:
Implementar um driver de caractere que controla o estado de um GPIO (GPIO12) através de um timer no kernel.

Arquitetura:
- blinker.c → lógica do driver (/dev/blinker, read/write, timer)
- gpio.c → acesso ao hardware (GPIO12 via ioremap)
- gpio.h → interface entre driver e hardware

Funcionamento:
- /dev/blinker permite interação com user space
- read() → devolve o período atual (ms)
- write() → altera o período do blink
- hrtimer → alterna o estado do GPIO12 (LED ON/OFF)

Validação:
- insmod sem erros ✔
- lsmod confirma módulo carregado ✔
- cat /dev/blinker → 2000 ms ✔
- echo 1000 > /dev/blinker ✔
- cat /dev/blinker → 1000 ms ✔

Conclusão:
Driver funcional com comunicação user space ↔ kernel ↔ hardware.
```

---

## Objetivo

Consolidar o que aprendeste e garantir que consegues explicar o exercício numa avaliação.

---

## Como pensar 🧠

Isto não é só “um exercício que funciona”.
Tu fizeste:

```text
User Space ↔ Kernel ↔ Hardware
```

Mais concretamente:

```text
echo → write() → altera variável interna → timer usa essa variável → GPIO muda
cat  → read() → devolve estado interno
```

👉 Isto é literalmente o modelo base de qualquer driver Linux.

---

## Pitfalls ⚠️

* ❌ esquecer separar lógica (blinker) de hardware (gpio)
* ❌ não perceber que `/dev/blinker` é a API do driver
* ❌ achar que o LED é o importante (não é — é só prova física)

---

## Alternativas / tradeoffs

* Timer normal (`jiffies`) vs `hrtimer`
  ✔ hrtimer → mais preciso
  ❌ mais complexo

* GPIO direto vs abstração (`gpio.c`)
  ✔ abstração → código reutilizável
  ❌ mais ficheiros para gerir

---

## Pergunta de decisão ❓

👉 Queres avançar para o **Exercício III (Software PWM com hrtimer)** ou queres primeiro perceber profundamente **como o `my_timer_func` controla o GPIO12 internamente**?
