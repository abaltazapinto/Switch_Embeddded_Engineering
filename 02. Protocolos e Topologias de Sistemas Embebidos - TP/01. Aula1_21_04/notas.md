![alt text](image.png)

quem quer fazer processadores define o processador 

Professor Miguel Leitao.

Modelo Osi, quando nnos inventamos uma tecnologia  e melhor descrever a nossa invencao com as interface .

![alt text](image-1.png)

O modelo osi define 7 camadas. Sempre que oimpletmentamos uma comunicacao sestamos a inmoplementar algum conjunto destas camasdas. Nao necessariament todas 

![alt text](image-2.png)

![alt text](image-3.png)

![alt text](image-4.png)

encaminhamento e decidir se as coisa hao de ir por este link ou por este link. 

quanto maior for a segmentacao da rede , o empacotamento mais subidas e descidas. 

O modelo OSI e complicado nem sempre se ajusta as .. modelo TCP/IP e modelo mais simples tem apensa 4 niveis. 

![alt text](image-5.png)

![alt text](image-6.png)

nas redes industriais onde nao e preciso fazer enderecamento as vezes,. pode enviar para todas as outras maquinas, modelo osi colapsado.

onde se omite o nivel de rede. 

Nos hoje vamos falar sobretudo de enderecos. O enderecamento existe em variops niveis. 

![alt text](image-7.png)

![alt text](image-8.png)

vamos falar de enderecos que esta na ascamada de rede da internet, esta camada serve para interligar trafego de redes locais. 
Protocolo IP tem principal funcao fazer o enderecamento. em todos os protocolosxd de rede a camada que impoletmentou o protocolo revebe os dados da camada superiores 

![alt text](image-9.png)

![alt text](image-10.png)

desmu;ltiplexagem. separa ps dados para as aplicacoes todas que estamos a usar. 

![alt text](image-11.png)

a idenia da internet foi criar uma rede global. pudesse falar com qualquer outra mnaquina. 

![alt text](image-12.png)

![alt text](image-13.png)

protocolo ip para agregar as todas uma camada em cima daquilo que ja existia. 

o IP nao deteta sduplicados as vezes .... 

![alt text](image-14.png)

32 bits sao 4 bytes

![alt text](image-15.png)

![alt text](image-16.png)

![alt text](image-17.png)

os enderecos sao de 32 bits, principal caracterisca no protocolo IP. 

os telefones nao tem nada a ver com o IP mas tambem usam endereco

![alt text](image-18.png)

em portugal o numero tem 12 digitos

![alt text](image-19.png)

10 levantado a 10 telefone ou seja muitos milhoes de telefones/ 

![alt text](image-20.png)

endereco unico para qq maquina no mundo. 

2 levantado a 32... 

![alt text](image-21.png)

![alt text](image-22.png)

![alt text](image-23.png)

enderecos ip podemos considerar que sao divididos em duas partes. 

o dendereco completo e concatenacao ou o conjunto do net ID com oi site ID. 

![alt text](image-24.png)

![alt text](image-25.png)

 A PARTIR DE 93 DEIXOU DE HAVER CLASSES DE ENDERECOS. E PASSOU SE A PODER USAR QUALQUER COMPRIMENTO DE NET id. 

 aCTUALMENTE TODAS AS MAQUINAS  suportam todos os tamsanhos de NET ID. 


 NAT e importatnte para internet das coisas, porque os enderecos privados sao a solucao iudeal para ligar copisas a internet.

 IPV6 ja existe definido desde 96 de forma oficial em 2000, No entanto quando se desenvolve sistemas novos . 

 em 2011 acabaram os enderecos IPV4 , Nem pensar usar a versao IPV4 , porque IPv6 ja nao sofre a escassez de enderecos. 

 ![alt text](image-26.png)

 os paise distribuem para operadores etc...

 ![alt text](image-27.png)

 ![alt text](image-28.png)

 reservado nao ha mais mblocos para distreibuir a ninguem a partir de 2011

 ![alt text](image-29.png)

 ![alt text](image-30.png)

 na rede telefonica., para sabermos qual e a parte que diz ao identificaticvo do pais.

 ![alt text](image-31.png)

 ![alt text](image-32.png)

 match com conjunto de dois digitos ou mesmo de 3 digitos

 os enderecos pode ser dividico net ID e host ID. 

 saber NETID e HostID e Addr

 com as mascaras tem de comecar por u m e acabar em zeros

 ![alt text](image-33.png)

 ![alt text](image-34.png)

 ![alt text](image-35.png)

 1 mais a mascar negada... em binario e isto que esta aqui 

 ![alt text](image-36.png)

 Gams de enderecos, atribuimos sempre um conjunto de enderecos que genericamente comeca  unum endereco e acaba noutro. 

 gams CIDR, algumas gamas cumprem estes reqyuisitos outras nao. Sao aquelas que podem ser escritas por um enderco base e uma mascara. 

 uma gama de 8 enderecos nao pode comecar num endereco que seja multiplo de 5 se nao for multiplo de 8. 

 ![alt text](image-37.png)

 ![alt text](image-38.png)
comecei a segunda gravacao //////////////////
![alt text](image-39.png)

mascara de rede tem esta conta. 

![alt text](image-40.png)

![alt text](image-41.png)

na proxima aula vamos ver como se usa enderecos para encaminhar o trafego !

Proponho fazermos exercicios que estao publicados no moddle 

binario para decimal e uma divisao para uma rede destas. 

![alt text](image-42.png)

![alt text](image-43.png)


router 1 router 2 , 

![alt text](image-44.png)

quantos enderecos vamos fdar a cada ssubrede

![alt text](image-45.png)

vamos calcular ... 

sector C gama de nedercos 176.23.96.0/22

sector B gama de enderecos 176.23.100.0/23

qual a razao de serem multiplos.

e uma restricao pela norma IP

multiplo do seu comprimento /23 se nao comecasse nu m multiplo nos nao sabiamos onde e que comecas e onde e que acabava. 

setup do router com esta notacao. /23 /22 so essas gams alinhadas e que servem !!!

Se ali alocamos 512 endercos vamos para a um sitito que pode ser quele + 512

Sector D gama de enderecos 176.23.102.0/24

o backbone e um conjunto de 16 endercos., vai comecar o endereco onde acaba o sector A. 

![alt text](image-46.png)

