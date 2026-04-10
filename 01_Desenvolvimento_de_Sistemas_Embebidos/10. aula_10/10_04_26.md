**Ação (1 passo):** usa esta resposta para resolver primeiro o **Exercício 1** e confirmar que percebeste a lógica-base de acesso a registos, porque o resto da aula reaproveita exatamente esse modelo.

**Objetivo:** provar que já distingues 3 níveis que o professor misturou ao longo da aula:

1. acesso direto a registos em user space com `/dev/mem` + `mmap`,
2. módulos de kernel com `ioremap`/timers/interrupções,
3. acesso a periféricos Linux via device drivers e ficheiros especiais como SPI.

---

# 1) Reconstrução da aula 10

## Visão geral do que foi realmente dado

A aula teve quatro blocos principais:

1. **Compilação de módulos de kernel no Raspberry Pi**
2. **GPIO e PWM**
3. **Timers e interrupções no kernel**
4. **SPI no Raspberry Pi, comparação com I2C, e leitura de ADC/Arduino via SPI**

O professor também falou bastante de **detalhes práticos de laboratório**, sobretudo:

* versões do kernel,
* diferenças entre compilar no Raspberry Pi e cross-compilar,
* pequenos erros/typos nos próprios slides/código,
* e como usar isto para os exercícios.

---

## Bloco A — Kernel modules: compilação e versões

### O que foi ensinado

O professor começou por um problema muito prático: **a versão exata do kernel importa** para compilar módulos.

A ideia principal foi:

* no Raspberry Pi, os módulos de kernel têm de ser compilados para a **mesma árvore/configuração/headers** do kernel usado;
* existe um problema real em encontrar a **versão exata** usada pela distribuição;
* o repositório do kernel do Raspberry Pi tem branches por versão principal, mas nem sempre é trivial casar isso com a subversão instalada.

### Ideia central

Um módulo de kernel não é um programa normal. Ele liga-se ao kernel em execução.
Por isso, se compilares contra headers errados, pode:

* não compilar,
* compilar mas não carregar,
* ou carregar com comportamento perigoso.

### Intuição

Pensa assim: um módulo de kernel é como uma peça mecânica feita para encaixar num motor específico.
Se o motor for parecido mas não exatamente igual, a peça “quase” entra — e isso é pior do que não entrar.

### O professor salientou

* No Raspberry Pi podes instalar headers.
* Em cross-compilation tens de apontar bem `ARCH` e `CROSS_COMPILE`.
* Muitas vezes o caminho da toolchain no Makefile/comando tem de estar explícito.

---

## Bloco B — GPIO “library” e acesso a registos

### O que foi ensinado

O professor mostrou uma pequena “biblioteca” em C baseada em `struct` para mapear os registos GPIO do BCM2711:

* `GPFSEL[]` para função do pino
* `GPSET[]` para pôr a 1
* `GPCLR[]` para pôr a 0
* `GPLEV[]` para ler nível
* e também registos ligados a deteção de eventos/interrupções

### Ideia central

Em vez de escreveres “endereços mágicos” por todo o lado, organizas os registos numa `struct`.
Isto melhora:

* legibilidade,
* manutenção,
* e reduz erros de offset.

### Exercício 1 — o que ele realmente quer

Escrever um programa que:

* recebe `GPIO` e `estado` na linha de comandos,
* faz `open("/dev/mem")`,
* faz `mmap()` da zona de GPIO,
* configura o pino como output,
* e escreve 0 ou 1.

### O que este exercício prova

Que sabes:

* abrir memória física exposta pelo Linux,
* mapear registos,
* selecionar função do pino,
* e manipular bits/endereços de hardware.

### Explicação simples

`/dev/mem` é como pedir ao Linux:
“dá-me acesso bruto a uma parte da memória onde estão os registos do hardware”.

Depois `mmap()` transforma isso num apontador em C.

---

## Bloco C — PWM no Raspberry Pi

### O que foi ensinado

O professor passou do GPIO digital normal para **PWM**.

Conceitos principais:

* o PWM usa um **clock de referência**;
* há registos para:

  * **range** = duração/resolução do ciclo,
  * **data** = quanto tempo fica a 1,
  * **control** = modo e enable;
* duty cycle = `Data / Range`.

Também explicou:

* modo **Mark/Space** (PWM “normal”),
* e o algoritmo alternativo do hardware BCM2711.

### Ponto prático importante

Para usar PWM num pino, já não basta pô-lo como output.
É preciso configurar o GPIO para uma **função alternativa**.

O professor repetiu isto várias vezes:

* para esse caso, usar **função alternativa 0**
* codificada como **valor 4** nos 3 bits de função

### Clock do PWM

Houve um detalhe muito importante:

* ao escrever nos registos do clock PWM, é necessário pôr **`0x5A` nos 8 bits mais significativos** da escrita.

Isto é um mecanismo de proteção do hardware.

### Analogia

É como uma fechadura de segurança:
não chega virar a chave principal; tens de introduzir também o “código de autorização”.

---

## Bloco D — Timers no kernel

### O que foi ensinado

O professor mostrou duas famílias de temporização:

1. **timers com jiffies**
2. **high-resolution timers (HR timers)**

### Jiffies

* `HZ` é a frequência do relógio interno do kernel.
* No exemplo dado, `HZ = 250`, logo:

  * 1 tick = 4 ms.

Isto é suficiente para coisas lentas, mas não para PWM mais rápido.

### HR timers

Para melhor resolução:

* usa-se `hrtimer`,
* com tempos expressos em `ktime`,
* incluindo parte em nanossegundos.

### Ponto conceptual importante

O professor insistiu em algo clássico:

> Linux não é, por natureza, um sistema operativo de tempo real.

Ou seja:

* podes pedir nanossegundos,
* mas o sistema não garante esse rigor absoluto,
* porque há escalonamento, outras tarefas, latências do kernel, etc.

### O que isto significa para ti

Se queres PWM visivelmente estável e frequência mais alta:

* `jiffies` pode ser grosseiro demais,
* `hrtimer` é mais apropriado,
* mas continua sem ser “hard real-time”.

---

## Bloco E — Kernel modules e `ioremap`

### O que foi ensinado

O professor foi explícito:

> num módulo de kernel, não se deve usar `/dev/mem`.

Em kernel space:

* o acesso é direto,
* mas é preciso mapear endereços físicos para o espaço virtual do kernel com **`ioremap()`**.

### Diferença mental essencial

User space:

* `open("/dev/mem")` + `mmap()`

Kernel space:

* `ioremap()`

### Porque isto importa

Porque o kernel e o processo do utilizador vivem em contextos diferentes.
Misturar as duas abordagens é erro de modelo mental.

---

## Bloco F — Interrupções externas e Device Tree Overlay

### O que foi ensinado

Para usar interrupções em GPIO no Raspberry Pi com Linux, o professor mostrou:

* **device tree overlay**
* depois o **platform driver**
* depois o **interrupt handler**

### Device tree overlay

Serve para descrever ao Linux:

* que pino queres usar,
* em que função,
* se é input,
* e que interrupção queres ativar.

No exemplo:

* GPIO16 como input
* interrupção por **flanco ascendente**

### Campo `compatible`

Este campo é a “ponte” entre:

* a descrição do hardware no device tree
* e o código do driver no kernel

### Analogia

O `compatible` é como uma etiqueta de encaixe:

* o device tree diz “preciso de um driver deste tipo”,
* o kernel procura um módulo cujo `of_match_table` diga “eu sei tratar disso”.

---

## Bloco G — Platform driver e `probe`

### O que foi ensinado

O professor mostrou a estrutura típica:

* tabela `of_device_id`
* `platform_driver`
* função `probe`
* função `remove`

### Ideia central

`probe()` é chamada quando o kernel encontra uma correspondência entre:

* o que o device tree descreve
* e o que o driver diz suportar

### O que acontece em `probe()`

No exemplo:

* obter número IRQ com `platform_get_irq()`
* registar handler com `devm_request_irq()`

### Sobre `devm_*`

O professor destacou a vantagem:

* recursos alocados são libertados automaticamente quando o módulo termina/remove.

### Intuição

É uma espécie de gestão automática de cleanup.
Não é “garbage collection” no sentido estrito de linguagens geridas, mas a ideia prática é essa: menos fugas de recursos.

---

## Bloco H — Medidor de frequência com interrupções

### O que foi ensinado

O professor propôs um exercício extra:

* contar interrupções num pino,
* medir o tempo com `ktime_get_ns()`,
* calcular frequência.

### Método

1. guardar timestamp inicial na primeira interrupção
2. contar impulsos
3. quando o intervalo atingir 1 segundo (ou outro), calcular:

   * frequência = número de impulsos / tempo

### Aplicação prática

Ele disse que isto é útil para:

* verificar se o PWM gerado está na frequência esperada,
* fazer debug sem osciloscópio.

Isto é muito relevante.

---

## Bloco I — SPI: princípios

### O que foi ensinado

O professor introduziu o SPI como protocolo série síncrono e comparou com I2C.

### Diferenças essenciais em relação ao I2C

**I2C**

* partilha bus de dados
* cada slave tem endereço

**SPI**

* clock também é síncrono
* mas cada slave é escolhido por linha própria de **chip select**
* logo, precisas de uma linha por dispositivo

### Consequência

SPI costuma permitir:

* taxas mais altas,
* simplicidade de protocolo,
* full duplex

Mas paga-se com:

* mais fios,
* menos escalabilidade em número de slaves.

---

## Bloco J — Full duplex em SPI

### O que foi ensinado

Aqui houve uma nuance importante:

SPI é **full duplex**, mas de um modo particular.

Quando o master transmite:

* está automaticamente a receber ao mesmo tempo.

Ou seja:

* TX e RX acontecem em paralelo a cada ciclo de clock.

### Porque isso pode confundir

Muita gente pensa em “write” e “read” como ações separadas.
No SPI real, o shift register faz as duas ao mesmo tempo.

### Implicação prática

Se usares apenas `read()` e `write()` no Linux:

* podes perder controlo fino do full duplex verdadeiro.

Para full duplex controlado:

* precisas de `ioctl()` com as estruturas próprias do driver SPI.

---

## Bloco K — CPOL e CPHA

### O que foi ensinado

O professor mostrou os 4 modos SPI, definidos por:

* polaridade do clock (CPOL)
* fase (CPHA)

### Ideia simples

A pergunta é:

* em que nível o clock fica parado?
* em que flanco é que os dados são amostrados?

### Porque isto é crítico

Se master e slave não concordarem:

* os bits são lidos no instante errado,
* e a comunicação parece “aleatoriamente” errada.

---

## Bloco L — Exemplo de ADC por SPI e ligação ao ATmega128/Arduino

### O que foi ensinado

O professor mostrou um ADC SPI e depois fez a ponte com o Arduino/ATmega.

Pontos principais:

* alguns dispositivos usam palavras maiores do que 8 bits;
* no ATmega128/Arduino o SPI típico trabalha em blocos de 8 bits;
* por isso uma conversão de 10 bits, por exemplo, pode vir repartida por várias transferências.

### Ideia essencial

Ao receber vários bytes:

* tens de reconstruir o valor final com shifts e máscaras.

### Analogia

É como receber uma palavra partida em envelopes:

* primeiro envelope traz cabeçalho + 2 bits úteis
* segundo envelope traz os 8 bits restantes
* tu tens de juntar tudo na posição correta.

---

## Bloco M — SPI no Raspberry Pi com overlays e `spidev`

### O que foi ensinado

Para usar SPI no Raspberry Pi com Linux:

* ativar overlay correspondente
* deixar o kernel carregar o driver
* depois surge um ficheiro especial em `/dev`, do tipo `spidevX.Y`

### Depois disso

No programa:

1. `open()` do ficheiro
2. `ioctl()` para configurar

   * modo
   * velocidade
   * bits por palavra
3. `read()` / `write()` ou `ioctl` específico para transferência full duplex

---

# 2) Explicação simples das partes difíceis

## `/dev/mem` vs `ioremap`

* `/dev/mem` = abordagem de user space
* `ioremap` = abordagem de kernel

Pergunta de engenharia:
“Estou a escrever uma aplicação normal ou um módulo de kernel?”
Essa resposta decide o mecanismo.

---

## Device Tree Overlay

Não é “o driver”.
É uma **descrição do hardware/configuração** que o Linux usa para saber o que existe.

O driver é o código.
O overlay é a forma de dizer ao kernel: “trata este hardware como presente e configurado assim”.

---

## `probe()`

Não é uma função que tu chamas manualmente no fluxo normal.
É o kernel que a chama quando encontra match.

---

## PWM com `hrtimer`

O timer não “faz PWM sozinho”.
Tu usas a callback para:

* mudar o pino,
* calcular o próximo intervalo,
* e rearmar o timer.

---

## `read()`/`write()` em SPI

Funcionam para muitos casos simples.
Mas não expressam naturalmente o full duplex real do SPI.

---

# 3) Erros, inconsistências e partes pouco claras detetadas

## 1. PWM pin: GPIO16 vs GPIO12

Há uma inconsistência no material visual:

* num ponto aparece **GPIO16**
* depois aparece **GPIO12** para PWM

### Correção

O fluxo da aula aponta que o exemplo correto foi tratado com:

* **GPIO12**
* função alternativa correspondente
* canal 1 do bloco PWM (identificado como `CHN0` na `struct`)

### Como pensar

Não aceites o slide isoladamente.
Confirma sempre com:

* função alternativa do pino,
* canal PWM suportado pelo datasheet,
* e exemplo de código final.

---

## 2. Endereço/offset do clock PWM

O próprio professor disse que tinha um erro num endereço/offset do material.

### Correção conceptual

Quando trabalhas com base + offset:

* confirma sempre se o offset está em bytes,
* em words,
* em hexadecimal,
* ou decimal.

Este é um erro clássico de hardware/software.

---

## 3. Escrita no registo do clock sem `0x5A`

Se esqueceres esse prefixo nos bits mais significativos:

* a escrita não terá o efeito esperado.

Isto não é detalhe decorativo. É requisito do hardware.

---

## 4. Usar `/dev/mem` dentro de módulo de kernel

Errado para o modelo ensinado.

### Correção

* user space → `/dev/mem` + `mmap`
* kernel module → `ioremap`

---

## 5. “Linux com resolução de nanossegundos” não significa tempo real garantido

O tipo `ktime` permite granularidade muito fina.
Mas isso **não prova** precisão real equivalente.

---

# 4) Como fazer os exercícios todos — mapa mental prático

## Exercício 1 — GPIO output por `/dev/mem`

Objetivo:

* abrir memória,
* mapear GPIO,
* configurar função,
* escrever 0/1.

Competências:

* `open`
* `mmap`
* `struct` de registos
* seleção de bits

---

## Exercício 2 — PWM generator em user space

Objetivo:

* configurar pino para função alternativa PWM,
* configurar clock PWM,
* definir range/data,
* duty cycle por argumento de linha de comandos.

Competências:

* tudo do exercício 1
* mais clock do PWM
* mais registos do PWM
* mais noção `duty = data/range`

---

## Exercício 3 — PWM em módulo de kernel com timer

Objetivo:

* pegar no `blinker_hr`
* substituir atraso fixo por lógica de duty cycle
* criar PWM por software com `hrtimer`

Competências:

* `ioremap`
* callback de timer
* rearmar temporização
* casos limite 0% e 100%

---

## Exercício extra — frequencímetro por interrupções

Objetivo:

* medir frequência de um sinal externo
* usando GPIO16 + interrupções + `ktime_get_ns()`

Competências:

* overlay
* platform driver
* handler de interrupção
* medição temporal
* cálculo de frequência

---

## Exercício SPI — Raspberry Pi ↔ dispositivo SPI / Arduino

Objetivo:

* ativar overlay SPI
* abrir `spidev`
* configurar modo/velocidade/bits
* enviar/receber dados
* reconstruir valor lido do ADC

Competências:

* device driver Linux já existente
* `ioctl`
* buffers TX/RX
* máscaras e shifts
* protocolo do slave

---

# 5) Perguntas de exame

## Teóricas

1. Qual a diferença entre usar `/dev/mem` e `ioremap()`?
2. Porque é que Linux usa device tree overlays em hardware como o Raspberry Pi?
3. O que faz a função `probe()` num `platform_driver`?
4. Porque é que o SPI precisa de linhas de chip select separadas?
5. Porque é que `ktime_get_ns()` não transforma Linux num RTOS?

## Resposta curta

1. O que representa `HZ`?
2. O que são `jiffies`?
3. O que é duty cycle?
4. Para que serve o campo `compatible` no device tree?
5. Que função Linux obtém o número IRQ a partir do `platform_device`?
6. Que vantagem têm as funções `devm_*`?
7. O que significam CPOL e CPHA?
8. Porque é que `read()`/`write()` simples podem não explorar o full duplex do SPI?

## Compreensão conceptual

1. Porque é perigoso assumir offsets sem confirmar unidades?
2. Porque é que um sinal PWM de frequência muito baixa faz o LED parecer “piscar”?
3. Porque é que contar interrupções durante 1 segundo dá a frequência?
4. Porque é que um ADC de 10 bits pode exigir mais do que uma transferência SPI de 8 bits?
5. Porque é que um erro na função alternativa do GPIO impede o periférico de funcionar mesmo que os registos PWM estejam certos?

---

# 6) Mind map da aula

```text
Aula 10 — Raspberry Pi / Linux kernel / SPI
|
|-- Compilação de módulos
|   |-- kernel headers
|   |-- versão do kernel
|   |-- cross-compilation
|   |-- toolchain / path
|
|-- GPIO em user space
|   |-- /dev/mem
|   |-- mmap
|   |-- struct de registos
|   |-- GPFSEL / GPSET / GPCLR / GPLEV
|
|-- PWM
|   |-- função alternativa do GPIO
|   |-- clock PWM
|   |-- 0x5A nos bits altos
|   |-- CONTROL / RANGE / DATA
|   |-- duty cycle = data/range
|
|-- Timers no kernel
|   |-- jiffies / HZ
|   |-- timer_list
|   |-- hrtimer
|   |-- callback
|   |-- Linux não é RTOS
|
|-- Módulos de kernel
|   |-- ioremap
|   |-- parâmetros do módulo
|   |-- ficheiros virtuais / sysfs
|
|-- Interrupções externas
|   |-- GPIO16 input
|   |-- rising edge
|   |-- device tree overlay
|   |-- compatible
|   |-- platform driver
|   |-- probe / remove
|   |-- platform_get_irq
|   |-- devm_request_irq
|
|-- Frequencímetro
|   |-- contar interrupções
|   |-- ktime_get_ns
|   |-- frequência = impulsos / tempo
|
|-- SPI
|   |-- síncrono
|   |-- SCLK
|   |-- MOSI / MISO
|   |-- chip select
|   |-- full duplex
|   |-- CPOL / CPHA
|   |-- maior velocidade que I2C
|
|-- SPI no Raspberry Pi
    |-- overlay
    |-- spidev
    |-- open
    |-- ioctl
    |-- read / write
    |-- transferência full duplex
    |-- ADC / Arduino / ATmega128
```

---

# 7) Teste de compreensão — 5 perguntas só com base na aula

1. Porque é que o professor disse que o exercício do PWM exige “três conjuntos de registos” e não apenas GPIO?
2. Se estiveres num módulo de kernel, porque é que usar `/dev/mem` está conceptualmente errado?
3. Qual é o papel do `compatible` no device tree overlay?
4. Porque é que o SPI é chamado full duplex e, ainda assim, `read()` e `write()` simples nem sempre chegam?
5. Como usarias interrupções + `ktime_get_ns()` para validar a frequência de um PWM?

---

# 8) Simulação de exame oral/código, estilo professor

## Nível 1

Quero gerar PWM no Raspberry Pi.
Que subsistemas tens de configurar além do GPIO?

## Nível 2

Tens um programa em user space que já liga/desliga um GPIO.
Qual é a diferença conceptual para passar isso para um módulo de kernel?

## Nível 3

No teu módulo PWM por software, como tratas os casos limite de 0% e 100% duty cycle?

## Nível 4

Quero medir a frequência de um sinal externo no GPIO16.
Preferes polling ou interrupções? Justifica com custo e precisão.

## Nível 5

Mostra-me a sequência lógica desde o device tree até ao handler de interrupção ser chamado.

## Nível 6

Se o teu SPI com um Arduino está a devolver valores incoerentes, que hipóteses técnicas testas primeiro?

* modo SPI errado,
* velocidade excessiva,
* bits por palavra errados,
* protocolo do slave mal alinhado,
* reconstrução errada do valor recebido.

## Nível 7

Tens um ADC de 10 bits ligado a um ATmega128 por SPI, mas o master recebe só bytes.
Como reconstruis o valor?
Que bits vêm primeiro?
Como validas experimentalmente?

---

# 9) One-page cheat sheet

## Raspberry Pi / Aula 10 — Cheat Sheet

**User space GPIO**

* `open("/dev/mem", O_RDWR|O_SYNC)`
* `mmap()` registos
* configurar `GPFSEL`
* escrever com `GPSET` / `GPCLR`

**Kernel module GPIO**

* não usar `/dev/mem`
* usar `ioremap()`

**PWM**

* GPIO tem de estar em função alternativa correta
* duty cycle = `DATA / RANGE`
* `CONTROL`: enable + modo
* clock PWM exige escrita com `0x5A` nos bits 31:24

**Temporização**

* `jiffies` / `HZ`: resolução grosseira
* `hrtimer`: melhor resolução
* Linux ≠ RTOS garantido

**Interrupções**

* usar device tree overlay
* `compatible` faz match com driver
* `platform_get_irq()`
* `devm_request_irq()`
* handler devolve `IRQ_HANDLED`

**Frequência por interrupções**

* contar impulsos
* medir tempo com `ktime_get_ns()`
* `freq = count / delta_t`

**SPI**

* síncrono
* SCLK, MOSI, MISO, CS
* full duplex real
* 4 modos: CPOL/CPHA
* mais rápido que I2C, mas com mais fios

**SPI no Linux**

* ativar overlay
* abrir `/dev/spidevX.Y`
* configurar com `ioctl()`
* `read/write` simples
* `ioctl` específico para full duplex/controlar TX+RX

**ADC/Arduino**

* atenção a palavras > 8 bits
* usar máscaras + shifts
* validar timing e protocolo

---

# 10) Resumo final estrito da aula

## Key concepts

* compilação de módulos de kernel depende da versão correta do kernel
* acesso a registos por `/dev/mem` + `mmap` em user space
* acesso por `ioremap` em kernel space
* PWM por hardware com clock, range e data
* PWM por software com `hrtimer`
* Linux não é naturalmente tempo real
* interrupções externas exigem overlay + driver + IRQ handler
* SPI é síncrono, usa chip select, e é full duplex
* `ioctl` é central para configuração de dispositivos SPI no Linux

## Key terminology

* `mmap`
* `/dev/mem`
* `ioremap`
* `jiffies`
* `HZ`
* `hrtimer`
* callback
* device tree overlay
* `compatible`
* `platform_driver`
* `probe`
* IRQ
* `devm_request_irq`
* `ktime_get_ns`
* MOSI / MISO / SCLK / CS
* CPOL / CPHA
* `spidev`
* `ioctl`

## Typical exam traps

* confundir user space com kernel space
* esquecer função alternativa do GPIO
* esquecer `0x5A` nos registos do clock PWM
* assumir que Linux dá timing exato porque usa nanossegundos
* usar `read/write` em SPI e esperar controlo full duplex total
* errar reconstrução de valores multibyte no ADC
* confiar em slide com pin errado sem validar no datasheet

## Real-world applications

* controlo PWM de LEDs e atuadores
* medição de frequência por interrupções
* aquisição de dados de ADC
* comunicação com microcontroladores externos
* drivers Linux para hardware customizado
* debug de sinais digitais sem osciloscópio, usando o próprio sistema

---

## Pitfalls & troubleshooting

* Se o PWM não aparece, suspeita primeiro da **função alternativa do pino** e do **clock**.
* Se o módulo não carrega, suspeita da **versão/configuração do kernel**.
* Se a interrupção nunca dispara, valida o **overlay**, o **pino**, e o **tipo de flanco**.
* Se o SPI devolve lixo, verifica **modo SPI**, **velocidade**, **bits por palavra** e **protocolo do slave**.

## Alternativas / tradeoffs

* **PWM hardware**: mais limpo e estável, mas exige perceber registos e clock.
* **PWM software com hrtimer**: mais flexível para aprender, mas menos robusto temporalmente.
* **SPI**: mais rápido que I2C, mas usa mais linhas.
* **Interrupções**: melhor para eventos, mas mais complexas do que polling.

## Pergunta de decisão (1)

Queres que no próximo passo eu pegue **apenas no Exercício 1** e o decomponha em raciocínio de engenharia, sem te dar logo a solução completa?
