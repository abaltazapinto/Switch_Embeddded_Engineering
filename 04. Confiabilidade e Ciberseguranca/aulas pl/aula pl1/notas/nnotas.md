## Ação — 1.º passo: desenha a topologia antes de abrir o Proxmox

Copia este esquema para o teu caderno e entende **quem está ligado a quem**:

```txt
                 Rede do laboratório / Internet
                         10.0.32.0/24
                              |
                            vmbr2
                              |
        ------------------------------------------------
        |                                              |
       C1                                      WAN da OPNsense
   Container                                  IP por DHCP
   em vmbr2                                         |
                                                    |
                                             Firewall OPNsense
                                                    |
                                                  LAN
                                                    |
                                                  vmbr3
                                           bridge interna isolada
                                                    |
                              --------------------------------
                              |                              |
                             C2                             C3
                         Container                      Container
                          em vmbr3                       em vmbr3
```

### Objetivo

Este passo prova que percebes a ideia central dos dois guiões:

> **vmbr2** = rede exterior/laboratório
> **vmbr3** = rede interna isolada
> **OPNsense** = firewall/router entre vmbr2 e vmbr3

Sem isto, os comandos de `nmap`, IP, DNS e SSH ficam mecânicos e confusos.

---

## Como pensar

Pensa nas `vmbr` como **switches virtuais** dentro do Proxmox.

| Elemento     | Analogia                        | Função                           |
| ------------ | ------------------------------- | -------------------------------- |
| `vmbr2`      | switch ligado ao mundo exterior | dá acesso à rede do laboratório  |
| `vmbr3`      | switch privado na bancada       | só liga máquinas internas        |
| OPNsense WAN | porta virada para fora          | recebe IP por DHCP               |
| OPNsense LAN | porta virada para dentro        | serve a rede interna             |
| C1           | máquina “do lado de fora”       | testa a firewall a partir da WAN |
| C2/C3        | máquinas “do lado de dentro”    | testam LAN, serviços e scans     |

O ponto importante:

```txt
C2 -> C3
```

deve funcionar porque estão ambos na LAN `vmbr3`.

Mas:

```txt
C1 -> C2
```

não deve funcionar livremente, porque a firewall deve proteger a LAN.

---

## O que os guiões querem ensinar

### Guião 1 — Proxmox

O foco é perceber:

* criar containers LXC;
* criar VMs;
* ligar máquinas a bridges;
* testar IP, DNS e Internet;
* usar SSH com password e depois com chave;
* perceber diferença entre bridge com rede externa e bridge isolada.

### Guião 2 — Firewall OPNsense

O foco é perceber:

* criar VM firewall;
* dar duas interfaces à firewall:

  * WAN em `vmbr2`;
  * LAN em `vmbr3`;
* testar comunicação entre containers;
* usar `nmap`;
* perceber diferença entre scan a uma máquina interna e scan à firewall;
* verificar resolução DNS.

---

## Correções importantes nos guiões

### 1. Inconsistência no Ubuntu

No Guião 1 diz:

```txt
Criar container LXC com imagem ubuntu 22.04
```

mas nos recursos aparece:

```txt
ubuntu-24.04.iso
```

Isto mistura duas coisas diferentes:

| Tipo          |        Usa ISO? | Exemplo                            |
| ------------- | --------------: | ---------------------------------- |
| VM            |             Sim | Ubuntu ISO, Kali ISO, OPNsense ISO |
| LXC container | Normalmente não | template Ubuntu 22.04/24.04        |

Para o exercício, segue a intenção: **container LXC Ubuntu**, não instalação por ISO.

---

### 2. Erro provável no comando `nmap`

O Guião 2 mostra:

```bash
nmap -sA -<IP-C3>
```

Isto está errado.

O provável correto é:

```bash
nmap -sA <IP-C3>
```

ou, se quiseres velocidade semelhante ao outro scan:

```bash
nmap -sA -T4 <IP-C3>
```

Mesma coisa para:

```bash
nmap -sA -<IP-firewall>
```

Deve ser:

```bash
nmap -sA <IP-firewall>
```

---

## Conceito crítico: `nmap -sS` vs `nmap -sA`

| Comando    | Nome     | Pergunta que faz                  |
| ---------- | -------- | --------------------------------- |
| `nmap -sS` | SYN scan | “Esta porta parece aberta?”       |
| `nmap -sA` | ACK scan | “Existe firewall a filtrar isto?” |

O `-sS` tenta perceber se há serviços abertos.

O `-sA` é mais subtil: não procura exatamente portas abertas; tenta perceber se há regras de firewall a bloquear ou deixar passar pacotes.

---

## Pitfalls & troubleshooting

1. **WAN e LAN trocadas na OPNsense**
   Resultado: a firewall fica “ao contrário” e os testes não fazem sentido.

2. **vmbr3 ligada por engano a uma placa física**
   Resultado: a rede deixa de ser isolada.

3. **Containers sem gateway correto**
   Resultado: conseguem falar dentro da LAN, mas não chegam ao exterior.

4. **DNS falha mas IP funciona**
   Resultado: há conectividade, mas o servidor DNS ou forwarding DNS está mal configurado.

---

## Alternativas / tradeoffs

### Abordagem A — aprender pela rede primeiro

Começas por desenhar e prever tráfego:

```txt
quem consegue fazer ping a quem?
quem deve ser bloqueado?
quem resolve DNS?
```

Melhor para entender cibersegurança.

### Abordagem B — aprender clicando no Proxmox primeiro

Começas logo a criar VMs/containers.

Mais rápido, mas mais arriscado: podes configurar algo errado sem perceber porquê.

Para esta aula, eu escolheria **Abordagem A**.

---

## Pergunta de decisão

Queres que o próximo passo seja **montar a tabela de endereços IP esperada para C1, C2, C3, WAN e LAN da OPNsense**?


A AULA E sobre máquinas virtuais + containers + redes virtuais + firewall

########################################################################

![alt text](image.png)

Excelente — agora sim ✅
O Proxmox Web UI está acessível em:
https://localhost:8006

Browser do teu PC
https://localhost:8006
        ↓
VirtualBox NAT forwarding
        ↓
Proxmox dentro da VM
https://10.0.2.15:8006

######################

Objetivo

Entrar na interface gráfica onde vais fazer o Guião 1:

Criar containers LXC
Criar VMs
Configurar redes/bridges
Testar SSH
Preparar base para OPNsense

Agora já saímos da parte de instalação. A partir daqui começa realmente o laboratório.

##################################################

Objetivo

Confirmar a password do utilizador root dentro do container c1.

Este container vai ficar com:

Hostname: c1
User: root
Password: 12345
CT ID: 100

![alt text](image-1.png)


![alt text](image-2.png)

Storage: local-lvm
Disk size: 8 GiB

![alt text](image-3.png)

512 MiB  → mínimo apertado
1024 MiB → seguro para laboratório
2048 MiB → desnecessário para C1

########################33

Name: eth0
Bridge: vmbr0
Firewall: marcado
IPv6: Static / None

###############################

![alt text](image-4.png)


#############################

Excelente. Primeiro LXC criado ✅

Tens agora:

CT 100
Hostname: c1
Ubuntu 24.04
TASK OK

Isto prova que o Proxmox já consegue criar containers.


![alt text](image-5.png)

CT 100 / c1
IP: 10.0.2.16
Apache2 instalado
Serviço esperado: porta 80

![alt text](image-6.png)

#############################

pve host
  ↓ curl http://10.0.2.16
c1 container
  ↓
Apache2 responde

###########################

Objetivo

Instalar nmap no host Proxmox para fazer scan ao container c1.

Depois vamos testar:

nmap 10.0.2.16

e deverás ver a porta HTTP aberta:

80/tcp open http


c1      = alvo / servidor Apache
pve     = máquina que observa/testa
nmap    = ferramenta de enumeração


Que serviços estão expostos?
Que portas estão abertas?
O que um atacante ou auditor consegue ver?

![alt text](image-7.png)

Validação feita ✅

O nmap encontrou:

22/tcp open  ssh
80/tcp open  http

Isto prova que o container c1 está exposto na rede com:

SSH  → porta 22
HTTP → porta 80 / Apache2

Ação — 1 passo

Na Shell do pve, corre:

nmap -sV -p 22,80 10.0.2.16
Objetivo

Descobrir que serviços e versões estão por trás das portas abertas.

O scan anterior respondeu:

porta aberta

Agora queremos algo mais útil para cibersegurança:

porta aberta + serviço + versão provável\

# nmap -sV -p 22,80 10.0.2.16

![alt text](image-8.png)



####################

Perfeito — resultado correto ✅

O nmap -sV identificou:

22/tcp open  ssh   OpenSSH 9.6p1 Ubuntu
80/tcp open  http  Apache httpd 2.4.58

Isto prova:

c1 está vivo
SSH está exposto
Apache está exposto
nmap consegue identificar serviços e versões


###############################

Como pensar

Até agora fizeste isto:

pve → nmap/curl → c1

Mas numa topologia de cibersegurança queremos algo mais parecido com:

c2 → nmap/curl → c1

O Proxmox deve ser a infraestrutura, não a máquina de teste.

########################################

Como pensar

Isto é o conceito de golden image / golden container:

1. Preparas uma máquina base
2. Validaste serviços
3. Paras a máquina
4. Clonas
5. Modificas rede/IP/hostname no clone

É muito usado em virtualização real.


# guiao

3.1 Container LXC → ligar à bridge vmbr2 → DHCP → Internet
3.2 VM Kali       → ligar à bridge vmbr2 → DHCP → Internet
3.3 Criar vmbr3   → sem interface física → rede isolada


####################

Como pensar

Tens duas bridges com funções diferentes:

Bridge	No guião	No teu PC	Função
vmbr2	rede do laboratório com Internet	vmbr0	DHCP + Internet
vmbr3	rede isolada	vmbr3	só comunicação entre containers


<@@@@@@3###########3


vmbr2 do guião  ≈  vmbr0 no teu Proxmox

################

| Requisito do guião            | Estado                                        |
| ----------------------------- | --------------------------------------------- |
| Criar container LXC Ubuntu    | ✅ feito: `c1`                                 |
| Ligar à bridge com Internet   | ✅ feito: `vmbr0`                              |
| IP por DHCP                   | ✅ feito: `10.0.2.16`                          |
| Instalar `apache2`            | ✅ feito                                       |
| Instalar `nmap`               | ✅ feito                                       |
| Apache responde               | ✅ feito                                       |
| Acesso por IP/DNS ao exterior | quase validado, mas falta evidência explícita |


Requisito do guião	Estado
Criar container LXC Ubuntu	✅ feito: c1
Ligar à bridge com Internet	✅ feito: vmbr0
IP por DHCP	✅ feito: 10.0.2.16
Instalar apache2	✅ feito
Instalar nmap	✅ feito
Apache responde	✅ feito
Acesso por IP/DNS ao exterior	quase validado, mas falta evidência explícita
Ação — 1 passo

Na consola do c1, corre este comando de evidência:

hostname -I && ping -c 3 8.8.8.8 && ping -c 3 google.com && systemctl is-active apache2 && nmap --version
Objetivo

Fechar o ponto 3.1 com prova clara:

IP atribuído
Internet por IP funciona
DNS funciona
Apache ativo
nmap instalado

Depois disso, sim: passamos para 3.2 — criar a VM Kali.

######################################

Sim — 3.1 está fechado ✅

A evidência está perfeita:

IP atribuído: 10.0.2.17
Ping por IP: 8.8.8.8 OK
Ping por DNS: google.com OK
Apache2: active
nmap: instalado

Portanto o ponto 3.1 — Criação de um container está cumprido.

A vmbr3 já criada não faz mal. Só não a usamos ainda. Ela pertence ao ponto 3.3.

################################################3

# 3.2

c1 Ubuntu LXC → template
Kali VM       → ISO


   3.2 VM Kali + bridge com Internet + DHCP + testar IP/DNS



#####################

![alt text](image-9.png)

Essa interface será usada para criar:

vmbr2

e cumprir o ponto 3.2:

Kali VM → vmbr2 → DHCP → acesso exterior

Como pensar

O que estamos a construir é isto:

VirtualBox Adapter 1 → Proxmox vmbr0 → gestão do Proxmox
VirtualBox Adapter 2 → Proxmox vmbr2 → rede da Kali

Assim não destruímos o acesso atual ao Proxmox.

VirtualBox Adapter 2
        ↓
NIC nova dentro do Proxmox
        ↓
vmbr2
        ↓
VM Kali

Enable Network Adapter: checked
Attached to: Bridged Adapter
Name: wlp0s20f3
Promiscuous Mode: Allow All
Cable Connected: checked

####################

![alt text](image-10.png)

ip -br link

![alt text](image-11.png)

