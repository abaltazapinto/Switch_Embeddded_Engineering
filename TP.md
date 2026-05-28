## TP1

1. Escreva o número 011011002 em decimal.
   Answer: 108

2. Escreva o número 51 em binário.
   Answer: 00110011

3. Determine: 142.86.25.122 + 0.1.240.85
   Apresente o resultado no formato Dotted Decimal (IPv4).
   Answer: 142.88.9.207

4. Determine: 142.86.25.122 + 2048
   Apresente o resultado no formato Dotted Decimal (IPv4).
   Answer: 142.86.33.122

5. Um fabricante de dispositivos dedicados dispõe da gama de endereços 176.23.96.0/21  para preparar a instalação de um conjunto de sistemas dedicados.
   
   a) Por quantos endereços é composta esta gama?
   Answer: 2048

   b) Os dispositivos dedicados serão instalados em 4 setores distintos, com a distribuição especificada na tabela seguinte. As redes dos diversos setores serão interligadas de acordo com o esquema da figura. Proponha gamas de endereços a atribuir a cada uma das sub-redes.

   | Rede     | Nº de Dispositivos | Gama de Endereços |
   | -------- | ------------------:| ----------------- |
   | Backbone |                  0 | 176.23.103.128/28 |
   | Setor A  |                 71 | 176.23.103.0/25   |
   | Setor B  |                412 | 176.23.100.0/23   |
   | Setor C  |                730 | 176.23. 96.0/22   |
   | Setor D  |                167 | 176.23.102.0/24   |

## TP2

> [!warning] My score was 97 out of 100, so one of these is wrong, but I have not yet reviewed it.

1. Complete as seguintes afirmações (pertence ou não):
   O endereço 192.68.15.23 **pertence** à gama 192.68.14.0/23.
   O endereço 192.68.15.23 **não pertence** à gama 192.68.14.0/24.  
   O endereço 192.68.15.23 **pertence** à gama 192.68.15.0/24.  
   O endereço 192.68.15.23 **pertence** à gama 192.68.8.0/21.  
   O endereço 192.68.15.23 **pertence** à gama 192.68.12.0/22.  
   O endereço 192.68.15.23 **não pertence** à gama 192.68.8.0/22.  

2. Complete as seguintes afirmações (pertence ou não):
   O endereço 117.68.133.213 **não pertence** à gama 192.68.64.0/22.
   O endereço 117.68.73.37 **não pertence** à gama 192.68.64.0/22.  
   O endereço 117.68.115.85 **não pertence** à gama 192.68.64.0/22.  
   O endereço 117.68.65.197 **não pertence** à gama 192.68.64.0/22.  
   O endereço 117.68.51.19 **não pertence** à gama 192.68.64.0/22.  
   O endereço 117.68.95.232 **não pertence** à gama 192.68.64.0/22.  


3. Uma empresa adquiriu a gama de endereços IPv4 especificada como: **168.213.72.0/21**
   Por quantos endereços é composta esta gama?
   Answer: 2048

4. A empresa encontra-se organizada em 4 departamentos (Dep_A, Dep_B, Dep_c e Dep_D). O número de postos de trabalho em cada departamento é o apresentado na tabela seguinte.
   
   | **Departamento** | **Postos de Trabalho** |
   |:----------------:|:----------------------:|
   | Dep_A            | 418                    |
   | Dep_B            | 112                    |
   | Dep_C            | 795                    |
   | Dep_D            | 195                    |
   
   Determine o número total de postos de trabalho da empresa.
   Answer: 1520

5. Esta empresa pretende agora reestruturar a rede de interligação entre os seus 4 departamentos (Dep_A, Dep_B, Dep_C e Dep_D) e ligação à Internet, de forma a obter a estrutura apresentada na figura.

   [(to see this image, sign in to Moodle, then paste this URL)](https://moodle.isep.ipp.pt/pluginfile.php/31423/question/questiontext/56044/5/42706/rede2021_ingre_4.png)

   **a)** Proponha uma distribuição de gamas de endereços para cada uma das sub-redes necessárias.
   
   | **Nome da rede** | **Endereço Base** | **Máscara**     |
   | ---------------- | ----------------- | --------------- |
   | Dep_A            | 168.213.76.0      | 255.255.254.0   |
   | Dep_B            | 168.213.79.0      | 255.255.255.128 |
   | Dep_C            | 168.213.72.0      | 255.255.252.0   |
   | Dep_D            | 168.213.78.0      | 255.255.255.0   |
   | (resto)          | 168.213.79.128    | 255.255.255.128 |
   
   
   **b)** Proponha endereços para atribuir às _interfaces_ dos _routers_ R1 e R2.
   
   | **Router** | **Porta** | **Endereço**   |
   | ---------- | --------- | -------------- |
   | R1         | Eth_A     | 168.213.76.1   |
   | R1         | Eth_B     | 168.213.79.1   |
   | R1         | Eth_C     | 168.213.72.1   |
   | R1         | -         | -              |
   | R1         | -         | -              |
   | R2         | Eth_C     | 168.213.72.2   |
   | R2         | Eth_D     | 168.213.78.1   |
   | R2         | Eth_I     | ???? isp.0.0.1 |


6. Complete a tabela de encaminhamento a utilizar no _router_ R2. 

   
   | **Gama de Destino** | **Gateway**  | **Porta** |
   | ------------------- | ------------ | --------- |
   | 168.213.72.0/22     | -            | Eth_C     |
   | 168.213.78.0/24     | -            | Eth_D     |
   | isp.0.0.0/n         | -            | Eth_I     |
   | 168.213.76.0/23     | 168.213.72.1 | Eth_C     |
   | 168.213.79.0/25     | 168.213.72.1 | Eth_C     |
   | 0.0.0.0/0           | isp.x.x.x    | Eth_I     |
   | -                   | -            | -         |

## TP3

1. A utilização de NAT (Network Address Translation) elimina a necessidade de utilização de ARP.
    - [x] False 

2. O cabeçalho de um datagrama IP numa rede pública pode conter um endereço de origem privado.
    - [x] False 

3. O cabeçalho de um datagrama IP numa rede privada pode conter um endereço de origem público.
    - [x] True
   
4. O cabeçalho de um datagrama IP numa rede privada pode conter um endereço de destino público.
    - [x] True

5. Um router IP que efectue NAPT (_Network Address and Port Translation_) tem que alterar o cabeçalho dos datagramas UDP (_User Datagram Protocol_).
    - [x] True
   
6. O cabeçalho de um datagrama IP numa rede pública pode conter um endereço de destino privado.
    - [x] False 

## TP4


1. Um endereço IPv6 é composto por 16 Bytes.
    - [x] True

2. Um cabeçalho IPv6 tem 128 bits.
    - [x] False 

3. Uma trama Ethernet pode encapsular um datagrama IPv6.
    - [x] True

4. Em IPv6 define-se um método de confirmação selectiva (SACK: _Selective Acknowledge_).
    - [x] False 

## TP5

> [!warning] I did not save the questions, and am unable to review this quiz.

## TP6

1. A Ethernet é uma tecnologia de rede utilizada principalmente em redes locais (LAN).
    - [x] True 

2. Numa rede Ethernet, todos os dispositivos devem usar conexão sem fios.
    - [x] False

3. O endereço MAC Ethernet possui 48 bits.
    - [x] True 

4. O cabo coaxial nunca foi utilizado em redes Ethernet.
    - [x] False

5. O protocolo Ethernet opera principalmente nas camadas Física e de Ligação do modelo OSI.
    - [x] True 

6. O _switch_ Ethernet envia sempre os dados para todas as portas ao mesmo tempo.
    - [x] False

7. O endereço IP substitui completamente o endereço MAC na comunicação local Ethernet.
    - [x] False

8. Redes Ethernet podem utilizar fibra óptica como meio físico.
    - [x] True 

## TP7

1. Em CAN clássico com trama extendia (extended frame), o campo de dados pode transportar até 64 Bytes.
    - [x] False
    
2. O protocolo CAN utiliza um mecanismo de arbitragem não destrutiva baseado nos identificadores das tramas.
    - [x] True

3. Numa rede CAN, um bit dominante sobrepõe-se sempre a um bit recessivo.
    - [x] True

4. (This was the same as question 1, aside from a spelling error; the professor confirmed that it was the same question.)

5. O identificador de uma trama CAN serve apenas para identificar o emissor da mensagem.
    - [x] False

6. Em CAN, mensagens com identificadores numericamente mais baixos têm maior prioridade.
    - [x] True

7. O protocolo CAN implementa automaticamente retransmissão quando deteta erros numa trama.
    - [x] True

8. O barramento CAN utiliza normalmente uma topologia física em estrela.
    - [x] False

9. O CAN Low-Speed Fault-Tolerant foi concebido para operar tipicamente a velocidades mais baixas do que o CAN High-Speed.
    - [x] True
    
10. O protocolo CAN depende obrigatoriamente de um endereço MAC único por dispositivo.
    - [x] False

11. CAN-FD permite taxas de transmissão superiores às do CAN clássico durante a fase de dados.
    - [x] True

12. Em CAN-FD, o campo de dados pode transportar até 64 Bytes.
    - [x] True

## TP8

1. Os protocolos de encaminhamento do tipo **Link State** rquerem mais recursos de processamento do que os protocolos do tipo **Distance Vector**.
    - [x] True

2. Um encaminhador que utilize RIP (Routing Information Protocol) aplica o algoritmo **Dijkstra** para determinar os caminhos mais favoráveis para cada um dos destinos.
    - [x] False

3. Numa rede que utilize RIP (_Routing Information Protocol_) as trocas de informação de encaminhamento são realizadas apenas entre encaminhadores vizinhos.
    - [x] True

4. A técnica de **Split Horizon** permite mitigar os problemas do tipo **Count-To-Infinty**.
    - [x] True

5. Nos protocolos do tipo **Distance Vector**, justifica-se a aplicação da técnica **Split Horizon**.
    - [x] True

6. Os protocolos de encaminhamento do tipo **Link State** apresentam tempos de convergência mais longos do que os protocolos do tipo **Distance Vector**.
    - [x] False

7. O protocolo STP foi concebido para evitar loops de camada 2 em redes Ethernet com caminhos redundantes.
    - [x] True

8. O STP (Spanning Tree Protocol) utiliza mensagens BPDU para trocar informação entre switches.
    - [x] True

9. O protocolo STP opera na camada de rede (_Layer 3_) do modelo OSI.
    - [x] False

10. O Rapid Spanning Tree Protocol (RSTP) foi desenvolvido para reduzir o tempo de convergência relativamente ao STP clássico.
    - [x] True

## TP9

> [!warning] I have not received a grade for this yet, so I cannot guarantee that these are correct.

1. O protocolo MQTT segue um modelo de comunicação publish/subscribe.
    - [x] True

2. Em MQTT, os clientes publicam mensagens diretamente para outros clientes sem intervenção de um broker.
    - [x] False

3. O broker MQTT pode armazenar mensagens retain para novos subscribers.
    - [x] True

4. O QoS 0 em MQTT, garante entrega exata de uma mensagem uma única vez.
    - [x] False

5. As respostas HTTP/1.0 identificam o método na primeira linha.
    - [x] False

6. Em HTTP/2, os cabeçalhos (_headers_) são normalmente comprimidos usando a técnica HPACK.
    - [x] True

7. Os pedidos pelo método POST podem utilizar HTTP/2.
    - [x] True

8. Todos os servidores HTTP/2 suportam PHP.
    - [x] False

## TP10

1. Considere uma sessão TCP estabelecida entre as máquinas A e B com a troca de mensagens representada na tabela. Para cada mensagem são indicados:
   (Consider a TCP session established between machines A and B with the message exchange represented in the table. For each message are indicated:)
   
   o número de sequencia (Seq)
   o número de confirmação (Ack)
   o comprimento dos dados (Len) em Bytes.
   
   | Direção |   Seq   |   Ack   |   Len   |
   |:-------:|:-------:|:-------:|:-------:|
   | A -> B  |   203   |   232   | **151** |
   | B -> A  |   232   | **354** |   143   |
   | A -> B  |   354   |   375   | **93**  |
   | B -> A  | **375** |   447   |   179   |
   | A -> B  | **447** |   554   |    0    |
   | A -> B  |   447   | **554** |   163   |
   | B -> A  |   554   |   610   | **180** |
   | A -> B  | **610** |   734   |   130   |
   
   Determine os valores em falta na tabela.

2. Considere uma sessão TCP estabelecida entre as máquinas A e B com a troca de mensagens representada na tabela. Para cada mensagem são indicados:
   (Consider a TCP session established between machines A and B with the message exchange represented in the table. For each message are indicated:)
   
   o número de sequencia (Seq)
   o número de confirmação (Ack)
   o comprimento dos dados (Len) em Bytes.
   
   | Direção |   Seq   |   Ack   |   Len   |
   |:-------:|:-------:|:-------:|:-------:|
   | A -> B  |   161   |   116   |   98    |
   | B -> A  | **161** |   259   |   114   |
   | A -> B  |   259   |   230   | **177** |
   | B -> A  |   230   |   436   |   89    |
   | A -> B  |   436   | **319** |    0    |
   | A -> B  | **436** |   319   |   98    |
   | B -> A  |   319   |   534   |   121   |
   | A -> B  |   534   |   440   |   102   |
   
   Determine os valores em falta na tabela.

3. Os serviços que utilizam UDP nunca são fiáveis.
    - [x] False

4. O protocolo UDP disponibiliza um serviço com garantias de entrega.
    - [x] False

5. Um cabeçalho UDP inclui um campo com o número de sequência (SEQ).
    - [x] False

6. Um cabeçalho TCP inclui um campo SessionID para identificar a sessão estabelecida.
    - [x] False

7. Num contexto típico de comunicação TCP/IP, um segmento TCP transporta um datagrama IP.
    - [x] False

8. Uma conexão TCP é sempre estabelecida por iniciativa do nó que pretende solicitar informação.
    - [x] False


**The following are from a second attempt of TP10 (that I did not complete):**

1. A flag ECE (ECN-Echo) de um cabeçalho TCP pode ser ativada por um encaminhador da rede para assinalar um congestionamento.

2. Um cabeçalho TCP especifica o porto de origem.

3. Um cabeçalho UDP inclui um campo com o porto de origem (_Source port_).

4. O campo de confirmação (ACK) incluído num cabeçalho TCP tem 64 bits.

5. Um cabeçalho TCP inclui um campo com a dimensão da janela de controlo de fluxo.

6. Um datagrama IPv6 pode encapsular um pacote UDP.
