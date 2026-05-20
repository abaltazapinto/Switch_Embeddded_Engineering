## Ação (1 passo)

**Sim: começa pelo TT4.** 🎯
Mas trata o **TT4 como “setup/base de infraestrutura”**, não como o conteúdo conceptual principal.

## Objetivo

O **TT4 — MOKER Setup** prepara o ambiente para compilar o teu próprio kernel: instalar dependências, mostrar o GRUB, obter o source do Linux, criar `.config`, compilar e instalar o kernel. Isto é pré-requisito para os TTs seguintes sobre o framework MOKER. 

## Como pensar

A sequência lógica é:

**TT4 → TT5 → TT6 → TT7**

Porque:

* **TT4**: preparar e compilar o kernel MOKER.
* **TT5**: criar a estrutura `kernel/moker`, Kconfig e Makefile do framework. 
* **TT6**: adicionar mecanismo de tracing do escalonamento com eventos como `SCHED_TICK`, `SWITCH_TO`, `SWITCH_AWAY`. 
* **TT7**: controlar o tracing com uma nova system call. 

Portanto, **não comeces por TT6 ou TT7**, porque eles assumem que já tens o kernel preparado e o framework MOKER criado.

## Pitfalls & troubleshooting

* O TT4 pode demorar muito porque compilar kernel é pesado.
* Se o GRUB não mostrar o menu, depois não consegues escolher facilmente o kernel novo.
* Se a VM tiver pouco espaço em disco, a compilação pode falhar.
* Se saltares o TT5, o TT6 não terá onde integrar `trace.c` e `trace.h`.

## Alternativas / tradeoffs

**Opção A — seguir TT4 completo:** melhor para compreender kernel real, mas demora.
**Opção B — rever TT4 teoricamente e fazer TT5/TT6 depois:** mais rápido, mas arriscas não conseguir compilar/testar.

## Pergunta de decisão

Queres agora fazer o **TT4 como instalação real na tua VM**, ou queres primeiro fazer uma **leitura técnica guiada do TT4 para perceber exatamente o que cada comando prova**?


---

## Ação (1 passo)

Lê o **TT4 como um mapa de bootstrapping do kernel**, não como uma lista de comandos.

Divide mentalmente o TT4 em **7 blocos**:

| Bloco | O que acontece                       | Pergunta de engenharia                                                    |
| ----- | ------------------------------------ | ------------------------------------------------------------------------- |
| 1     | Instalar ferramentas                 | “Que partes do build precisam de compilador, parser, crypto, ELF, menus?” |
| 2     | Mostrar GRUB                         | “Como recupero se o kernel novo não arrancar?”                            |
| 3     | Obter source Linux                   | “Estou a trabalhar numa árvore de código isolada?”                        |
| 4     | Criar `.config`                      | “Que features entram no kernel final?”                                    |
| 5     | Alterar `EXTRAVERSION` para `-moker` | “Como distingo o meu kernel do kernel original?”                          |
| 6     | Compilar/instalar                    | “Onde vão parar imagem, módulos e initramfs?”                             |
| 7     | Boot pelo GRUB                       | “Estou mesmo a correr o kernel que compilei?”                             |

O TT4 começa com ferramentas e pacotes, depois passa ao GRUB, depois source code, configuração, compilação, instalação e boot do kernel MOKER. 

## Objetivo

Perceber que o TT4 não é “instalar coisas”. É criar uma **linha de segurança** para mexeres no kernel:

```text
VM limpa
  ↓
dependências
  ↓
source Linux
  ↓
.config
  ↓
kernel 6.19.9-moker
  ↓
GRUB permite escolher kernel
  ↓
boot controlado
```

A ideia central da aula TP8 confirma isto: primeiro obténs o source, configuras features/modules via `.config`, compilas, instalas módulos, instalas kernel e atualizas o bootloader. 

## Como pensar

A tua decisão de sair do dual boot para VM é boa engenharia. No dual boot, um erro no kernel/GRUB pode afetar a máquina principal. Na VM, o erro vira experiência controlada.

A pergunta principal nesta leitura é:

> “Estou a criar um ambiente onde posso falhar sem destruir o sistema principal?”

Por isso, antes de executar comandos, queremos saber **o papel de cada fase**:

* **Pacotes**: preparar toolchain e libs para construir kernel.
* **GRUB visível**: permitir escolher kernel antigo se o novo falhar.
* **Source separado em `~/linux-kernel`**: manter a experiência isolada.
* **`.config`**: snapshot das opções de compilação.
* **`EXTRAVERSION=-moker`**: etiqueta técnica para reconhecer o teu kernel no boot.
* **`make modules_install`**: instala módulos em `/lib/modules/KERNEL_VERSION`.
* **`make install`**: instala imagem do kernel em `/boot`.
* **`update-grub2`**: regista o novo kernel no menu de arranque.

## Pitfalls & troubleshooting

* **Assumir que dual boot e VM são iguais**: não são; na VM podes destruir e reconstruir rápido.
* **Compilar sem espaço suficiente**: kernel build pode ocupar muito espaço.
* **Não mostrar o GRUB**: se o kernel novo falhar, perdes a forma simples de voltar ao kernel antigo.
* **Não confirmar `uname -r` depois do reboot**: sem isso, não sabes se estás mesmo no `moker`.

## Alternativas / tradeoffs

**Abordagem segura:** fazer TT4 inteiro numa VM nova. Mais lento, mas limpo e reversível.
**Abordagem rápida:** continuar no dual boot. Mais direto, mas mais arriscado se GRUB/kernel ficarem mal configurados.

## Pergunta de decisão

A tua VM nova já tem **Ubuntu instalado no disco virtual**, ou ainda estás na fase de **Live ISO / instalação do sistema operativo**?


---
## Ação (1 passo)

Depois do `sudo reboot`, **confirma que a VM arrancou bem e verifica o kernel atual**:

```bash
uname -r
```

## Objetivo

Provar que a fase **1 — Tools and packages** ficou concluída e que continuas num sistema estável antes de mexer no GRUB/kernel source. O TT4 manda instalar `libssl-dev`, `libncurses5-dev`, `libelf-dev`, `bison`, `flex` e depois fazer reboot; é exatamente onde estás agora. 

## Como pensar

Neste ponto ainda **não criaste o teu kernel MOKER**. Só preparaste o ambiente de build.

A tua screenshot mostra instalação de pacotes como:

```text
gcc
flex
bison
libelf-dev
libssl-dev
```

Isto significa:

| Pacote           | Papel no kernel build                       |
| ---------------- | ------------------------------------------- |
| `gcc`            | compilar C do kernel                        |
| `bison` / `flex` | gerar parsers usados no build/configuração  |
| `libncurses-dev` | interface textual do `make menuconfig`      |
| `libelf-dev`     | manipulação de objetos ELF                  |
| `libssl-dev`     | partes criptográficas/certificados do build |

O próximo bloco do TT4 é **mostrar o GRUB**, porque vais precisar de escolher entre o kernel normal e o futuro `6.19.9-moker`. O PDF recomenda comentar `GRUB_TIMEOUT_STYLE=hidden`, pôr `GRUB_TIMEOUT=10`, correr `sudo update-grub2` e reboot. 

## Pitfalls & troubleshooting

* Se fizeres alterações no GRUB antes de confirmar que o reboot foi limpo, misturas problemas.
* Se `uname -r` não devolver algo normal, a VM pode ainda estar em instalação/live ou kernel inesperado.
* Se o ecrã ficar preto no reboot, pode ser VirtualBox/graphics, não kernel.
* Não avances para download do source ainda; primeiro valida o estado base.

## Alternativas / tradeoffs

**Seguir TT4 à risca:** reboot agora, depois GRUB. Mais seguro.
**Saltar reboot e continuar:** pode funcionar, mas perdes uma validação simples da VM.

## Pergunta de decisão

Depois do reboot, o `uname -r` mostra um kernel Ubuntu normal, por exemplo algo com `generic`?

---

## Ação (1 passo)

Agora faz o **bloco 2 do TT4: tornar o menu GRUB visível**.

Abre o ficheiro:

```bash
sudo nano /etc/default/grub
```

E altera estas linhas:

```bash
#GRUB_TIMEOUT_STYLE=hidden
GRUB_TIMEOUT=10
```

Depois grava e sai.

## Objetivo

Garantir que, quando instalares o kernel `moker`, consegues escolher no boot entre:

```text
Ubuntu kernel normal: 6.17.0-29-generic
Kernel MOKER futuro: 6.19.9-moker
```

Isto é a tua “rede de segurança” antes de mexeres no kernel. ⚙️

## Como pensar

Ainda não estamos a compilar kernel. Estamos a preparar **recuperabilidade**.

Pergunta de engenharia:

> “Se o meu kernel novo falhar no boot, tenho forma simples de voltar ao kernel antigo?”

O GRUB visível resolve exatamente isso.

## Pitfalls & troubleshooting

* Não apagar a linha `GRUB_TIMEOUT_STYLE`; só comentar com `#`.
* Não deixar `GRUB_TIMEOUT=0`, senão o menu passa demasiado rápido.
* Usar `sudo nano`, não editar sem permissões.
* Depois de gravar, ainda falta aplicar com `sudo update-grub2`, mas esse será o próximo passo.

## Alternativas / tradeoffs

**GRUB visível:** mais seguro para kernel lab.
**GRUB escondido:** arranque mais limpo, mas pior para debugging.

## Pergunta de decisão

Conseguiste editar e gravar o ficheiro `/etc/default/grub`?

---

# compilacao do kernel 

    make -j$(nproc)

- instalar modulos

    sudo make modules_install

- instalar imagem do kernel

    sudo make install

---

# full screen na VM

    xandr


---

instalar isto em vez do kcompile

    sudo apt install virtualbox-guest-utils virtualbox-guest-x11


