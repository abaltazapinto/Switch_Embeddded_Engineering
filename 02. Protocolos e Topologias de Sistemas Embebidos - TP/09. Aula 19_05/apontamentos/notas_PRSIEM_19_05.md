mQTT vantagem que oferece para os sistemas embebidos

HTTP 

![alt text](image.png)

os broswers webs sao cliente httop, e efeciente , e leve mas nao tanto como MQTT, os protocolos de e considerado eficiente,

funciona sobre tcp. 

![alt text](image-1.png)

mqtt funciona sobre TCP e http tambem

so pode comecar depois de tcp

![alt text](image-2.png)

responde com os conteudo ou uma mesagem de erro, mesma sessao tcp para fazer varios pedidos. 

Se conseguires arranjar uma sessao TCP antes de fazer o pedido do HTTP . 

So se pode pedir um,a coisa depois de a anterior ja ter chegado. 

![alt text](image-3.png)

os servidoere web fecham a ligac ao deppois de satisfazer um pedido http. depois tem de se establecer outra sessaioo TCP.

![alt text](image-4.png)

escuta no porto 80 quando nao se diz nada. 

![alt text](image-5.png)

http 1.1 era a unica que existia, ou a versap mais atual dis[pnivel]

![alt text](image-6.png)

como funciona o http, depois da ligacao establecida TCP. o cliente HTTP faz um pedido.

a primeira seccao chama se request line depois seccao de conteudo.

![alt text](image-7.png)

Servidor saber que lingua falamos
tem de se assinalar fim de linha


![alt text](image-8.png)

mais habituais 

# GET
# HEAD
# POST

![alt text](image-9.png)

![alt text](image-10.png)

# PUT
upload de ficheiros

# DELETE 
pedir para apagar o conteudo

# Trace

# Options

![alt text](image-11.png)

![alt text](image-12.png)

Header lines acabam sempre num final delinha

![alt text](image-13.png)

estes cabecalhos servem para juntarmos informacao sobre o pedido

podemos identificar quem feez o pedido

![alt text](image-14.png)

![alt text](image-15.png)

![alt text](image-16.png)

para pedidos que tem de enviar dados para o servidor, temos de juyntar uma seccao com algum conteudo, pode ser conteudo binario qualquer, se e binvario nao exite marcacao no fim. 

precisamos d eocntent length para saber o conteudo
|
![alt text](image-17.png)

---

![alt text](image-18.png)

# pedido feito com metodo Post

content-length
depois conteudo

---

![alt text](image-19.png)

depois do pedido ha que haver respoista

foramatada em tres seccoes, 

# Status line
que diz queal o resul;tado


# Headers

---

![alt text](image-20.png)

versao do http codigo do resultado, 3 digitos. 

codigos dee sucesso comecam por 2

erro

4 quando e cliente
5 quando e o server

200 e o coidigo do sucesso

erro mais conhecido e o 404 quandoi o ficheirop nao e encontrado/ 

---

![alt text](image-21.png)

---
![alt text](image-22.png)
---

![alt text](image-23.png)

http 1.0 a seguir vem bloco de cabecalhos que pode ter zeron  linhas. 

---

![alt text](image-24.png)

Pedido com duas respostas, maior parte dos servidores nao gosta de ficar a esppera , e o servidor fecha a sua ligacao

depois do http1.1 podemos ter ligacoes persistentes

---

![alt text](image-25.png)

---

![alt text](image-26.png)

http quando funciona com tls e sobvre tcp

---

![alt text](image-27.png)

isto nao e adequado para transformar info de tempo real, mesmo para web, e a latencia. porque demora muito a processar o pedido
---
![alt text](image-28.png)

estao a escuta no porto 443

---
![alt text](image-29.png)
problema que apontam, sao sobretudo o peso necessario para paginas complexas

---
![alt text](image-30.png)
teve de criar http2 permitiu acabar com truques, saiu emn 2015, formatos binarios, para termos menos overheads e tempos mais interessantes e para nmultiplexar varios pedidos , e as respostas vem , hao de chegar todas as repostas mas nao n estamos a espera. 

---
![alt text](image-31.png)
---
![alt text](image-32.png)
http2 para diminuir overheads que e inserida pelko protocolo, todos os pacotes de pedidios e resposta
---
![alt text](image-33.png)
define mecanimo de push, teoricamente que um servidor, o server podera enviar mais coisa sque op cliente nao pediu
---
![alt text](image-34.png)
isto permite diminuir o periodo de latencia, 

http2 multiplexar pedidos. 

com o push pedes por ex htmll e servidor envia html javascript css

---

# MQTT

![alt text](image-35.png)

![alt text](image-36.png)

ja surgiu ha muito tempo... varias versoes utilizacao fechada. 
consorcio empresarial OASIS -> fazem normalizacao. formalizacao a norma mQTT norma definida pr eles.

a versao mais atual e 5.0

---
![alt text](image-37.png)

porque se usa e simples eficiente, funciona bem na internet, mesmo que ligacao seja fraca e instavel. 
cpmunicacao assicrona, 
quem envia pode nem sequer estar ligado a internet, circula quando pode ate elemento ou broker e partir dai quando ouver possibilidade pode seguir ao ddestino final;l

protocolo simples pouco overhead. 
---

![alt text](image-38.png)

usa se em muitos ambientes 

automacao caseira
automacao industrial
smart cities

feita por servidores , a;lguns gratuiata e livre com limites

as infraestruturas, tambe suportam MQTT, instalar e disponibilizam mqtt em cloud, 
---
![alt text](image-39.png)
API que podemos ligar.
quando criamos aplicacaoes feitas em C, pythhon

servidores comerciasi publicos na internet, instalar o nosso proprio servidor, podemos instalar servidor open source como mosquito vamos experimentar na aula. 

---
![alt text](image-40.png)

mqtt adopta puclicaco subscricao, existe uma entidade sempre ligada broker ou servidopor, 
um assume o papel de subscritor 
um determinado toiipo de mensagens
o que publica essa mensagem e enviada a todos. 

ambos os extremos tem de conhecer o broker. 

---

![alt text](image-41.png)

pode haver overhead no broker, visto que tem de trabalhare para fazer o envio das mensagens. 

---

![alt text](image-42.png)

um broker pode receber de varios publuisher, logo varios subscritores

---

![alt text](image-43.png)

# sensor de temperatura
(boa ideia para o quintal plantado)
adapata se bem a ambientes de
---
![alt text](image-44.png)
aplica se bem a publicacao esporaddica, ligar ou desligar dependendo das ordnes.
---
![alt text](image-45.png)
clientes mqtt


---

![alt text](image-46.png)

---

![alt text](image-47.png)

---
TCP ou TLS
---
![alt text](image-48.png)
---
![alt text](image-49.png)
topicos identificam a mensagem, presupoe hierarquia de topicos, significa a raiz, sub sub topico, ate ao item, 
---
![alt text](image-50.png)

exemplo de topicos.
---
![alt text](image-51.png)
---
![alt text](image-52.png)
conteudo binario sao daos opacos sem significado para a camada MQTT
efeitos praticos e iliminado
---
![alt text](image-53.png)
a quem recomende formatos para organizarmos os nosso dados mqtt
codificacoes que sejam legiceis por humanos, 
---
![alt text](image-54.png)
os subscritores qunado pretende vir receber a um determinado topico, tem de fazer subscricao dessse topicos.
para cada mensagem de subscribe responde comacknowledegemnt
---
![alt text](image-55.png)
simbolo + e cardinal #
---
![alt text](image-56.png)
fazer a comparacao o htrtp a comunicacoa e sempre 1-1
aqui podemos ter muitos sensores para varios dispositivos many to many. 
onormal no httpo um pedido tem sempre um resul;tado nao depende de pedidos anteriores
No MQTT existe manutencao de estado quer estado de ligacoes TCP, ENQUANTO O SERVIUDOR FAZ OUTRA PARTE DA TAREFA
---
![alt text](image-57.png)
DEPOIS DE ESTABLECER a conexao tcp depois MQTT
---
![alt text](image-58.png)
os pacotes MQTT que circula ate ao broker, tem uma estrutra simples
2 bytes po cabecalho
---
![alt text](image-59.png)
---
![alt text](image-60.png)
o qyue e o QOS - qualidade de serviico, trata com mais qualidade as mensagens que queremos melhor qualidade. 
---
![alt text](image-61.png)
uma mensagem MQTT exemplo de mensagem de disconnet e so dois bytes
---
![alt text](image-62.png)
vamos instalar servidor mosquito criando pequena aplicacao em C
podemos experimentear conjuinto de ferramentas
que implementam clientes MQTT,
nmosquito PUB q ue serve para publicar uma mensagem. 

    mosquito_sub -h localhost -p 1883 -t '#'

 cardinal e para todos os topicos vamos receber todas as mensagens que chegamn ao broker.
 PINGREQ
 PINGRESP
---
![alt text](image-63.png)
---
![alt text](image-64.png)
QOS 0 nao exitem confirmacaoes que a mensagem vai chegar ao destino
QOS 1 o mqtt garante que vai chegar copia aos destino pode eventualmente chegar mais
QOS 2 aqui temos grantia que vai receber e so 1 mensagem

QOS 0 = coisas rapidas nao temos tempo ou largura de banda
QOS 1 = exemplo quando eu quero a luz acesa, logo nao tem mal se houver varias
QOS 2 = quandoquero mudar estado da luz a ordem for duplicada e pode fazer efeito diferente, ou aumentar temperatura. 
---
![alt text](image-65.png)

Com qos 0 , se chegar tudo bem senao tudo bem tb
qos1 existe confirmacao de chegada
![alt text](image-66.png)
![alt text](image-67.png)
![alt text](image-68.png)
---
qos =  2
![alt text](image-69.png)
mais pesado mais complexo, memorizacao de mensagens, o broker 
---
![alt text](image-70.png)
os qos funcionan nos dois sentidos

    mosquito_sub -q 1 -h localhost -p 1883 -t '#'

---
![alt text](image-71.png)
---
![alt text](image-72.png)
---
![alt text](image-73.png)
---
![alt text](image-74.png)
---
![alt text](image-75.png)
---
![alt text](image-76.png)
---
![alt text](image-77.png)
result/to/1
result/to/2
---
![alt text](image-78.png)
enviando dados adicionais, para ver quem deve receber a resposta ou quem deve receber o pedido.
---
![alt text](image-79.png)
possibilidade de guardar mensagens retenidas ou retains podem ser guardadas no btoker. temos de ter mensagens retenidas. 
---
![alt text](image-80.png)
se tivermos mensagens que o sensor da porta noos envia sempore que ha um evento, aabre porta fecha porta.
---
![alt text](image-81.png)
funcionalidade de retencao, state cash, a luz esta ligada com retencao
---
![alt text](image-82.png)
---
![alt text](image-83.png)
coAP

sabado vamos experimentar instalar servidor MQTT
---
AMQP e mais pesado que mqtt!!!
---

vamos de falar de tcp