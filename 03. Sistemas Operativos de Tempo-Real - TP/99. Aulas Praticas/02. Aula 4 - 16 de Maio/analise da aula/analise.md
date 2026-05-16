vou ver o tt4

terminal 

ção — 1 passo 🚀

Abre o terminal e confirma primeiro em que sistema estás a trabalhar:

uname -r
lsb_release -a
pwd

![alt text](image.png)


Antes de mexer no kernel , precisamos validar 3 coisas.:

    1. Versao atual do kernel com uname -r
    2. Distribuicao Linux com lsb_release -a
    3. Diretorio atual com pwd

Isto e importante porque o TT4 e sobre criar e compilar um kernel proprio chamado *MOKER*. O pdf comeca por instalar ferramentas, mostrar o menu GRUB, descarregar o kernel Linux, configurar, alterar o EXTRAVERSION = -moker compilar e instalar o kernel

    Hoje nao e para "decorar comandos" e para perceber a cadeia: 

sistema atual
   ↓
ferramentas de compilação
   ↓
código-fonte do kernel
   ↓
.config
   ↓
Makefile com -moker
   ↓
make
   ↓
install
   ↓
GRUB
   ↓
boot no novo kernel

#############################################################

## Ação — 1 passo 🚀

Agora instala **só as ferramentas necessárias para compilar o kernel**:

```bash
sudo apt-get update
sudo apt-get install libssl-dev libncurses5-dev libelf-dev bison flex build-essential
```

## Objetivo

Preparar o Ubuntu 24.04 para conseguir executar depois:

```bash
make menuconfig
make
sudo make modules_install
sudo make install
```

O TT4 pede precisamente instalar `libssl-dev`, `libncurses5-dev`, `libelf-dev`, `bison` e `flex`; estas dependências são necessárias para configurar e compilar o kernel. 

O teu estado inicial está bom:

```text
Kernel atual: 6.17.0-23-generic
Distribuição: Ubuntu 24.04.4 LTS noble
```

## Como pensar

Antes de compilar kernel, pensa assim:

```text
make menuconfig precisa de ncurses
assinatura/crypto precisa de openssl/libssl
ELF/kernel build precisa de libelf
parsers do kernel precisam de bison/flex
compilação C precisa de gcc/make/build-essential
```

Isto ainda **não mexe no GRUB**, **não instala kernel novo**, **não altera boot**. É preparação segura.

######

Como pensar

Este reboot ainda não muda o kernel. Vais continuar, em princípio, no:

6.17.0-23-generic

O reboot aqui serve para começar a fase seguinte com o sistema estável antes de mexer no GRUB e no código-fonte do kernel.

#####

Ação — 1 passo 🚀
Agora ativa o menu do GRUB para poderes escolher kernels no boot:
sudo nano /etc/default/grub
Dentro do ficheiro, procura estas linhas:
GRUB_TIMEOUT_STYLE=hiddenGRUB_TIMEOUT=0
Altera para:
#GRUB_TIMEOUT_STYLE=hiddenGRUB_TIMEOUT=10

# Objectivo

Objetivo

Quando compilares e instalares o kernel -moker, vais precisar escolher entre:

Ubuntu normal kernel
Ubuntu kernel -moker

O TT4 manda comentar GRUB_TIMEOUT_STYLE=hidden e mudar GRUB_TIMEOUT de 0 para 10, para o menu GRUB aparecer durante o arranque.

# como pensar 

Como pensar

Ainda não estás a instalar kernel. Estás só a preparar o “seletor de kernels”.

kernel atual existe
   ↓
futuro kernel -moker será instalado
   ↓
GRUB precisa mostrar os dois
   ↓
tu escolhes no boot


################

![alt text](image-1.png)


O PDF usa gedit, mas o objetivo real não é usar esse editor; é editar o ficheiro /etc/default/grub para o menu GRUB aparecer no arranque. O TT4 diz para comentar GRUB_TIMEOUT_STYLE=hidden, mudar GRUB_TIMEOUT para 10, guardar, e depois atualizar o GRUB.

Como pensar
gedit = editor gráfico
nano  = editor de terminal

Ambos editam o mesmo ficheiro. O resultado final é igual.

####################################

Falta só comentar a primeira linha com #. Assim o GRUB deixa de estar escondido e fica visível durante 10 segundos no arranque, como pedido no TT4.

Como pensar

GRUB_TIMEOUT=10 sozinho define tempo, mas se GRUB_TIMEOUT_STYLE=hidden continuar ativo, o menu pode continuar escondido. O # transforma essa linha em comentário.


####################

Agora atualiza o GRUB:

sudo update-grub2


Objetivo

Aplicar a alteração feita em:

/etc/default/grub

#######################

Como pensar

Ainda não criaste o kernel MOKER. Só preparaste o sistema para, mais tarde, poderes escolher entre kernels.

GRUB visível
   ↓
mais tarde: kernel normal + kernel -moker
   ↓
escolha segura no boot

########################################

# Ponto 4 - makemenu config



Sim, está certo. Agora abre o menu de configuração e sai sem alterar nada:

make menuconfig

Quando abrir o ecrã azul/cinzento:

Exit
Save? → Yes
Objetivo

Validar que o sistema consegue abrir o configurador do kernel baseado em ncurses e guardar a configuração .config.

O output que tens está correto:

*** Default configuration is based on 'x86_64_defconfig'
#
# configuration written to .config
#

Isto significa que o .config foi criado com sucesso.

Como pensar

O defconfig criou uma configuração base. O menuconfig permite editar opções do kernel, mas nesta aula o TT4 diz para abrir e escolher Exit, sem alterar opções.

defconfig
   ↓
.config criado
   ↓
menuconfig
   ↓
validar interface/configuração
   ↓
guardar

###########################

# Ponto 6.

Ação — 1 passo 🚀

Agora começa a compilação do kernel:

cd linux-6.19.9-moker
make -j$(nproc)
Objetivo

Compilar o kernel 6.19.9-moker.

No PDF, o ponto 6 usa simplesmente:

make

Mas make -j$(nproc) usa os cores disponíveis da máquina e normalmente é mais rápido. O resultado final é o mesmo: compilar o kernel antes de instalar módulos e kernel.

Como pensar

Agora entramos na fase pesada:

source code + .config + EXTRAVERSION
   ↓
make
   ↓
kernel compilado

Só depois disto faz sentido executar:

sudo make modules_install
sudo make install


###############

Objetivo

O kernel já foi compilado e instalado. A imagem mostra:

Found linux image: /boot/vmlinuz-6.19.9-moker
Found initrd image: /boot/initrd.img-6.19.9-moker
done

Isto significa que o GRUB já detetou o teu kernel 6.19.9-moker. É exatamente o resultado esperado depois de sudo make modules_install e sudo make install, passos indicados no ponto 6 do TT4.

Como pensar

Agora o fluxo está assim:

compilação             ✅
modules_install        ✅
make install           ✅
GRUB atualizado        ✅
reboot                 ← agora
validar uname -r       ← depois

Depois do reboot, a validação será:

uname -r

Esperado:

6.19.9-moker
