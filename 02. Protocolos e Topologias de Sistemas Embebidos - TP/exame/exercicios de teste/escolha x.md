## Ação — mini-teste escolha múltipla 🎯

Responde só com:

```text
1A 2B 3C 4D ...
```

Sem justificar agora.

---

### 1. IPv4 / IPv6 headers

No cabeçalho IPv4, o campo que identifica TCP, UDP ou ICMP chama-se:

A) Next Header
B) Protocol
C) EtherType
D) Payload Length


b
---

### 2. IPv6

No cabeçalho IPv6, o campo equivalente para identificar o próximo protocolo/cabeçalho chama-se:

A) Protocol
B) Header Checksum
C) Next Header
D) IHL

c
---

### 3. NAT

NAPT distingue várias máquinas internas usando principalmente:

A) Endereços MAC
B) Portos TCP/UDP
C) TTL
D) VLAN ID

b
---

### 4. Ethernet

O endereço MAC Ethernet tem:

A) 32 bits
B) 48 bits
C) 64 bits
D) 128 bits
b
---

### 5. STP

O objetivo principal do STP é:

A) Atribuir endereços IP automaticamente
B) Evitar loops de camada 2
C) Encaminhar pacotes IPv6
D) Comprimir cabeçalhos HTTP
b
---

### 6. RIP

RIP é um protocolo de encaminhamento do tipo:

A) Link State
B) Distance Vector
C) Path Vector
D) Source Routing
b
---

### 7. CAN

Em CAN, uma mensagem com ID numericamente menor tem:

A) Menor prioridade
B) Maior prioridade
C) Prioridade igual
D) Prioridade dependente do MAC

b
---

### 8. MQTT

Em MQTT, os clientes comunicam normalmente através de:

A) Broker
B) Router OSPF
C) Switch STP
D) Servidor DHCP
a
---

### 9. TCP

Um ACK TCP indica:

A) O último byte recebido
B) O próximo byte esperado
C) O tamanho da janela Ethernet
D) O número total de pacotes IP
b
---

### 10. UDP

O cabeçalho UDP inclui:

A) Sequence Number
B) Acknowledgment Number
C) Source Port
D) Window Size
b X | C

O UDP tem portos, mas nao tem ACK nem, Sequence Number. Nosmateriais da cadeira, a desmultiplexagem TCP/IP usa portas na camada TCP/UDP ENQUANTO ACK/retransmissao sao fubcoes associadas ao transporte fiavel como TCP.

## Objetivo

Aquecer com armadilhas rápidas antes de voltar ao IPv6 hexadecimal.

## Pergunta de decisão

Quais são as tuas 10 respostas?

---


v/f

1. Em MQTT, dois clientes publicam mensagens diretamente um para o outro sem broker. F
2. UDP tem campo Source Port. V
3. UDP tem campo ACK. F
4. TCP tem campo ACK. V

---

Numa comunicação TCP/IP típica, qual encapsulamento está correto?

A) Segmento TCP transporta datagrama IP

B) Datagrama IP transporta segmento TCP

C) Trama Ethernet transporta segmento TCP diretamente, sem IP

D) Pacote UDP transporta trama Ethernet

B

Qual afirmação é correta?

A) O campo EtherType do cabeçalho Ethernet identifica portas TCP/UDP

B) O campo Protocol do IPv4 identifica TCP, UDP ou ICMP

C) O campo Next Header do IPv6 identifica o endereço MAC de destino

D) O campo Source Port do TCP identifica o protocolo IP usado

B

---

v/f

1. IPv4 tem campo TTL. v
2. IPv6 tem campo TTL. f
3. IPv6 tem campo Hop Limit. v
4. IPv6 tem Header Checksum. f

---

1. Em IPv6, routers podem fragmentar pacotes como em IPv4. F
2. Em IPv6, pode existir cabeçalho de extensão de fragmentação. V
3. Em IPv4, existem campos relacionados com fragmentação no cabeçalho base. V
4. Em IPv6, a ausência de fragmentação em routers ajuda a simplificar o processamento. V

---

Qual afirmação é falsa?

A) SLAAC usa Router Advertisement para obter o prefixo de rede
B) SLAAC normalmente usa prefixos /64
C) NDP substitui funções que em IPv4 eram feitas por ARP
D) SLAAC exige sempre um servidor DHCPv6 para atribuir endereço IPv6

---

1. SLAAC precisa obrigatoriamente de DHCPv6 para criar endereço global. F
2. Router Advertisement pode anunciar o prefixo IPv6. V
3. NDP usa ICMPv6. V
4. Neighbor Solicitation pode ser usado para descobrir endereço de camada 2. V

---
Qual afirmação é falsa?

A) Router Solicitation é uma mensagem NDP enviada por hosts
B) Router Advertisement pode ser enviado por routers
C) Neighbor Solicitation pode ser usado em Duplicate Address Detection
D) ARP é usado em IPv6 para descobrir endereços MAC

Certo.

D) ARP é usado em IPv6 para descobrir endereços MAC

É falsa