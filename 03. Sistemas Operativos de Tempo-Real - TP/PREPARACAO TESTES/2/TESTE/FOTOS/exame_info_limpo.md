# PRSIEM - Protocolos e Topologias de Sistemas Embebidos

**Teste Final - Maio 2026**

> Documento reconstruido a partir das fotografias. Algumas zonas estavam inclinadas/desfocadas; os campos assinalados como `[ilegivel]` devem ser confirmados no original.

---

## Questao 2 - TCP / `tcpdump`

A lista seguinte apresenta um extrato da saida produzida pelo `tcpdump` durante uma sessao TCP estabelecida entre 2 maquinas.

```text
pc1.myhome.pt.2387 > srv.porto.pt.ftp: Flags [P.], seq 382,  ack 891,  win 115, length 16
srv.porto.pt.ftp  > pc1.myhome.pt.2387: Flags [P.], seq 891,  ack SSSS, win 91,  length XXXX
pc1.myhome.pt.2387 > srv.porto.pt.ftp: Flags [.],  seq YYYY, ack WWWW, win 115, length 0
srv.porto.pt.ftp  > pc1.myhome.pt.2387: Flags [P.], seq RRRR, ack WWWW, win 115, length 3
pc1.myhome.pt.2387 > srv.porto.pt.ftp: Flags [P.], seq 94,   ack ZZZZ, win 91,  length 23
srv.porto.pt.ftp  > pc1.myhome.pt.2387: Flags [.],  seq ZZZZ, ack 1021, win 115, length 0
```

**Determine os valores em falta:**

| Variavel | Valor |
|---|---|
| XXXX | __________ |
| RRRR | __________ |
| YYYY | __________ |
| ZZZZ | __________ |
| SSSS | __________ |
| WWWW | __________ |

---

## Questao 3 - IPv6 / SLAAC / Sub-redes

Uma empresa pretende implementar uma rede de sensores nos diversos pisos dos seus 2 edificios, **Edificio A** e **Edificio B**.

A empresa tem disponivel a gama de enderecos proprios:

```text
2002:1c20:b460::/59
```

Pretende implementar isolamento **Layer 3** entre os edificios e entre os diversos pisos de cada edificio.

Os sensores deverao usar enderecos IPv6 autoconfigurados (**SLAAC**).

### Estrutura dos edificios

| Edificio A | Edificio B |
|---|---|
| Piso A.3 | Piso B.2 |
| Piso A.2 | Piso B.1 |
| Piso A.1 |  |

### 3.1

Por quantos enderecos e composta a gama de enderecos proprios disponibilizada?

> Apresente o resultado como uma potencia de 2.

```text
Resposta: ____________________
```

### 3.2

Qual e o ultimo endereco desta gama?

```text
Resposta: ____________________
```

### 3.3

Para os seguintes enderecos, indique quais pertencem (`E`) e quais nao pertencem (`F`) a esta gama.

| Endereco IPv6 | E | F |
|---|---:|---:|
| `2002:1c20::b46:aaaa:bbbb:cccc:dd` | [ ] | [ ] |
| `2002:1c20:b46e:8800:1:22cc:eeee` | [ ] | [ ] |
| `2002:1c2::b4c0:dddd:cccc:bbbb` | [ ] | [ ] |
| `2002:1c20:b476:b928:cc:bbaa` | [ ] | [ ] |

### 3.4

Utilizando a gama de enderecos proprios disponibilizada, proponha gamas IPv6 para as sub-redes dos 2 edificios da empresa.

| Sub-rede | Gama IPv6 proposta |
|---|---|
| Edificio A | ____________________ |
| Edificio B | ____________________ |

### 3.5

Utilizando as gamas propostas para os edificios respetivos, defina gamas IPv6 para as sub-redes de cada um dos pisos.

| Piso | Gama IPv6 proposta |
|---|---|
| Piso A.3 | ____________________ |
| Piso A.2 | ____________________ |
| Piso A.1 | ____________________ |
| Piso B.2 | ____________________ |
| Piso B.1 | ____________________ |

---

## Questoes 1.5 a 1.9 - Verdadeiro / Falso

### 1.5 - TCP

| Afirmacao | V | F |
|---|---:|---:|
| A aplicacao do algoritmo de Nagle pode aumentar a latencia de uma transmissao. | [ ] | [ ] |
| No mecanismo de confirmacao seletiva, **Selective Acknowledgement**, utilizam-se 64 bits para identificar cada um dos blocos a confirmar explicitamente. | [ ] | [ ] |
| A flag SYN e utilizada no processo de encerramento de uma ligacao TCP. | [ ] | [ ] |
| Numa ligacao TCP, a aplicacao do controlo de congestionamento depende de um acordo previo entre os extremos da ligacao. | [ ] | [ ] |
| O numero de sequencia, **Sequence number**, incluido num cabecalho TCP, tem 64 bits. | [ ] | [ ] |
| Um cabecalho TCP inclui um campo com o numero de sequencia, **Sequence number**. | [ ] | [ ] |
| Um cabecalho TCP inclui um campo **Window** com a dimensao da janela de controlo de fluxo. | [ ] | [ ] |

### 1.6 - NAT / NAPT

| Afirmacao | V | F |
|---|---:|---:|
| A utilizacao de NAT, **Network Address Translation**, elimina a necessidade de utilizacao de DHCP. | [ ] | [ ] |
| O mecanismo de **Port Forward** destina-se a permitir o acesso a servicos privados, a partir da rede publica. | [ ] | [ ] |
| Um encaminhador NAT substitui o endereco de destino dos datagramas dirigidos a rede privada. | [ ] | [ ] |
| O cabecalho de um datagrama IP numa rede publica pode conter um endereco de origem privado. | [ ] | [ ] |
| Os router IP que efetuam NAPT, **Network Address and Port Translation**, nao sao compativeis com QUIC. | [ ] | [ ] |

### 1.7 - STP / RSTP

| Afirmacao | V | F |
|---|---:|---:|
| O Rapid Spanning Tree Protocol, **RSTP**, foi desenvolvido para reduzir o tempo de convergencia relativamente ao STP classico. | [ ] | [ ] |
| O protocolo STP opera na camada de rede, **Layer 3**, do modelo OSI. | [ ] | [ ] |
| O STP, **Spanning Tree Protocol**, utiliza mensagens BPDU para trocar informacao entre switches. | [ ] | [ ] |
| O protocolo STP foi concebido para evitar loops de camada 2 em redes Ethernet com caminhos redundantes. | [ ] | [ ] |

### 1.8 - MQTT

| Afirmacao | V | F |
|---|---:|---:|
| O protocolo MQTT segue um modelo de comunicacao **publish/subscribe**. | [ ] | [ ] |
| Em MQTT, os clientes publicam mensagens diretamente para outros clientes sem intervencao de um broker. | [ ] | [ ] |
| O broker MQTT pode armazenar mensagens retidas para novos subscritores, **subscribers**. | [ ] | [ ] |
| O QoS 0 em MQTT garante a entrega exata de uma mensagem uma unica vez. | [ ] | [ ] |
| Um unico pacote MQTT `SUBSCRIBE` pode incluir multiplos topicos/subscricoes. | [ ] | [ ] |
| O protocolo MQTT segue um modelo de comunicacao **publish/subscribe**. | [ ] | [ ] |

### 1.9 - CAN / CAN-FD

| Afirmacao | V | F |
|---|---:|---:|
| Em CAN classico com trama extendida, **extended frame**, e possivel utilizar identificadores de 29 bits. | [ ] | [ ] |
| O identificador de uma trama CAN serve apenas para identificar o destinatario da mensagem. | [ ] | [ ] |
| Em CAN, mensagens com identificadores numericamente mais altos tem maior prioridade. | [ ] | [ ] |
| O protocolo CAN implementa automaticamente retransmissao quando deteta erros numa trama. | [ ] | [ ] |
| O CAN Low-Speed Fault-Tolerant foi concebido para operar tipicamente a velocidades mais baixas do que o CAN High-Speed. | [ ] | [ ] |
| O protocolo CAN depende obrigatoriamente de um endereco MAC unico por dispositivo. | [ ] | [ ] |
| CAN-FD permite taxas de transmissao superiores as do CAN classico durante a fase de dados. | [ ] | [ ] |
| Em CAN-FD, o campo de dados pode transportar ate 64 bytes. | [ ] | [ ] |
