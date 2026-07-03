# Respostas — Avaliação Guião 3

## Ação — 1 passo

Copia estas respostas para o email/relatório do grupo e junta screenshots dos comandos:

```bash
ip a
ip route
cat /etc/resolv.conf
ping -c 4 192.168.1.1
ping -c 4 8.8.8.8
ping -c 4 google.com
getent ahostsv4 google.com
```

---

## 1) Ao colocar o IP no `vmbr3`, como é que as rotas são realizadas e como permitem o acesso à LAN?

Ao colocar o `vmbr3` na mesma rede da LAN da OPNsense, o host/cliente passa a conseguir comunicar diretamente com a interface LAN da firewall.

No nosso caso:

```text
OPNsense LAN: 192.168.1.1/24
C3:           192.168.1.142/24
Gateway C3:   192.168.1.1
```

Como ambos estão na rede `192.168.1.0/24`, o C3 consegue comunicar diretamente com a OPNsense pela LAN.

A rota local fica assim:

```text
192.168.1.0/24 dev eth0
```

E a rota para fora da LAN fica:

```text
default via 192.168.1.1
```

Isto significa que todo o tráfego que não pertence à rede local é enviado para a OPNsense. Depois, a OPNsense encaminha esse tráfego da LAN para a WAN, usando NAT.

Frase curta:

> O `vmbr3` liga o cliente à LAN da OPNsense. O cliente comunica diretamente com `192.168.1.1` na rede local e usa essa interface como gateway para chegar ao exterior.

---

## 2) Explique o funcionamento dos servidores recursivos

Um servidor DNS recursivo recebe pedidos DNS dos clientes e procura a resposta em nome deles.

Exemplo:

```text
C3 pergunta: qual é o IP de google.com?
DNS recursivo procura a resposta
DNS recursivo devolve o IP ao C3
```

Na prática, o cliente não precisa de contactar diretamente servidores root, TLD ou autoritativos. Ele apenas pergunta ao servidor DNS configurado.

No nosso guião:

```text
C3 → DNS 192.168.1.1 → OPNsense / Unbound
```

A OPNsense, através do serviço Unbound, atua como servidor DNS para a LAN. O cliente pergunta à OPNsense e esta resolve ou encaminha o pedido para outros servidores DNS.

Frase curta:

> Um servidor recursivo recebe a pergunta DNS do cliente, procura a resposta junto da hierarquia DNS ou de servidores configurados, guarda em cache e devolve o resultado ao cliente.

---

## 3) Qual a função dos servidores root no DNS?

Os servidores root são o primeiro nível da hierarquia DNS. Eles não sabem normalmente o IP final de `google.com`, mas sabem indicar para onde o pedido deve seguir.

Exemplo simplificado:

```text
Cliente quer google.com
Servidor root indica servidores .com
Servidor .com indica servidores autoritativos de google.com
Servidor autoritativo devolve o IP de google.com
```

Ou seja, os root servers ajudam a iniciar a resolução DNS, indicando quais são os servidores responsáveis pelos domínios de topo, como:

```text
.com
.org
.net
.pt
```

Frase curta:

> Os servidores root são o ponto inicial da hierarquia DNS. Eles encaminham a resolução para os servidores TLD corretos, como `.com`, `.pt` ou `.org`.

---

## 4) Explique sucintamente o funcionamento da firewall OPNsense

A OPNsense funciona como firewall entre duas redes: uma rede interna protegida, chamada LAN, e uma rede externa, chamada WAN.

No nosso caso:

```text
LAN: 192.168.1.1/24
WAN: 10.42.0.227/24
```

O cliente C3 está na LAN:

```text
C3: 192.168.1.142/24
Gateway: 192.168.1.1
DNS: 192.168.1.1
```

Quando o C3 quer aceder à Internet, envia o tráfego para a OPNsense. A firewall verifica as regras, permite ou bloqueia o tráfego, e quando permite, encaminha-o para a WAN usando NAT.

Também pode fornecer serviços à LAN, como:

* gateway;
* DHCP;
* DNS com Unbound;
* regras de firewall;
* NAT;
* logs de tráfego.

Frase curta:

> A OPNsense controla o tráfego entre LAN e WAN. Os clientes internos usam a OPNsense como gateway; a firewall aplica regras de segurança, faz NAT para permitir acesso ao exterior e pode fornecer serviços como DHCP e DNS.

---

# Resposta final curta para enviar

```text
1) Ao colocar o IP no vmbr3, o cliente/host fica na mesma rede da LAN da OPNsense. No nosso caso, a LAN da OPNsense é 192.168.1.1/24 e o C3 recebeu 192.168.1.142/24. Assim, a rota local 192.168.1.0/24 permite comunicação direta com a LAN, e a rota default via 192.168.1.1 envia o tráfego externo para a firewall.

2) Um servidor DNS recursivo recebe pedidos DNS dos clientes e procura a resposta em nome deles. Pode consultar a hierarquia DNS ou encaminhar para servidores configurados. No guião, o C3 usa 192.168.1.1 como DNS, ou seja, a OPNsense/Unbound resolve os nomes para a LAN.

3) Os servidores root são o nível inicial da hierarquia DNS. Eles não devolvem normalmente o IP final do domínio, mas indicam quais os servidores responsáveis pelo domínio de topo, como .com, .pt ou .org.

4) A OPNsense funciona como firewall entre a LAN e a WAN. No nosso caso, a LAN é 192.168.1.1/24 e a WAN é 10.42.0.227/24. O C3 usa a OPNsense como gateway e DNS. A firewall aplica regras, encaminha tráfego permitido, faz NAT para acesso ao exterior e pode prestar serviços como DHCP e DNS.
```

## Pitfall importante

Não escrevas que “o DHCP não funcionava”. O correto é:

> O DHCP funcionava; o problema inicial era o DNS estar configurado para `192.168.1.21` em vez de `192.168.1.1`.

**Pergunta de decisão:** queres agora fazer um **mini-relatório final do Guião 3 com screenshots esperados e frases de defesa oral**?
