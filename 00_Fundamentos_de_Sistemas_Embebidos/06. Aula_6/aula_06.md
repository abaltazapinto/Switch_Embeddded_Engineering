Falar em processos 


![alt text](image.png)


programa e processo e definicoes embora sejam muito parecidos....

![alt text](image-1.png)

Temos as tarefas todas que estao a ser executadas neste momento. 

![alt text](image-2.png)

![alt text](image-3.png)

mais threads do que processos, 

![alt text](image-4.png)

sao variavei static sao 

Heap alocada dinamicamente.. 

![alt text](image-5.png)

processo vai ser criado.. programa que esta no disco , ver quais aas necessidades que o programa tem 

estado de ready podem estar varios processos ao mesmo tempo . 
estado redy ao runining , o escanolador e super importan para sistemas operativos em tempo real...

Pode ser um interry=upt ... E portanto se nao houvver nada pelo menos vai haver um timern  e a volta d e20 milisegundos. e seja executado o escanolador, estou no estado de running e o meu programa decide que vai fazer uma leitura de um ficheiro. 

![alt text](image-6.png)

pode terminar ordenadoi ou nao ordenado.. passa para estado terminated. 

estadpo zombi....

![alt text](image-7.png)

![alt text](image-8.png)

![alt text](image-9.png)

PID identificador unico... 

![alt text](image-10.png)

![alt text](image-11.png)

![alt text](image-12.png)

Linux e mais complicado o escalonamento 

![alt text](image-13.png)

![alt text](image-14.png)

700 horas de GPU E CPU

![alt text](image-15.png)

registos da cpu que permite fazer 

![alt text](image-16.png)

pointers 

informacao sobre o evento....

![alt text](image-17.png)

isto e generico. no lininux e exit o end of the process. 

Fazer o Load do programa na memoria.

![alt text](image-18.png)

![alt text](image-19.png)

![alt text](image-20.png)

a memoria principal e dificil de gerir. 

vamos ter um conjunto de byters que sao enderecadas individualmente pelo meu processador. 
Um dos papeis principais que tenho aqui e a alocacao de memoria . 200 processos a funcionar ao mesmo tempo, vai ser uma manta de retalhos

![alt text](image-21.png)

First Bit
ser rapido, secalhar pode entrar na posicao 0,,

Best Fit 
Vai alocar o bloco de memoria mais pequeno, pequeno ma s suficiente grande paracaber os dados. 

Worst Fit 
contribuir para que nao haja fragmentacao... bloco maior de memoria. qual a logica, se a usar e provavel que consiga por outro processo.

![alt text](image-22.png)

Memory mangement deve manter uma lista. 
decidir processos , impoortante em telemovel importante em sistemas com p[oucos recursos. 

malloc e free

![alt text](image-23.png)


![alt text](image-24.png)

![alt text](image-25.png)

DEVICE MANAGEMENT

device drivers 

![alt text](image-26.png)

![alt text](image-27.png)

![alt text](image-28.png)

podemos ter sistemas diferentes e protocolos de comunicacao mais utilizado e o tCP IP sobre o qual assentei todos os outros protocolos. 

vamos trablhar com bluettoh na aula pratica talvez, o bluettoh .

O TCP ja nao vai tao longe , podem haver varios flavors desta interface com a propria rede. 

![alt text](image-29.png)

![alt text](image-30.png)

Process scheduling. 

![alt text](image-31.png)

![alt text](image-32.png)

![alt text](image-33.png)

num sistema que estja aberto na sabemos o que vai entrar la para dentro. 

e ha tanta capacidade de processamento para coisas banais. 
![alt text](image-34.png)

muitas coisas em sistemas embebidos, de x xem ex tempo o sitema e lancado vai ,,..

![alt text](image-35.png)

o escalonador, entra nesta [passagem de ready para running , 

quando esta interrupcao e programada periodicamente.....

![alt text](image-36.png)

ha 3 tiiops de escalonadores , shotrt term scheduler corre com extrema frequencia... 

o medium term scheduler, aliviar a carga do processador, 

long term scheduler eu escalonei para ser a noite programacao embates , controlar a carga do sistema de forma a nao sobrcarregar spo sitema. 

![alt text](image-37.png)

![alt text](image-38.png)

podemos tambem querer maximar o uqe e o numero de trablalhos, tepo de espera ... 

![alt text](image-39.png)

FCFC first come first serve


![alt text](image-40.png)

temos de distinguir CPU bound e 

![alt text](image-41.png)

![alt text](image-42.png)

![alt text](image-43.png)

![alt text](image-44.png)

![alt text](image-45.png)

![alt text](image-46.png)

![alt text](image-47.png)

![alt text](image-48.png)

![alt text](image-49.png)

![alt text](image-50.png)

![alt text](image-51.png)

![alt text](image-52.png)

![alt text](image-53.png)

![alt text](image-54.png)

algoritmo dos mais utiliuzado em algoritmos de tempor real , matematicamente olhando para estes tempos de execucao, 

![alt text](image-55.png)


![alt text](image-56.png)

outro algoritmo usado em sitemas normais e o ROUND-robin

10 - 100 ms 

![alt text](image-57.png)

temos aqui os processos time quantum de 20 

![alt text](image-58.png)

![alt text](image-59.png)

overhead de comutacao de processo pode ser grande o ideal ter um time quantum extremamente pequeno. 

![alt text](image-60.png)

algoritmo multi nivel por filas...

Posso fazer mais do que isso ,, usar politicas de escalonamento diferente

![alt text](image-61.png)

![alt text](image-62.png)

![alt text](image-63.png)

![alt text](image-64.png)

![alt text](image-65.png)

![alt text](image-66.png)

![alt text](image-67.png)

![alt text](image-68.png)

