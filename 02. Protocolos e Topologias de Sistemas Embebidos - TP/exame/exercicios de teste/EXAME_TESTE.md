## Exame Relâmpago PRSIEM — Estilo Recurso 🎯

Baseado no exame da época normal que enviaste: muito **V/F**, uma questão de **tcpdump TCP seq/ack**, e uma questão de **IPv6/SLAAC/sub-redes**. O exame normal tinha exatamente esta estrutura: conceitos iniciais, TCP, NAT/NAPT, STP/RSTP, MQTT, CAN/CAN-FD, depois `tcpdump`, depois IPv6/SLAAC/sub-redes. 

**Responde sem justificar primeiro.**
Formato recomendado:

```text
1.1: F V F V ...
2: XXXX=..., YYYY=...
3.1=...
...
```

---

# Parte 1 — Verdadeiro / Falso

## 1.1 Ethernet / VLAN

Indica **V** ou **F**.

```text
a) O endereço MAC Ethernet possui 48 bits. V
b) A Ethernet é usada principalmente em redes locais LAN. V
c) Numa rede Ethernet, todos os dispositivos têm obrigatoriamente o mesmo endereço MAC. F
d) VLANs permitem dividir uma rede Ethernet física em várias redes Ethernet virtuais. V
e) VLANs eliminam sempre a necessidade de routers entre redes diferentes. F
```

---

## 1.2 IPv4 / IPv6 / NDP

```text
a) Um cabeçalho IPv4 inclui um campo Protocol. V
b) Um cabeçalho IPv6 inclui um campo Protocol com esse nome. F
c) Um cabeçalho IPv6 tem 40 bytes. F
d) FE80::1234 é um endereço IPv6 Link-Local. V
e) NDP usa ICMPv6. F
f) NDP substitui funções que em IPv4 eram feitas por ARP. V
g) Router Advertisement é normalmente enviado por hosts finais. F
```

---

## 1.3 HTTP / MQTT

```text
a) Pedidos HTTP/1.1 GET incluem sempre Content-Length. V
b) HTTP/1.1 permite Protocol Upgrade. V
c) HTTP/2 pode usar o método POST. V
d) HTTP/2 sobre TCP elimina totalmente o head-of-line blocking. F
e) MQTT usa modelo publish/subscribe. V
f) Em MQTT, os clientes publicam diretamente uns para os outros sem broker. F
g) Um broker MQTT pode armazenar retained messages. V
h) MQTT QoS 0 garante entrega exatamente uma vez. F
```

---

## 1.4 RIP / STP / RSTP

```text
a) RIP é um protocolo Distance Vector. V
b) RIP usa Dijkstra para calcular caminhos. V
c) Link State tende a usar mais recursos computacionais do que Distance Vector. V
d) Link State normalmente converge mais lentamente do que Distance Vector. F
e) Split Horizon é uma técnica associada a Distance Vector. V
f) STP evita loops de camada 2. V
g) STP opera na camada 3. F
h) RSTP reduz o tempo de convergência face ao STP clássico. V
```

---

## 1.5 TCP / UDP / NAT / CAN

```text
a) UDP tem campo Sequence Number. F
b) TCP tem campo Window. V
c) TCP ACK indica o próximo byte esperado. V
d) SYN é usado no estabelecimento da ligação TCP. V
e) FIN consome um número de sequência. V
f) NAT elimina a necessidade de DHCP. F
g) NAPT altera portos TCP/UDP. V
h) Port Forward normalmente usa DNAT. V
i) Em CAN, menor ID significa maior prioridade. V
j) CAN-FD pode transportar até 64 bytes de dados. V
```

---

# Parte 2 — Escolha múltipla

## 2.1

No IPv6, o campo equivalente ao TTL do IPv4 chama-se:

```text
A) Protocol
B) Hop Limit - X 
C) Next Header
D) Flow Control
```

## 2.2

NAPT distingue múltiplos hosts internos usando:

```text
A) VLAN ID
B) Endereço MAC
C) Portos TCP/UDP - X
D) TTL
```

## 2.3

Qual é o encapsulamento correto?

```text
A) TCP transporta IP
B) IP transporta Ethernet
C) Ethernet transporta IP, IP transporta TCP - X
D) UDP transporta Ethernet
```

## 2.4

Em IPv6, quem fragmenta pacotes?

```text
A) Routers intermédios
B) Switches Ethernet
C) Host emissor -X
D) Broker MQTT
```

## 2.5

Em CAN clássico extended frame:

```text
A) O identificador pode ter 29 bits - X
B) O campo de dados pode ter 64 bytes
C) Existe endereço MAC obrigatório
D) ID maior ganha arbitragem
```

---

# Parte 3 — TCP `tcpdump`

Sessão TCP já estabelecida:

```text
pc1.4000 > srv.80: Flags [P.], seq 1200, ack 5000, win 100, length 30
srv.80 > pc1.4000: Flags [P.], seq 5000, ack AAAA, win 90, length BBBB
pc1.4000 > srv.80: Flags [.], seq CCCC, ack DDDD, win 100, length 20
pc1.4000 > srv.80: Flags [.], seq EEEE, ack DDDD, win 100, length 10
srv.80 > pc1.4000: Flags [P.], seq 5060, ack FFFF, win 90, length 40
pc1.4000 > srv.80: Flags [.], seq GGGG, ack HHHH, win 100, length 0
```

Determina:

```text
AAAA = 1230
BBBB = 60
CCCC = 1230
DDDD = 5060
EEEE = 1250
FFFF = 1260
GGGG = 1260
HHHH = 6000
```

---

# Parte 4 — IPv6 / SLAAC / Sub-redes

Uma empresa tem a gama:

```text
2002:1c2:0:b800::/58
```

Quer dividir a rede por:

```text
4 edifícios
```

Cada edifício terá pisos com redes `/64`, porque os sensores usam **SLAAC**.

## 4.1

Quantos endereços existem na gama original?

```text

    Resposta como potência de 2: 128 - 58 = 2^60
```

## 4.2

Qual é o último endereço da gama original?

0X10 DE SALTO COM /60 ; 8000 + 10 + 10 + 10 + 10 = 840
```text
Resposta: 2002:1C2:0:B83f::/58 
```

## 4.3

Indica se pertencem à gama original: **E** ou **F**

```text
a) 2002:1c2:0:b800:aaaa:bbbb:cccc:dddd E
b) 2002:1c2:0:b83f::1 E
c) 2002:1c2:0:b840::1 F
d) 2002:1c2:0:b7ff::ffff F
e) 2002:1c2:0:b8c0::1234 E
```

## 4.4

Propõe as gamas dos 4 edifícios:

```text
Edifício 0 = 2002:1C2:0:B800::/60
Edifício 1 = 2002:1C2:0:B810::/60
Edifício 2 = 2002:1C2:0:B820::/60
Edifício 3 = 2002:1C2:0:B840::/60
```

## 4.5

Para o **Edifício 2**, indica as primeiras 4 redes `/64` de pisos:

```text
Piso 0 = 2002:1C2:0:B820::/64
Piso 1 = 2002:1C2:0:B821::/64
Piso 2 = 2002:1C2:0:B822::/64
Piso 3 = 2002:1C2:0:B823::/64
```

## 4.6

Qual é a última rede `/64` dentro do Edifício 2?

```text
Resposta: 2002:1C2:0:B82f::/64
```

---

## Pergunta de decisão

Responde ao exame todo. Eu corrijo como exame real, marco erros conceptuais e digo o que rever nos últimos minutos.


---

## Ação — exercício IPv6 final 🎯

Resolve só este, rápido e com atenção ao **4.º bloco**:

```text
Gama original: 2002:1c2:0:d200::/57
```

A empresa quer dividir em:

```text
2 edifícios logo 2^1

57 + 1 = 58
```

Cada piso usa `/64` por causa de SLAAC.

### Perguntas

```text
1) Quantos endereços tem a gama original? Responde como potência de 2.
128-57 = 2 ^ 71
2) Qual é a última rede /64 da gama original?

3) Edifício A = 2002:1c2:0:27f::/64
4) Edifício B = 2002:1c2:0:3e0::/64

5) Primeiras 3 redes /64 do Edifício B:
   Piso B.1 = 2002:1c2:0:201::/64
   Piso B.2 = 2002:1c2:0:202::/64
   Piso B.3 = 2002:1c2:0:203::/64

6) O endereço 2002:1c2:0:d27f::1 pertence à gama original? E/F e
7) O endereço 2002:1c2:0:d280::1 pertence à gama original? E/F f
```

## Objetivo

Fixar o caso:

```text
/57 → intervalo de 0x80 redes /64
```

## Como pensar

```text
/57 até /64 = 7 bits
2^7 = 128 redes /64
salto = 0x80
```

Logo uma gama `/57` começa na base e vai até:

```text
base + 0x7f
```

## Pergunta de decisão

Quais são as tuas 7 respostas?
