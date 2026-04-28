vamos falar de redes privadas. 

nao podem ser ligadas a Internet

![alt text](image.png)

enderecos privados...

pode haver outras pessoas no mundo que usem os nossos enderecos

bom para redes dispositivoos IOT , queremos criar uma familia 

![alt text](image-1.png)

nos vimos os enderecos publicos , quando recebemos um endereco dessses vem sempre de um pacote global

os privados sao livres, nao precisamos de dizeer a ninguem que os usamos. 

mecnism0  mais comum atraves de NAT - network asdrress translation. 

![alt text](image-2.png)

router NAT ou gateway NAT, enderco oficial de um lado e do outro do lado do privado, em casa temos equeipamento deste tipo. 

![alt text](image-3.png)

![alt text](image-4.png)

funciona assim acesso a internet quenado usamos NAT, 

![alt text](image-5.png)

NAT basico, temos tabela com varias linhas para cada endereco privado iremos ter publicos. 

quando precisamos de poupar, podemos nao ter enderecos publicos que cheguem. 

![alt text](image-7.png)

![alt text](image-8.png)

NAT da jeito para outros efeitos para a migracao de ...

enderecos que sao emprestados pelo nosso fronecedor de internet. 

migracao de isp, solucao NAT

![alt text](image-9.png)

![alt text](image-10.png)

![alt text](image-11.png)

temos tres servidores, internet, endereco publico que esta aqui. 

![alt text](image-12.png)

IP masquerading.... umma especificacao port translation...

Protocolpos de transporte... TCP e IP

identificar aplicacoes dentro de u,ma maquina. para se saber as respostas para quem sao. numero de porto. UDP e tcp na camada de transporte ha .

![alt text](image-13.png)

![alt text](image-14.png)

em tempo real normalmente nao se usa TCP/ 

A implementacao de nat mais aberta, e fulcone NAT

.
 ![alt text](image-15.png)

 ![alt text](image-16.png)

 a maqiuna privada envia ium pacore, o pacote chega depois de feita a dttraudcao de enderecos. 

 ![alt text](image-17.png)

 ![alt text](image-18.png)

 ![alt text](image-19.png)

 ainda mais restritivo

 ![alt text](image-20.png)

 ![alt text](image-21.png)

 ![alt text](image-22.png)

 casa symetric nat. 

 ![alt text](image-23.png)

 ![alt text](image-24.png)

 ![alt text](image-25.png)

 ![alt text](image-26.png)

 ![alt text](image-27.png)

 ![alt text](image-28.png)

 ![alt text](image-29.png)

 nao podemos ter servicos publicos nas redes privadas, 

 para isso temops de fazer configuracao adicional no Router NAT, essa config adicional chama se normalmente fazer um port forward. 

 ![alt text](image-30.png)


 ![alt text](image-31.png)

 relaying e unica soluca que funciona sempre se forem nat simetrico a unica solucao que e garantida e utilizar o servidor de relay. nao e eficiente para tempo real. 

![alt text](image-32.png)

![alt text](image-33.png)

![alt text](image-34.png)

CRIAR UM ROUTER NAT COM LINUZ USANDO iptables

temos de aprender esta sintaxe 

![alt text](image-35.png)

aberto trabalho que vamos fazer no sabado

configuracvao da rede IP e verificar que funciona


Laboratorio

Vamos fazer configuracao de uma rede. no laboratorio ja levar tudo preparado no papel, vmaos fazer antes uma parate para quando chegar estar pronto. 

ate amanha para estar pronto o importante e que sabado funcione. 


####################################################################################


NOTAS EXERCICIOS



 NAT = Network Address Translation

Altera endereços IP (camada rede / Layer 3).

Exemplo:

192.168.1.10  ->  85.20.30.40

O router troca IP privado por IP público.

XXXX

NAPT / PAT 

Alem do IP altera tambem portas TCP / UDP (camada transporte / Layer 4)

Exemplo:

192.168.1.10:52341 -> 85.20.30.40:40001

Permite vários PCs partilharem 1 IP público.


Pergunta 1:

Um router IP que efectue NAPT tem que alterar o cabecalho dos segmentos TCP. 

Resposta: VERDADEIRO

PORQUE?

NAPT traduz: 
    > IP origem
    > porta origem

A porta esta no cabecalho TCP (ou UDP). Logo o router precisa modificar

######################################################################################################################

Lab parte 1 - EXPLICACAO STOR.

![alt text](image-36.png)

aqui so temos dispositivos quem souber por um dispositivo a funcionar, sabe por 3. 

cada um de voces vai usar uma gama de enderecos especifica. 


o professor tem esta gama de enderecos .. ![alt text](image-37.png)


![alt text](image-38.png)

/21 2^32 / 2 ^ 21 

![alt text](image-39.png)

/22 e um conjunto de 1000 enderecos

![alt text](image-40.png)

512 enderecos / 23 endereco que seja 1024 enderecos depois deste..
![alt text](image-41.png)

![alt text](image-42.png)

![alt text](image-43.png)

![alt text](image-44.png)

![alt text](image-45.png)

![alt text](image-46.png)

dimensao do predixo da rede onde esta porta esta ligada.

relacao 1/1 com o /22 pode se obter a mascara. endereco nao tem o / . se puserem vi vos facilitar o trablho, a einterface de configuracao aceita ISTO isto tudo de uma vez/. 


![alt text](image-47.png)

para falarmos de n1 para rede A temos de arranjar uma rota. |

dois caminhos possiveis deve usar o caminho curto. 
caminho porventura , perfeitamente simetrico aqui. 

![alt text](image-48.png)

![alt text](image-49.png)

![alt text](image-50.png)

![alt text](image-52.png)

![alt text](image-53.png)

TABELA DE ENCAMINHAMENTO PARA O N2 E MAIS SIMPLES

![alt text](image-54.png)

![alt text](image-55.png)


encaminhamento n3

![alt text](image-56.png)

![alt text](image-59.png)

![alt text](image-60.png)


SABADO 

APARESSE FEITO>>>>> ou num pape ou no moddle copiar endercos e por nas maquinas. 

