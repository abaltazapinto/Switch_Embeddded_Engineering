![alt text](image.png)

slide 14

eu estava ao lado do andre... 

![alt text](image-1.png)

board expansao o que e ?

display de 7 segmentos...

![alt text](image-2.png)

![alt text](image-3.png)
esquema importante da board de expansao.

multiplexer e switches mesmo porto, nao entendo nada... vou entender...

porque aqui desmultiplexagme ![alt text](image-4.png)

![alt text](image-5.png)

![alt text](image-6.png)

![alt text](image-7.png)

pwm como calculamos ???

![alt text](image-8.png)

pb7 no dfundo quando estiver a um sao tudo entradas, saidas de um micro 

no fundo esta ligado a uma linha a um drive do motor quando esta 1 quando esta 0 desativa, este dir0 e dir1 tem 4 comibinacoes duas delas corresponde a motor estar parado..

para estar a rodar numa direcao 

pb5 a 0 e pb6 a um .

para o motor rodar 

![alt text](image-9.png)

![alt text](image-10.png)

diferenca de potencial motor a trabalhar tenho de entender isto tudo. 

![alt text](image-11.png)

motores a posse , tem mais polos .... para fazer dar o passo vai ativar os polos em sequencia,,, ai nem e preciso o pwm, non caso de motor a passo a passo, .. tensao media... variacao media , estou a ficar meio perdido...

![alt text](image-12.png)

codigo da resposta... 

![alt text](image-13.png)


porta se

![alt text](image-14.png)

pwm e potenciometro... 

![alt text](image-15.png)

![alt text](image-16.png)

![alt text](image-17.png)

![alt text](image-18.png)

Portb = 0b01111111; para a geracao do pwm o enunciado nao especifica se deve ser o fast ou o outro ele sugere que tentem usar o do modo 1 supostamente e o mais adequado para . 
fazer contas com o PWM!!!

![alt text](image-19.png)

phase correct, temos conjunto limitado para o pwm.. temos uma proxima o 64.... 

![alt text](image-20.png)

usando o mesmo prescaler frequencia de 1 quilohertz... 

![alt text](image-21.png)

![alt text](image-22.png)

![alt text](image-23.png)

![alt text](image-24.png)

este bits nao e suposto estar 

![alt text](image-25.png)

![alt text](image-26.png)

basicamente o que nos queremos, ![
    
](image-28.png)

![alt text](image-27.png)

porque que passa a zero ? ![alt text](image-29.png)


![alt text](image-30.png)

![alt text](image-31.png)

funcao para converter duncao de valor de pwm 

![alt text](image-32.png)

pwm duty cycle ... OCR2 a 255 0 - 0porcento 255 %=100%

![alt text](image-33.png)

![alt text](image-34.png)

![alt text](image-35.png)

![alt text](image-36.png)

slide 19  

![alt text](image-37.png)

![alt text](image-38.png)

2ms - 
![alt text](image-39.png)
![alt text](image-40.png)

![alt text](image-41.png)

![alt text](image-42.png)

![alt text](image-43.png)

nivel de bits de paridade eu coloquei  os bits de paridade, pronto mas tambem se ele nao faz nverificacao !!!

de seguida vamos ter de testar , 

![alt text](image-44.png)

keyword case,,,

![alt text](image-45.png)

terminar com break;

nos cases

![alt text](image-46.png)

![alt text](image-47.png)

![alt text](image-48.png)

![alt text](image-49.png)

underflow

mudar de rotacao... aqui ja e discutivel.... 
9600 bits por segundo da para enviar 250 caracteres

![alt text](image-50.png)
![alt text](image-51.png)

![alt text](image-52.png)

programacao defensiva snprintf

vai fazer a escrita para o vector mas de forma controlada ! programacao defensiva...

![alt text](image-53.png)

bugs dificeis de detetar...

pwm de 0 a 100

ora bem e aqui a partir do momenmto que faco conversao de interiro para string estao prontos para envioar a string caractere a caractere.

![alt text](image-54.png)

![alt text](image-55.png)

strings interrupts.., 

![alt text](image-56.png)

envio pode ser enviado por interrupcoes 
![alt text](image-57.png)

variavel auxiliar para  o programa saber qual o caractere que esta a tramsitir. 

se isto estiver a zero... 

![alt text](image-58.png)

![alt text](image-59.png)

![alt text](image-60.png)

![alt text](image-61.png)

0 e volaor zero de ascii 

![alt text](image-62.png)

![alt text](image-63.png)


![alt text](image-64.png)

funcinamento 3 

![alt text](image-65.png)

![alt text](image-66.png)

![alt text](image-67.png)

interrupcao para modos pwm ... tentar entender isto tudo  !!!

![alt text](image-68.png)

![alt text](image-69.png)

![alt text](image-70.png)

comutacoes quando se muda o valor do OCR a meio do ciclo..

pode criar confusoes quando esta a fazer a essa transicao. 

![alt text](image-71.png)

![alt text](image-72.png)

![alt text](image-73.png)

phase correct 

![alt text](image-74.png)
timer 2 nao tem os mesmos que timer 1

![alt text](image-75.png)

![alt text](image-76.png)

relogio externo ... a seleccao desse modeo e feito atraves deste modos, para poder configurar

![alt text](image-77.png)

![alt text](image-78.png)

![alt text](image-79.png)

![alt text](image-80.png)

![alt text](image-81.png)

![alt text](image-82.png)

