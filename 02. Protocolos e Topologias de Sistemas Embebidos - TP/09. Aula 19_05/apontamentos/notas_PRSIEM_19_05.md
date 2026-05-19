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

