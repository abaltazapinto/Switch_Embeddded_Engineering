# PRSIEM - Protocolos e Topologias de Sistemas Embebidos

**Teste Final - Maio 2026**


---

## Questoes 1.0 a 1.4 - Conceitos iniciais

### 1.0 - HTTP / MQTT / protocolos de aplicacao

| Afirmacao | V | F |
|---|---:|---:|
| O endereco MAC Ethernet possui 64 bits. | [ ] | [F ] |
|A Ethernet é uma tecnologia de rede utilizada principalmente em redes locais (LAN); | [v ] | [ ] |
| Numa rede Ethernet, todos os dispositivos partilham o mesmo endereço MAC; | [ ] | [f ] |
| As VLANs permitem implementar uma rede Ethernet física em múltiplas redes Ethernet virtuais; | [v ] | [ ] |
|As VLANs complementam a necessidade de routers em redes empresariais.| [ ] | [f ] |

## 1.2

| Afirmação | V | F |
|---|---|---|
| Um cabeçalho IPv4 inclui um campo Next Header; | [ ] | [f] |
| Um cabeçalho IPv6 tem 320 bits; | [v ] | [ ] |
| O protocolo NDP não se utiliza em IPv6; | [ ] | [ f] |
| "FE80::aaaa:9999" é um endereço IPv6 do tipo Link Local; | [ v] | [ ] |
| O protocolo NDP define um mecanismo de deteção de endereços duplicados; | [v ] | [ ] |
| Uma mensagem de Router Solicitation pode ser endereçada a um endereço de unicast; | [ ] | [f ] |
| Uma mensagem de Router Advertisement é normalmente enviada por um encaminhador (router); | [ ] | [ ] |

## 1.3

| Afirmação | V | F |
|---|---|---|
| Os pedidos HTTP/1.1 pelo método GET incluem sempre o cabeçalho (header) `content-length`; | [ ] | [ f] |
| O mecanismo de Protocol Upgrade do HTTP/1.1 permite que o cliente solicite a mudança para um protocolo diferente; | [v] | [ ] |
| Os pedidos HTTP/2 podem utilizar o método POST; | [v] | [ ] |
| A utilização de HTTP/2 sobre TCP evita o problema de head-of-line blocking; | [ ] | [f] |
| Os pedidos HTTP/1.0 identificam o método na primeira linha; | [ ] | [f] |
| Uma resposta HTTP/1.1 é normalmente transportada na mesma sessão TCP do pedido respetivo; | [v ] | [ ] |

## 1.4

| Afirmação | V | F |
|---|---|---|
| Para configurar um encaminhador com protocolo RIP (Routing Information Protocol), é necessário definir a tabela de encaminhamento; | [ ] | [f] |
| Os protocolos de encaminhamento do tipo Link State requerem mais recursos computacionais do que os protocolos do tipo Distance Vector; | [v] | [ ] |
| Os protocolos de encaminhamento do tipo Link State apresentam tempos de convergência mais longos do que os protocolos do tipo Distance Vector; | [ ] | [f] |
| O protocolo RIP (Routing Information Protocol) utiliza multicast para enviar informação aos encaminhadores seus vizinhos; | [ ] | [f] |
| A técnica de Split Horizon só se justifica em protocolos de encaminhamento do tipo Link State; | [ ] | [f] |

---


## Questoes 1.5 a 1.9 - Verdadeiro / Falso

### 1.5 - TCP

| Afirmacao | V | F |
|---|---:|---:|
| A aplicacao do algoritmo de Nagle pode aumentar a latencia de uma transmissao. | [v] | [ ] |
| No mecanismo de confirmacao seletiva, **Selective Acknowledgement**, utilizam-se 64 bits para identificar cada um dos blocos a confirmar explicitamente. | [ ] | [f] |
| A flag SYN e utilizada no processo de encerramento de uma ligacao TCP. | [ ] | [f] |
| Numa ligacao TCP, a aplicacao do controlo de congestionamento depende de um acordo previo entre os extremos da ligacao. | [ ] | [f] |
| O numero de sequencia, **Sequence number**, incluido num cabecalho TCP, tem 64 bits. | [ ] | [f] |
| Um cabecalho TCP inclui um campo com o numero de sequencia, **Sequence number**. | [v ] | [ ] |
| Um cabecalho TCP inclui um campo **Window** com a dimensao da janela de controlo de fluxo. | [v] | [ ] |

### 1.6 - NAT / NAPT

| Afirmacao | V | F |
|---|---:|---:|
| A utilizacao de NAT, **Network Address Translation**, elimina a necessidade de utilizacao de DHCP. | [ ] | [ f] |
| O mecanismo de **Port Forward** destina-se a permitir o acesso a servicos privados, a partir da rede publica. | [ v] | [ ] |
| Um encaminhador NAT substitui o endereco de destino dos datagramas dirigidos a rede privada. | [v] | [ ] |
| O cabecalho de um datagrama IP numa rede publica pode conter um endereco de origem privado. | [ ] | [f] |
| Os router IP que efetuam NAPT, **Network Address and Port Translation**, nao sao compativeis com QUIC. | [ ] | [f] |

### 1.7 - STP / RSTP

| Afirmacao | V | F |
|---|---:|---:|
| O Rapid Spanning Tree Protocol, **RSTP**, foi desenvolvido para reduzir o tempo de convergencia relativamente ao STP classico. | [V] | [ ] |
| O protocolo STP opera na camada de rede, **Layer 3**, do modelo OSI. | [ ] | [F] |
| O STP, **Spanning Tree Protocol**, utiliza mensagens BPDU para trocar informacao entre switches. | [V] | [ ] |
| O protocolo STP foi concebido para evitar loops de camada 2 em redes Ethernet com caminhos redundantes. | [V] | [ ] |

### 1.8 - MQTT

| Afirmacao | V | F |
|---|---:|---:|
| O protocolo MQTT segue um modelo de comunicacao **publish/subscribe**. | [V] | [ ] |
| Em MQTT, os clientes publicam mensagens diretamente para outros clientes sem intervencao de um broker. | [ ] | [F] |
| O broker MQTT pode armazenar mensagens retidas para novos subscritores, **subscribers**. | [V] | [ ] |
| O QoS 0 em MQTT garante a entrega exata de uma mensagem uma unica vez. | [ ] | [F] |
| Um unico pacote MQTT `SUBSCRIBE` pode incluir multiplos topicos/subscricoes. | [V] | [ ] |
| O protocolo MQTT segue um modelo de comunicacao **publish/subscribe**. | [V] | [ ] |

### 1.9 - CAN / CAN-FD

| Afirmacao | V | F |
|---|---:|---:|
| Em CAN classico com trama extendida, **extended frame**, e possivel utilizar identificadores de 29 bits. | [V] | [ ] |
| O identificador de uma trama CAN serve apenas para identificar o destinatario da mensagem. | [ ] | [F] |
| Em CAN, mensagens com identificadores numericamente mais altos tem maior prioridade. | [ ] | [F] |
| O protocolo CAN implementa automaticamente retransmissao quando deteta erros numa trama. | [V] | [ ] |
| O CAN Low-Speed Fault-Tolerant foi concebido para operar tipicamente a velocidades mais baixas do que o CAN High-Speed. | [v] | [] |
| O protocolo CAN depende obrigatoriamente de um endereco MAC unico por dispositivo. | [ ] | [F] |
| CAN-FD permite taxas de transmissao superiores as do CAN classico durante a fase de dados. | [V] | [ ] |
| Em CAN-FD, o campo de dados pode transportar ate 64 bytes. | [V] | [ ] |

---

## Questao 2 - TCP / `tcpdump`

A lista seguinte apresenta um extrato da saida produzida pelo `tcpdump` durante uma sessao TCP estabelecida entre 2 maquinas.

```text
pc1.myhome.pt.2387 > srv.porto.pt.ftp: Flags [P.], seq 382,  ack 891,  win 115, length 16
srv.porto.pt.ftp  > pc1.myhome.pt.2387: Flags [P.], seq 891,  ack SSSS, win 91,  length XXXX
pc1.myhome.pt.2387 > srv.porto.pt.ftp: Flags [.],  seq YYYY, ack WWWW, win 115, length 3
pc1.myhome.pt.2387 > srv.porto.pt.ftp: Flags [.],  seq RRRR, ack WWWW, win 115, length 23
srv.porto.pt.ftp  > pc1.myhome.pt.2387: Flags [P.], seq 942, ack ZZZZ, win 91, length 79
pc1.myhome.pt.2387 > srv.porto.pt.ftp: Flags [P.], seq ZZZZZ,   ack 1021, win 115,  length 0
```

**Determine os valores em falta:**

| Variavel | Valor |
|---|---|
| XXXX | 51 |
| RRRR | 401 |
| YYYY | 398 |
| ZZZZ | 424 |
| SSSS | 398 |
| WWWW | 942 |

---

## Questao 3 - IPv6 / SLAAC / Sub-redes

Uma empresa pretende implementar uma rede de sensores nos diversos pisos dos seus 2 edificios, **Edificio A** e **Edificio B**.

A empresa tem disponivel a gama de enderecos proprios:

```text
2002:1c2:0:b460::/59
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
Resposta: _________2 ELEVaDO A 69___________
```

### 3.2

Qual e o ultimo endereco desta gama?

```text
Resposta: 2002:1C2:B47F:FFFF:FFFF:FFFF:FFFF:FFFF
```

### 3.3

Para os seguintes enderecos, indique quais pertencem (`E`) e quais nao pertencem (`F`) a esta gama.

| Endereco IPv6 | E | F |
|---|---:|---:|
| `2002:1c20::b46:aaaa:bbbb:cccc:dd` | [ ] | [F] |
| `2002:1c2:0:b46e:8800:1:22cc:eeee` | [E] | [ ] |
| `2002:1c2::b4c0:dddd:cccc:bbbb` | [ ] | [F] |
| `2002:1c2:0:b476::b928:cc:bbaa` | [E] | [ ] |

### 3.4

Utilizando a gama de enderecos proprios disponibilizada, proponha gamas IPv6 para as sub-redes dos 2 edificios da empresa.

| Sub-rede | Gama IPv6 proposta |
|---|---|
| Edificio A | 2002:1c2:0:b460::/60 |
| Edificio B | 2002:1c2:0:b470::/60 |

### 3.5

Utilizando as gamas propostas para os edificios respetivos, defina gamas IPv6 para as sub-redes de cada um dos pisos.

| Piso | Gama IPv6 proposta |
|---|---|
| Piso A.3 | 2002:1c2:0:b460::/64 |
| Piso A.2 | 2002:1c2:0:b461::/64 |
| Piso A.1 | 2002:1c2:0:b462::/64 |
| Piso B.2 | 2002:1c2:0:b470::/64 |
| Piso B.1 | 2002:1c2:0:b471::/64 |

---


Primeira tentativa acabei 44 min.