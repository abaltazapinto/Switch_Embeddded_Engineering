versao do stor 6.12 importante. 

como ir buscar a versa exacta que tenm nas distribuicoes. 

a versao exacta para a versao que esta a usar....

Para compilar na escola tudo bem , mas para compilar.

Plano de trabalho para hoje. Programas para verificar e testar. 
Eu vou ter de compilar eu , nao percebo o que fala das versoes. 

fala do exercicio . 

relogio do pwm , confiurar a funcao do exercicio 1. era a funcao 4. 

![alt text](image.png)

ver os slides que o stror tem e depois ele fala does exercicios

![alt text](image-1.png)


![alt text](image-2.png)

![alt text](image-3.png)

![alt text](image-4.png)

![alt text](image-5.png)

![alt text](image-6.png)

![alt text](image-7.png)

qualquer escrita tem de colocar o valor 5A nos valores mais significativos. 

o quie eu sugeria e que usasem este oscillador, tem de colocar o valor 001, tem de colocar os valores 5A dos valores 31:24. 

![alt text](image-8.png)

![alt text](image-9.png)

apontador por mmap.. 

![alt text](image-10.png)

para os registos de relogio nbasicamente basta

fazer parea este endereco aqui 

![alt text](image-11.png)

vamos fazer um mmap de 8 bytes necessario para acedermos a estes regiistos. 

![alt text](image-12.png)

![alt text](image-13.png)

linux nao e para sitemas de tempo real. 

![alt text](image-14.png)

funcao de callback para termos qusdasd periodica em que ele soma , cria uma temporizacao para este tempo a partir do instante atual. 

![alt text](image-15.png)

![alt text](image-16.png)

![alt text](image-17.png)

![alt text](image-18.png)

interrupcoes.

 ![alt text](image-19.png)

 ![alt text](image-20.png)

 ficheiros de device tree , que no funcdo descrevem o hardware no sitema, ou aquele que queremos que seja detetado pelo LINUX, se quisermos usar as interrupcoes externas. 

 a forma mais pratica e criar um ficheiro de device tree que vai funcionar como uma camada . no pino GPIO 16 / 

 o device tree vamos dar o nome a esta seccao. indicar que queremos este pino como input. 

 este campo de compatibilidade poara fazer a correspondencia entre o codigo que temos no kernel e esta configuracao. 
 ![alt text](image-21.png)

 o kernel tem um conjubnto de modulos  uito grandes que podem estar a ser usados ou nao . 

que este modulo pretende controlar , de seguida criar estruturar platform driver . 

![alt text](image-22.png)

macro, platform driver. 

olhando para funcao my probe, ao ser ca=hamada vai ser preenchida pe;

device tree 

![alt text](image-23.png)

![alt text](image-24.png)

![alt text](image-25.png)

funcao de linux aspara saber o numero de interrupcao

 ![alt text](image-26.png)

 vamos fazer um pedidon para associar numero de interrupcao uma funcao !!

 IRQF| SHARED pode ser partilhada com varios pins de GPIO. 

 e possivel dar lhe nomes quando e feito o registo. estas funcoes comecado por devm_ uma das vantaegens e um sitema de funcoes , quando o modulo termina liberta automaticamente os recursos alocados pela funcao. 

 ![alt text](image-27.png)

 sempre que houver plano ascendente no pion16 esta funcao vai ser chamada 

 aqui tenho exercisiso 

 ![alt text](image-28.png)

 ![alt text](image-29.png)

 ao fim de determinado numero de impulsos . ou definimos que ao fim de um segundo tem de retornar o numero de imoulsos por esse tempo fixo.

 medir o tempo 

 ![alt text](image-30.png)

 k tikme get _ns

 ![alt text](image-31.png)

 dividir op numero de interrupcoes que foram contadas 

 ligar aa linha do pwm a esta entrada e assim vejo se a frequencia e aquela que pretendo. 

 ![alt text](image-32.png)

 nao vou pedir para entregar. este exercicio, util para fazre debug dos vosso programas. 

 ![alt text](image-33.png)


 ![alt text](image-34.png)

 este exercicio 1 e para ajudarem a compreender o codigo. 

 Cross compile com o arm- , depende ter o path bem configurado. mas no exercicio 2 , deixei aqui uma sugestao diferente colocar o path todo. 

 o exercicio II 

 e colocar 

 ![alt text](image-35.png)

 Exercicio 3 , foi por causa deste exercicio que dei o blinker hr.c 

 valor que tenha interrupcoes, frequencia de kilohertz 100 hetrx , led a piscar. depois de fazer o 2 , tem que implementar a logica doi pwm , ou sej no incio de cada ciclo. 

 Se o duty cycle for sempre 100 o pino tem de estar sempre a um !!!

 em vez de termos ddelay fixo. vamos ter de calcular esse delay ...

 ![alt text](image-36.png)

 exercicio 3 e pegarem no blinker hr , nas linhas de codigo que tem a ver e portanto na funcao do timer implementarem esta logica. o valor do duty cycle sao definidos atraves  destas macros. essa variavel pode ser usado como parametro do modulo. 

 066 leitura en escrita aos ficheiros , ao carregar o modulo cria automaticamente estes ficheiros. 

 ![alt text](image-37.png)

 exemplo simples da utilizacao de spi. 

 o spi e comparado ao i2C porque sao protocolos de comunicacao sincrono. 

[alt text](image-38.png)

![alt text](image-39.png)

ao contrario do I2C cada dispositivo tem o seu proprio endereco aqui tem de ser marcados individualmente. 

tem de haver uma linha para cada target. cada controlador de s[i do rasperry PI permitem 2 ou 3.

Por outro lado o SPI permite tazas de transmissao mais altas. 

em termos de transmissoes de dados. o spi permite fuill duplex especial 

![alt text](image-40.png)

quando o controlador comeca a transmitir os dados do seu buffer. comeca a receber , a preencher o seu proprio budfdfer com os dados que esta a receber. 

o modo tipico de utilizacao, no modo utilizacao ... Master para o slave... permite em simultaneo enviar os dados do seu buffer.

![alt text](image-41.png)

o buffer do slavve par ao master , muito rapido. comunicacao em full duplex so pode ser explorado em situacoes de transmissao continua. 

![alt text](image-42.png)

![alt text](image-43.png)

![alt text](image-44.png)

permitem configurar 4 modos de operacao. a ver com a polaridade do relogio. 

flanco ascendente flanco descendente., 

a titulo de exemplo .  

![alt text](image-45.png)

exemplo real , circuito integrado . usa uma comunicacao SPI. 
ver os 8 canais,

tensao de referencia 

![alt text](image-46.png)

sinal de relogio... Dout e o master in slave output. 

Mosi do controlador .

![alt text](image-47.png)

este modulo transmite palavras que podem ir ate 24 bits. No entanto o controlador SPSi ,...

o atmega128 so permitem trabalhar ate 8 bits. 

os impulsos 

![alt text](image-48.png)

oi master enviar , start bit, so entao e que comeca , estes 4 biuts sao usados para indicar o canl e o modo. Modo de single length, este AD 

![alt text](image-49.png)

![alt text](image-50.png)

o protocolo deste dispositivo, inicialmente enviou sempre um bit a 0- 
t=
1:23:35

![alt text](image-51.png)

![alt text](image-52.png)

![alt text](image-53.png)

t = 1:24:24

![alt text](image-54.png)

![alt text](image-55.png)

![alt text](image-56.png)

![alt text](image-57.png)

t = 1:25:37

![alt text](image-58.png)

![alt text](image-59.png)

![alt text](image-60.png)

![alt text](image-61.png)

controladores de SPI que permitem mais bits. 

![alt text](image-62.png)

raspberry pi4 temos varios conectores 

![alt text](image-63.png)

![alt text](image-64.png)

em temros de linux exite alguns device drivers feitos. para trabalhar com os controladores spi. 

temos de ativar o overlay correspondente/ ja sao fornecidos nao sao ativados por omissao. 

![alt text](image-65.png)

sudo doverlay spi0-lcs 

deteta que foi ativado uma funcionalidade e carrega os kernel correpondentes. 

![alt text](image-66.png)

lcs e de chip select.

![alt text](image-67.png)

sudo apt install spi-tools 

spi-pipe ponte de acesso

![alt text](image-68.png)

redorecionar para outro programa ou ficheiro. o controlador de spi do raspberry pi, permite enviar bits continuos 

![alt text](image-69.png)

chip select que vai a 1 e depoois a 0 ha um atraso que faz  com que as transmissoes naio sejam tao rapidas. |

![alt text](image-70.png)

![alt text](image-71.png)

leituras escritas para este fuc==icheiro . 

![alt text](image-72.png)

![alt text](image-73.png)

t = 1:39:18

![alt text](image-74.png)

ioctl o primeiro passo e abrir o ficheiro. permite mudar configuracoes desse ficheiro especial. 

![alt text](image-75.png)

![alt text](image-76.png)

![alt text](image-77.png)

![alt text](image-78.png)

fazer a selecao do kernel neste exercicio. 

![alt text](image-79.png)

![alt text](image-80.png)

![alt text](image-81.png)

![alt text](image-82.png)

![alt text](image-83.png)

![alt text](image-84.png)

![alt text](image-85.png)

![alt text](image-86.png)

Ad do atmega 128, para transpor os bits para parte mais significativa

![alt text](image-87.png)

![alt text](image-88.png)

![alt text](image-89.png)

![alt text](image-90.png)

![alt text](image-91.png)

![alt text](image-92.png)

![alt text](image-93.png)