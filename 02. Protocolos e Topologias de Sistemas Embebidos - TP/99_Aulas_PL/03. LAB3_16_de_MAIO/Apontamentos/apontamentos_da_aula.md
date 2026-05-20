Objetivo

Confirmar que tens a topologia da aula prática pronta para arrancar no Kathará. O enunciado indica exatamente esta rede: prsiem-net-6, usada no laboratório IPv6 & SLACC .

Como pensar

Nesta prática, o foco já não é NAT/IPv4. Agora estás a entrar em:

IPv6 + SLAAC + Router Advertisement + Link-local addresses

A rede tem três zonas principais:

Rede	IPv4	IPv6
N	203.0.113.0/24	2023:3:27::/80
A	203.0.114.0/24	2023:3:27:a::/64
B	203.0.115.0/24	2023:3:27:b::/64

Isto está no enunciado da prática .


########################

No terminal de cada nó da1, da2, da3, lê o MAC da interface eth0:

ip link show eth0

Procura a linha:

link/ether xx:xx:xx:xx:xx:xx

Esse é o endereço MAC que vais pôr na tabela.

Objetivo

Preencher a primeira coluna real da secção 1.4 — Identificadores IPv6/EUI-64: o enunciado pede para registar os MACs de da1, da2 e da3 e depois determinar o identificador IPv6/EUI-64 de 64 bits.

Como pensar

Para gerar o EUI-64 a partir do MAC:

Exemplo conceptual:

MAC:    aa:bb:cc:dd:ee:ff
Divide ao meio:
aa:bb:cc     dd:ee:ff
Insere ff:fe no meio:
aa:bb:cc:ff:fe:dd:ee:ff
Inverte o bit U/L do primeiro byte.
Na prática: faz XOR com 0x02 no primeiro byte.
aa XOR 02 = a8
Agrupa em blocos IPv6 de 16 bits:
a8bb:ccff:fedd:eeff

Esse é o identificador IPv6/EUI-64.


# professor disse para mudar 3.2

203:3:27:14::->2023:3:27:A::

#####################o

Em da1, executa:

ip addr show eth0

E copia duas coisas:

link/ether xx:xx:xx:xx:xx:xx
inet6 fe80::....
Objetivo

A pergunta 1.4 pede exatamente isto: registar os endereços MAC de da1, da2, da3 e determinar o identificador IPv6/EUI-64 de 64 bits desses nós. O enunciado também diz para confirmar primeiro os endereços configurados com ip addr show.

# Da1

![alt text](image.png)

link/ether 56:1e:67:ce:2d:59 brd ff:ff:ff:ff:ff:ff

Campo	Valor
Resposta 1 Pergunta 1	56:1e:67:ce:2d:59
Resposta 2 Pergunta 1	541e:67ff:fece:2d59
Objetivo

Converter o MAC de 48 bits de da1 para o identificador IPv6/EUI-64 de 64 bits.

Como pensar

Partimos do MAC:

56:1e:67:ce:2d:59

Dividimos em duas metades:

56:1e:67   ce:2d:59

Inserimos ff:fe no meio:

56:1e:67:ff:fe:ce:2d:59

Agora alteramos o bit U/L do primeiro byte:

56 XOR 02 = 54

Resultado final:

54:1e:67:ff:fe:ce:2d:59

Em formato IPv6, agrupado de 16 em 16 bits:

541e:67ff:fece:2d59


###############################################

# Maquina virtual TOPOLOGIAS


1.2 Sub-redes

Rede N
IPv4: 203.0.113.0/24
IPv6: 2023:3:27::/80

Rede A
IPv4: 203.0.114.0/24
IPv6: 2023:3:27:a::/64

Rede B
IPv4: 203.0.115.0/24
IPv6: 2023:3:27:b::/64


1.3 Endereços atribuídos

gwi eth0
IPv4: 203.0.113.254
IPv6: 2023:3:27::1ff

srv eth0
IPv4: 203.0.113.99
IPv6: 2023:3:27::99

ra eth0
IPv4: 203.0.114.254
IPv6: 2023:3:27:a::1ff

ra eth1
IPv4: 203.0.113.10
IPv6: 2023:3:27::a

rb eth0
IPv4: 203.0.115.254
IPv6: 2023:3:27:b::1ff

rb eth1
IPv4: 203.0.113.11
IPv6: 2023:3:27::b

da1 eth0
IPv4: 203.0.114.1

da2 eth0
IPv4: 203.0.114.2

da3 eth0
IPv4: 203.0.114.3

db1 eth0
IPv4: 203.0.115.1

db2 eth0
IPv4: 203.0.115.2

db3 eth0
IPv4: 203.0.115.3


1.4 Identificadores IPv6/EUI-64

da1
Endereço MAC: 56:1e:67:ce:2d:59
Identificador IPv6/EUI-64: 541e:67ff:fece:2d59

da2
Endereço MAC: 
Identificador IPv6/EUI-64: 

da3
Endereço MAC: 
Identificador IPv6/EUI-64: 

---
# da2

## Ação — 1 passo

Sim, esse é o **MAC de `da2`**. Preenche assim:

| Nó    | Endereço MAC        | Identificador IPv6/EUI-64 |
| ----- | ------------------- | ------------------------- |
| `da2` | `c2:b8:76:f1:3f:96` | `c0b8:76ff:fef1:3f96`     |

## Objetivo

Completar a linha de `da2` na pergunta 1.4.

## Como pensar

Partimos do MAC:

```text
c2:b8:76:f1:3f:96
```

Divide-se ao meio:

```text
c2:b8:76   f1:3f:96
```

Insere-se `ff:fe`:

```text
c2:b8:76:ff:fe:f1:3f:96
```

Altera-se o bit U/L do primeiro byte:

```text
c2 XOR 02 = c0
```

Resultado:

```text
c0:b8:76:ff:fe:f1:3f:96
```

Formato IPv6/EUI-64:

```text
c0b8:76ff:fef1:3f96
```

## Pitfalls

* Não uses o endereço completo `fe80::c0b8:76ff:fef1:3f96/64`.
* No Moodle mete só `c0b8:76ff:fef1:3f96`.
* O primeiro byte muda de `c2` para `c0`.

## Pergunta de decisão

Agora manda o `link/ether` de `da3`.
---

# DA3

## Ação — 1 passo

Para `da3`, preenche assim:

| Nó    | Endereço MAC        | Identificador IPv6/EUI-64 |
| ----- | ------------------- | ------------------------- |
| `da3` | `d6:62:3a:ad:38:bc` | `d462:3aff:fead:38bc`     |

## Objetivo

Completar a última linha da pergunta **1.4 Identificadores IPv6/EUI-64**.

## Como pensar

O teu terminal mostra:

```text
link/ether d6:62:3a:ad:38:bc
inet6 fe80::d462:3aff:fead:38bc/64
```

Logo:

```text
MAC da3:     d6:62:3a:ad:38:bc
EUI-64 da3: d462:3aff:fead:38bc
```

A conversão confirma:

```text
d6 XOR 02 = d4
```

## Tabela final para o Moodle

```text
da1
MAC: 56:1e:67:ce:2d:59
EUI-64: 541e:67ff:fece:2d59

da2
MAC: c2:b8:76:f1:3f:96
EUI-64: c0b8:76ff:fef1:3f96

da3
MAC: d6:62:3a:ad:38:bc
EUI-64: d462:3aff:fead:38bc
```

## Pitfalls

* Não colocar `fe80::`.
* Não colocar `/64`.
* Não trocar `d6` com `d4`: o MAC começa por `d6`, mas o EUI-64 começa por `d4`.

---

# ROUTER SOLICITATION && ROUTER ADVERTISEMENT

## Ação — 1 passo

Antes da **3.2 Router Advertisement**, faz primeiro a **3.1 Router Solicitation**: no terminal do **`ra`**, executa:

```bash
tcpdump -n -i eth0 icmp6
```

## Objetivo

Capturar as mensagens **RS — Router Solicitation** vindas de `da1`, `da2` e `da3`. A tabela da pergunta pede **3 mensagens RS**, com origem, nome do nó, destino e descrição do destino. O enunciado manda monitorizar ICMPv6 na porta `eth0` do nó `ra` .

## Como pensar

A ordem correta é:

```text
3.1 RS  → os hosts pedem informação ao router
3.2 RA  → o router anuncia prefixo/default gateway
3.3 SLAAC → os hosts configuram endereço global IPv6
```

Ou seja, **não saltes já para `systemctl start radvd`**. Primeiro queremos observar se os nós estão a enviar pedidos.

Normalmente vais ver algo parecido com:

```text
IP6 fe80::xxxx > ff02::2: ICMP6, router solicitation
```

A interpretação será:

```text
Origem: endereço fe80::... do da1/da2/da3
Nome: da1 / da2 / da3
Destino: ff02::2
Descrição: All Routers
```

## Pitfalls

* Tens de correr o `tcpdump` em `ra`, não em `da1`.
* Interface correta: `eth0`, porque `eth0` de `ra` está ligada à rede A.
* Pode não aparecer imediatamente; às vezes é preciso esperar ou reiniciar um nó.
* `ff02::2` é multicast link-local para **todos os routers**, não é endereço de um host.

## Pergunta de decisão

Quando correres `tcpdump -n -i eth0 icmp6` no `ra`, aparecem linhas com destino `ff02::2`?


###############################

---

## Ação — 1 passo

Não esperes aí: carregaste o comando no **`ra`**, mas esse comando era para correr no **`da1`**.

Deixa o `tcpdump` a correr no `ra` e abre o terminal **`root@da1:/#`**. Aí executa:

```bash
ip link set eth0 down && ip link set eth0 up
```

## Objetivo

Forçar o `da1` a emitir uma mensagem **Router Solicitation** para o destino multicast:

```text
ff02::2
```

Esse destino significa **All Routers**.

## Como pensar

Neste momento tens:

```text
ra → está a escutar ICMPv6 em eth0 ✅
da1 → ainda não foi forçado a pedir Router Advertisement ❌
```

O `tcpdump` só mostra pacotes quando algum nó envia tráfego. Reiniciar `eth0` no próprio `ra` não gera a RS que queremos observar.

## Pitfalls

* O comando `ip link set eth0 down/up` tem de ser em `da1`, `da2` ou `da3`.
* Não faças `Ctrl+C` no `tcpdump` enquanto estás a testar.
* Se não aparecer em `da1`, repete depois em `da2`.
* Se mesmo assim não aparecer, passamos para `rdisc6` ou reiniciamos um nó.

## Pergunta de decisão

Depois de correres o comando em `da1`, apareceu no `ra` uma linha com `router solicitation`?

sim

---

## Ação — 1 passo

A linha que apareceu **não é RS**. É **NS — Neighbor Solicitation**:

```text
ICMP6, neighbor solicitation
```

Para forçar uma **Router Solicitation**, deixa o `tcpdump` a correr no `ra` e executa isto no **`da1`**:

```bash
rdisc6 eth0
```

## Objetivo

Gerar uma mensagem:

```text
ICMP6, router solicitation
```

para conseguires preencher a tabela **3.1 Router Solicitation**.

O que tens agora:

```text
fe80::88b5:1fff:fe2d:314b > ff02::1:ff2d:314b: ICMP6, neighbor solicitation
```

Isto é o `da1` a perguntar:
“Quem tem este endereço IPv6?”
Não é o `da1` a perguntar por routers.

## Como pensar

Para a tabela **3.1**, procuras linhas deste tipo:

```text
IP6 fe80::... > ff02::2: ICMP6, router solicitation
```

A tabela ficaria conceptualmente assim:

| Campo            | Valor esperado                     |
| ---------------- | ---------------------------------- |
| Mensagem         | `RS`                               |
| Origem endereço  | `fe80::...` do `da1`, `da2`, `da3` |
| Origem nome      | `da1`, `da2`, `da3`                |
| Destino endereço | `ff02::2`                          |
| Descrição        | `All Routers`                      |

## Pitfalls

* `neighbor solicitation` ≠ `router solicitation`.
* `ff02::1:ffxx:xxxx` é multicast de **solicited-node**, usado por Neighbor Discovery.
* Para RS, o destino deve ser **`ff02::2`**.
* Se `rdisc6` não existir, o sistema vai dizer `command not found`.

## Pergunta de decisão

Quando executas `rdisc6 eth0` no `da1`, aparece no `ra` uma linha com `router solicitation`?

---
# da 1 router solicitation

## Ação — 1 passo

Perfeito — agora já tens **RS do `da1`**. Preenche uma linha da tabela **3.1 Router Solicitation** assim:

```text
Mensagem: RS
Origem Endereço: fe80::88b5:1fff:fe2d:314b
Origem Nome: da1
Destino Endereço: ff02::2
Destino Descrição: All Routers
```

## Objetivo

Registar uma mensagem **Router Solicitation** real capturada no `ra`.

A tua captura mostra:

```text
fe80::88b5:1fff:fe2d:314b > ff02::2: ICMP6, router solicitation
```

Isto significa:

```text
da1 perguntou aos routers da rede:
“Há algum router aí para me anunciar configuração IPv6?”
```

## Como pensar

* `fe80::88b5:1fff:fe2d:314b` é o endereço **link-local** do `da1`.
* `ff02::2` é multicast IPv6 para **All Routers**.
* `router solicitation` é a mensagem **RS** que a pergunta quer.

## Pitfalls

* Não uses a linha `neighbor solicitation`; essa não serve para a tabela RS.
* A descrição do destino deve ser `All Routers`, não `All Nodes`.
* Para completar a tabela, precisas de repetir o `rdisc6 eth0` em `da2` e `da3`.
* Mantém o `tcpdump` a correr no `ra`.

## Pergunta de decisão

Queres fazer agora o mesmo em `da2` para capturar a segunda linha RS?


---

# IANA

## Ação — 1 passo

Perfeito — agora já tens **RS do `da1`**. Preenche uma linha da tabela **3.1 Router Solicitation** assim:

```text
Mensagem: RS
Origem Endereço: fe80::88b5:1fff:fe2d:314b
Origem Nome: da1
Destino Endereço: ff02::2
Destino Descrição: All Routers
```

## Objetivo

Registar uma mensagem **Router Solicitation** real capturada no `ra`.

A tua captura mostra:

```text
fe80::88b5:1fff:fe2d:314b > ff02::2: ICMP6, router solicitation
```

Isto significa:

```text
da1 perguntou aos routers da rede:
“Há algum router aí para me anunciar configuração IPv6?”
```

## Como pensar

* `fe80::88b5:1fff:fe2d:314b` é o endereço **link-local** do `da1`.
* `ff02::2` é multicast IPv6 para **All Routers**.
* `router solicitation` é a mensagem **RS** que a pergunta quer.

---
# da2

## Ação — 1 passo

Sim — para `da2`, a origem deve ser:

```text
fe80::c0b8:76ff:fef1:3f96
```

Preenche a linha do `da2` assim:

```text
Mensagem: RS
Origem Endereço: fe80::c0b8:76ff:fef1:3f96
Origem Nome: da2
Destino Endereço: ff02::2
Destino Descrição: All Routers
```

## Objetivo

Usar o endereço **link-local** do `da2` como origem da mensagem Router Solicitation.

## Como pensar

Tu já tinhas calculado o EUI-64 do `da2`:

```text
c0b8:76ff:fef1:3f96
```

O endereço link-local junta:

```text
fe80:: + EUI-64
```

Logo:

```text
fe80::c0b8:76ff:fef1:3f96
```

## Pitfalls

* Para a tabela **RS**, aqui usas o endereço completo com `fe80::`.
* Para a tabela **EUI-64**, usas só `c0b8:76ff:fef1:3f96`.
* O destino continua sempre `ff02::2`.
* A descrição continua `All Routers`.

## Pergunta de decisão

Queres preencher já a linha do `da3` também?
---

# da3 e IANA

## Ação — 1 passo

Corrige a tabela para ficar assim:

```text
Mensagem: RS

Linha 1
Origem Endereço:  fe80::88b5:1fff:fe2d:314b
Origem Nome:      da1

Linha 2
Origem Endereço:  fe80::c0b8:76ff:fef1:3f96
Origem Nome:      da2

Linha 3
Origem Endereço:  fe80::d462:3aff:fead:38bc
Origem Nome:      da3

Destino Endereço: ff02::2
Destino Descrição: All Routers
```

## Objetivo

Sim: tens de fazer **duas coisas**:

1. **Identificar os nomes** dos nós pelos endereços de origem:

   * `fe80::88b5:...` → `da1`
   * `fe80::c0b8:...` → `da2`
   * `fe80::d462:...` → `da3`

2. **Usar a lista oficial da IANA** para descrever o destino:

   * `ff02::2` → `All Routers`

## Como pensar

A tua captura de RS tem esta estrutura:

```text
fe80::... > ff02::2: ICMP6, router solicitation
```

Lê-se assim:

```text
origem > destino: tipo de mensagem
```

Portanto:

```text
fe80::... = quem enviou
ff02::2   = grupo multicast que recebeu
```

A IANA entra só para confirmar o significado oficial de `ff02::2`.

## Pitfalls

* No `da3`, escreveste `0::d462...`; deve ser **`fe80::d462...`**.
* `ff02::2` não vai na origem.
* `All Routers` não vai no nome do nó; vai na descrição do destino.
* Como o Moodle parece ter só uma caixa para destino, basta preencher `ff02::2` e `All Routers` uma vez.

## Pergunta de decisão

Queres avançar agora para a **3.2 Router Advertisement**?


---

3,2 NO temrinal de ra verificar primeiro se o ficheioro radvd.conf esta correto

    radvd -c

---

apos isso arrancar o servico radvd no ra

    systemctl start radvd


papel de ra :

    antes: ra estava só a escutar/capturar
    agora: ra vai anunciar prefixo IPv6 + informação de router

---

Agora no terminal de da2 , comeca a escutar os Router Advertisements:

    tcpdump -n -1 eth0 icmp6

---

antes: ra estava só a escutar/capturar
agora: ra vai anunciar prefixo IPv6 + informação de router


---

## Ação — 1 passo

Ótimo, já capturaste o **RA**. Para a tabela **3.2 Router Advertisement**, preenche assim:

```text
Mensagem: RA
Origem Endereço:  fe80::1cd4:7eff:fe35:2ad5
Origem Nome:      ra
Destino Endereço: ff02::1
Destino Descrição: All Nodes
```

## Objetivo

Registar uma mensagem **Router Advertisement** enviada pelo router `ra` para todos os nós da rede local.

A tua captura mostra:

```text
fe80::1cd4:7eff:fe35:2ad5 > ff02::1: ICMP6, router advertisement
```

Interpretação:

```text
Origem  → fe80::1cd4:7eff:fe35:2ad5 = ra
Destino → ff02::1 = All Nodes
Tipo    → Router Advertisement = RA
```

## Como pensar

Na 3.1 tinhas:

```text
RS: host → routers
da1/da2/da3 → ff02::2
ff02::2 = All Routers
```

Agora tens:

```text
RA: router → hosts
ra → ff02::1
ff02::1 = All Nodes
```

A IANA serve para confirmar oficialmente os nomes dos grupos multicast:

```text
ff02::1 = All Nodes
ff02::2 = All Routers
```

## Pitfalls

* `rdisc6` ter dado `Timed out` antes não invalida a captura; o `tcpdump` apanhou o RA depois.
* Para a tabela, usa a linha que diz **router advertisement**, não as linhas antigas de **router solicitation**.
* O nome da origem é `ra`, não `da2`.
* A descrição do destino é `All Nodes`, não `All Routers`.

## Pergunta de decisão

Queres avançar para a **3.3 Autoconfiguração** e verificar os IPv6 globais de `da1`, `da2`, `da3`?
---

, vamos progffessor

---

no terminal da1 cverificar que ja apareceu IPv6 global da rede A

ifconfig

---

## Ação — 1 passo

No terminal de **`da1`**, verifica que já apareceu um IPv6 global da rede A:

```bash
ifconfig
```

Procura uma linha `inet6` que comece por:

```text
2023:3:27:a:
```

## Objetivo

Confirmar a **autoconfiguração SLAAC**: o `da1` deve ter recebido o prefixo anunciado pelo `ra` e
---


## Ação — 1 passo

O `da1` **ainda não recebeu o IPv6 global** `2023:3:27:a:...`. No terminal de **`da1`**, força um pedido ao router:

```bash
rdisc6 eth0
```

## Objetivo

Fazer o `da1` pedir explicitamente um **Router Advertisement** ao `ra`, para depois configurar o endereço IPv6 global via SLAAC.

Neste momento o `ifconfig` do `da1` só mostra:

```text
inet6 fe80::88b5:1fff:fe2d:314b
```

Isto é apenas **link-local**. Para a secção 3.3, queremos também algo como:

```text
inet6 2023:3:27:a:88b5:1fff:fe2d:314b
```

## Como pensar

O endereço global esperado é:

```text
prefixo da rede A + EUI-64 do da1
```

Ou seja:

```text
2023:3:27:a::/64 + 88b5:1fff:fe2d:314b
=
2023:3:27:a:88b5:1fff:fe2d:314b
```

## Pitfalls

* O `radvd` pode demorar a anunciar periodicamente.
* `rdisc6` pode mostrar `Timed out`, mas mesmo assim o `tcpdump` pode capturar RA.
* Se o endereço global não aparecer, temos de verificar se o prefixo em `/etc/radvd.conf` está correto.
* Não preenchas ainda a tabela 3.3 só com `fe80::`; ela quer o endereço atribuído da rede A.

## Pergunta de decisão

Depois de `rdisc6 eth0` no `da1`, o comando `ifconfig` mostra algum `inet6` começado por `2023:3:27:a:`?


---

nao deu 

vou ativar a aceitacao de router advertisements no da1

    sysctl -w net.ipv6.conf.eth0.accept_ra=2

## Ação — 1 passo

Ativa a aceitação de Router Advertisements no **`da1`**:

```bash
sysctl -w net.ipv6.conf.eth0.accept_ra=2
```

---

## Ação — 1 passo

Está correto: o IPv6 global do `da1` já apareceu ✅
Para a tabela **3.3**, preenche a linha de `da1` assim:

```text
da1 Endereço IPv6: 2023:3:27:a:88b5:1fff:fe2d:314b
Default Gateway:   fe80::1cd4:7eff:fe35:2ad5
```

## Objetivo

Registar o endereço IPv6 atribuído ao `da1` e o gateway anunciado pelo `ra`.

No teu `ifconfig`, agora aparece:

```text
inet6 2023:3:27:a:88b5:1fff:fe2d:314b prefixlen 64 scopeid 0x0<global>
```

E o `rdisc6` indicou que o router veio de:

```text
from fe80::1cd4:7eff:fe35:2ad5
```

## Como pensar

Para a tabela 3.3:

```text
Endereço IPv6 = prefixo global da rede A + EUI-64 do nó
Default Gateway = endereço link-local do router ra
```

Ou seja:

```text
2023:3:27:a::/64 + 88b5:1fff:fe2d:314b
=
2023:3:27:a:88b5:1fff:fe2d:314b
```

## Pitfalls

* Não uses o `fe80::...` do `da1` como endereço IPv6 da tabela.
* O gateway não é `2023:3:27:a::1ff`; nesta prática, usa o link-local do `ra`.
* O `/64` não precisa de ir no campo se o Moodle só pede endereço.
* Como configurámos manualmente, faz o mesmo raciocínio para `da2` e `da3`.

## Pergunta de decisão

Queres calcular agora o endereço IPv6 global de `da2`?


---

