vamos fazer exercicio 02 ate 04

objetivo terminar o 4

tem de novo
- multiplexagem
- 


desenho no quadro:
quadrado 
auadrado ______

barramento de 8 que esta ligado a cada um destes dislays, mas sao os mesmos 8 bits. vou querer por numeros diferentes em cada um !!!

A1 | A0

interrupcao de 2 em 2 ms. 

Aula pratica

trabalhar com ferquencias 1 /T ha de ser igual a 16MHx igual a frequencia de oscilacao a dividir com o pre scaler = , vai dividir sempre por 256 .... e aquel valor e fixo, transformar isto em periodo, T =  N / grquencia de oscilacao. 

Pensando no timer desta forma, a frequencia do anterior por dois, consegue se deduzir estas equacoes....

depende di OCR, t = (OCR + 1) N / frequencia

MODO 3 

o pwm e gerado por uma onda triangular. e a comparacao triangular com onda continua com valor. O que acontece . Se eu colocar este valor de comparacao. O que fazemos em termos de comparcao, temos de um lado valor de serra 

foto potenciometro ...

sempre que uma tensao for superio 0 se nao menor a saida vale 0

foto com tudo

enquanto o valor a saida vale 0 e a saida ,

foto tracejados ..

A e A' tem a mesma tensao so para esplicacao.

agora trabalhar na base de tempo, exercuo pede para usar base de tempo 2ms, 

para configura o time TCCR OCR e o TCN

TCCR e OCR , 

TCCR = 0b_________ os ultimos tres sao cs [2:0

tccr = ob_____101


wo TIMSK permite fazer enable ou disable, temos a interrupcao por overflow ou por output compare, queremos que o TIMSK seja por outputa compare TIMSK = /b000000010;

as interrupcoes, so tem 1 vetro de interrupcao, bota de reset, e depois tem vetor de interrupcao varios, As mais impoirtantes sao as que tem os valores mais baixos, ciom maior prioridade. !

sei() e ativar interrupto, e do registo status e o bit mais significativo, via se em assembly.