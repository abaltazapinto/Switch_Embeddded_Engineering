![alt text](image.png)

![alt text](image-1.png)

![alt text](image-2.png)

![alt text](image-3.png)

saber a taz=xa de transmissao, o que interssa e que o emissor transmita o bit .

forma sincronizada com os tempos dos bits, esta repartida a mensagem sim sim

Em teoria nao seria preciso. aqui neste caso do avr sinceramente e um detalhe que podemos ver mais a frente. 
Nao sao necessarios, no caso do avr e uma questao que queria ver aqui nas caracteristicas, estava a falar da questao da sincronizacao, no caso de transmissao assicrona, qualquer pequeno descio do valor de frequencia do relogio, para trablhar a mesma taxa da transmuissao e da leitura

![alt text](image-4.png)

a maior parte das comunicacaoes serie, por exemplo usb embora tenha um protocolo,,  e tet e, usa a nivel fisico e codificacao byte. com start and stpoop bit. Em cada 10 bits que transmitimos so 8 e que sao de dados, a eficiencia acaba por ser 80 %. 

![alt text](image-5.png)

![alt text](image-6.png)
aspecto teoricoo

![alt text](image-7.png)

fullduplex ligacoes. com 3 condutore sno modo assincorono, licao de hoje estou me a focar no modo assincrono. 


![alt text](image-8.png)

![alt text](image-9.png)

![alt text](image-10.png)

baud rate e taxa de simbolos enviados.
grande periodo da historia dos computares a representacao digital era todo binariip

protocolosm da iultima geracao para duplicar , estao a correr as essa tecnicas. 

tempo de bit porque estou a transmitir bits. 

![alt text](image-11.png)

bit paridade permite detetar erros simples. o par e impar , 

![alt text](image-12.png)

sem analisar e detalhe este diagrama...

![alt text](image-13.png)

xclock nao e usadi so e usado nas transmissoes sincronas.

![alt text](image-14.png)

![alt text](image-15.png)


![alt text](image-16.png)

![alt text](image-17.png)

![alt text](image-18.png)

![alt text](image-19.png)

![alt text](image-20.png)

![alt text](image-21.png)
![alt text](image-22.png)

erro dos timings ou do stop bit.
data overun estao a chegar dados e nos nao estamos a ler.
erro de  paridade. 


![alt text](image-23.png)

falnco ascendente ou descendente, o que  e isto ?

![alt text](image-24.png)

Exercicio 

![alt text](image-25.png)

O STOR A FAZER 

![alt text](image-26.png)

FALOU double speed 

![alt text](image-27.png)


![alt text](image-28.png)

![](imalt textage-29.png)

cds 

![alt text](image-30.png)


![alt text](image-31.png)

mostrar as utilizacoes de flags, fazer a transmissao de todos caracteres todos que forem recebidos transmiti los de volta . 

fazer ciclo wihle e testar a flag 

![alt text](image-32.png)

![alt text](image-33.png)
![alt text](image-34.png)
![alt text](image-35.png)

diz que nao fazia sentido bloquear o programa fique a espera ate chegar um byte. 
para que par ou impar, paridade o bit paridade. 
po numero de bits a um deve ser par. 
se os recebidos nao for um da erro !
convencoes de paridades, 

![alt text](image-36.png)

![alt text](image-37.png)

![alt text](image-38.png)

UDR1 de seguida vamos escrever o bit a um para limpar aa flag...

![alt text](image-39.png)
e basicamente podemos logo a seguir para fazer o eco escrever , o para enviar e receber tem o mesmo nome em termos de ponto de visto de interface de software. 

comunicacao full duplex e preencher  a comunicacao full duplex.

os bytes nunca chegam a uma taxa mais alta doque sao enviados. 

![alt text](image-40.png)

podeia se ante sdeste , fazer um averificacao da flag para nao se comecar a transmitir. o que eu queria mostrar esta questao a mesma variavel para fazer a leitura e para fazer o envio. 

para limpar flag de recepcao , pois   tem razao 

![alt text](image-41.png)

na transmissao e preciso fazer limpeza este e so de leitura. uDRX

confirmar na fonte. 

![alt text](image-42.png)
![alt text](image-43.png)

saber como e pino e so de leitura ou nao !!!

![alt text](image-44.png)

![alt text](image-45.png)

Falar um pouco do protocolo I2C tambem designado por two wire interface. 

![alt text](image-46.png)

![alt text](image-47.png)

serie sincrono, linha dedicada para relogio e outro para dados, permite taxas de transmissao dependendo do controlador usado, mas no limite 5 megabits por segundo !!
master slave , tentar abolir esses termos e comeca se mais as desinacoes de targe

![alt text](image-48.png)

![alt text](image-49.png)

![alt text](image-50.png)
![alt text](image-51.png)
conceito de start e stop isto e um protocolo sincrono. 
o bit de paragem transmisso e gerado com transicao descendente quando o clock esta a um, as transmissoes o datasshet ate se refer a transacoes consite a sequencias de pacotes. 

exemplo d eleitura simples 

![alt text](image-52.png)

![alt text](image-53.png)

sete bits para enderco e depois um bit para ver se querefmos fazer uma. 

fica sempre reservado um  bit para fazer o acknowledge, 

![alt text](image-54.png)

![alt text](image-55.png)

![alt text](image-56.png)

![alt text](image-57.png)

![alt text](image-58.png)

![alt text](image-59.png)

![alt text](image-60.png)

![alt text](image-61.png)

![alt text](image-62.png)
"broadcast"

uma das possiveis aplicacapes e quando se pretende enviar a mesma mensagem para todos os dispositivo do barramenteo. !

![alt text](image-63.png)

rwi de two wire. 

sao 
![alt text](image-64.png)

temos o registo de dados, depois temos o registo. 
usar o micro como target. 

Aqui o , io tempo de bit a frequencia dio clock como habitualmente esta dependente da frequencia de cpu, par aqual podemos escrever um valoir a teza de transmissao par ao valor desejado , pre scaler.. 

4 levandao a 2 ao cubo

sao valores de 8 bits. 

![alt text](image-65.png)

![alt text](image-66.png)

tentativa erro para varios prescaler...


![alt text](image-67.png)

![alt text](image-68.png)

![alt text](image-69.png)

i2c tem algumas semelhancas com o can qualquer dispositivo pode assumir o papel de ocntrolados, mas a regra quem tem o papel d controlodadeor gere o clock. 

![alt text](image-70.png)

