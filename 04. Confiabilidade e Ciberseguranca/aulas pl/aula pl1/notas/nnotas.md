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
