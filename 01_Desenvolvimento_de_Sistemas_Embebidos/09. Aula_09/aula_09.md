![alt text](image.png)

sudo apt install kernel-headers-rpi-v8

compilacao cruzada, 

![alt text](image-1.png)

![alt text](image-2.png)

feito para a versao 6.12 

![alt text](image.png)

![alt text](image-1.png)


![alt text](image-3.png)

![alt text](image-4.png)

![alt text](image-5.png)

exercicio registo 21 bits 

![alt text](image-6.png)

o data refister vai deteminar o duty cycle. 

para  o exercicio que usem o traditional PWM approach. 

![alt text](image-7.png)

os bits que tem activar neste registo de controlo. 

![alt text](image-8.png)

temos que activar 2 bits neste.

definir estrutura que mapeie e depoois vao usar a funcao .dev.mem 

![alt text](image-9.png)

![alt text](image-10.png)

![alt text](image-11.png)

se quisere, experimentar o prescaler ... comm diferente s frequencias 

o rasperrypi tem uns modulos bastante elaborado de geracao de sinais de relogio. 

isso esta no enuciado....

![alt text](image-12.png)

![alt text](image-13.png)

jiffies para a programacao de kernel serve de base de tempo , p

![alt text](image-14.png)

![alt text](image-15.png)

![alt text](image-16.png)

codigo do stor |

![alt text](image-17.png)

codigo do stror 

![alt text](image-18.png)

modulo de kernel. 

o que e diferente aqui e como aceder ao resgistos. elas fazem parte do API do linux

codigo do stor 

![alt text](image-19.png)

![alt text](image-20.png)

![alt text](image-21.png)

![alt text](image-22.png)

![alt text](image-23.png)

![alt text](image-24.png)

![alt text](image-25.png)

indicador de tranca, bloqueia o modulo em memoria,. quando o fichiero ja liberta o modulo. 

As funcoes de leitura escrita. trabalha em em nanosegundos. 
![alt text](image-26.png)

![alt text](image-27.png)

![alt text](image-28.png)

![alt text](image-29.png)

programcao do kernel nao temos acesso as funcoes da lib.c / 


exemplo para voces basico para o codigo nao ser muito extenso . 

![alt text](image-30.png)

placa de rede ligacao serie, vem dos nossos programa =, principalmente 

o primeiro exercicio e pegar neste codigo . 

![alt text](image-31.png)

conseguirmos usar este modulo para conseguir piscar o lled. 

![alt text](image-32.png)

chmar a funcao setGpioOutput value se tiver 1 colocar a 0, depois de explicar desta maneira es simples. 

programar modulos de kernel,

![alt text](image-33.png)

![alt text](image-34.png)

este open do /dev/mem para termos acesso aos enderecos fisicos de memoria por isso podemos usar os enderecos da datasheet. 

ao nivel do kernel temops permissoes para aceder a qualquer endereco de memoria, funcao especial para mapear o endereco dos registos que nos interessa, |

![alt text](image-35.png)

ou seja em vez de usadr iopen seguido de nmap, mas pega no enderco fisico .

![alt text](image-36.png)

Static serve para indicar que a variavel so visivel no modulo, , 
![alt text](image-37.png)


![alt text](image-38.png)

![alt text](image-39.png)

mkaefile obedece um formato especial ...

makefile
![alt text](image-40.png)

![alt text](image-41.png)

ultimo exercicio

medidor de frequencia de pwm, no fundoi e um contador de impulsos. 

sistema de interrupcoes externas do PI . associar uma interrupcao a cada um dos GPIO.

![alt text](image-42.png)

ficheiros de device tree, 

o software durante o arracnque consegue conifigurar automaticamente. 

exercicio criar ficheiro dispositivo vai funcionar como overlay

para o que kernel saiba 

![alt text](image-43.png)

![alt text](image-44.png)

![alt text](image-45.png)

o nosso modulo podia estar preparado para trabalhar com varios dispoisitivos. 

![alt text](image-46.png)