![alt text](image.png)

![alt text](image-1.png)

![alt text](image-2.png)

somas multiplicacoes importante , a capacidade d um gpu fazz 1000 multiplicacoes em dois ou 3 ciclos de relogio, cpu normal muito mais.

![alt text](image-3.png)

processadores para operacoes matematicas, o objectivo deste dsp e para pegar num sinal e anlisalo. 
capaz de transformada de fourier. Audio video anlise de sensores. 

![alt text](image-4.png)

![alt text](image-5.png)

![alt text](image-6.png)

este arm nao faz processadore smas vende o desenho a propriedade intelectual. 

nxp e infineon fazem chips, 

![alt text](image-7.png)

watch dog e importante , 

![alt text](image-8.png)


numero limitado de vezes para programar fpga sistemas embebidos de muita performance, temos de programar o hardware, + caro

![alt text](image-9.png)

56 de memoria ONCHIP, ligado a um barramento, 

![alt text](image-10.png)

funcoes logicas xor etc..

![alt text](image-11.png)

ha parealelismo sempre no processador,  a principal vantagem e a baixa latencia

![alt text](image-12.png)

![alt text](image-13.png)

![alt text](image-14.png)

os aceladradores de intelegencia artificial sao implementados de forma analogica mais rapidos que os digitais,

comparacao de MCU MPU SOC 

![alt text](image-15.png)

![alt text](image-16.png)

![alt text](image-17.png)

nao consigo aceder ao hardware mesmo que eu seja root. 

nunca se consegue fazer esse bypass. isto permite grande seguranca. se tiver programs que facam asneiras nao conseguem deitar abaixo outros programas. Vxworks mutio caro usado em Satelites. 

diversao de prioridades e um problema conhecido..

![alt text](image-18.png)

sitemas que necessitem alta performance. ambiente de software rico. 

![alt text](image-19.png)

![alt text](image-20.png)

![alt text](image-21.png)

![alt text](image-22.png)

![alt text](image-23.png)

![alt text](image-24.png)

SSTEMAS OPERATIVOS A SEGUIR

![alt text](image-25.png)

as boards 

![alt text](image-26.png)

o sistema operativo faz e administrar o hardware. 

![alt text](image-27.png)

aritmetica xor e tal..

accumulador onde vai ser colocado o resultado das operacoes. 

![alt text](image-28.png)

![alt text](image-29.png)

program counter e um registo operacial n=que nos diz q=em que sitio da memoria nosencontramos. 

![alt text](image-30.png)

![alt text](image-31.png)

![alt text](image-32.png)

![alt text](image-33.png)

![alt text](image-34.png)

![alt text](image-35.png)

![alt text](image-36.png)

![alt text](image-37.png)

![alt text](image-38.png)

o endereco onde eu vou querer escrever e aqui os dados vao aparecer imediatamente. 

o que os chips tem que baralha isto tudo , interupts nao afta  a memoria, quando compras novo tem de se ver a memoria cache, e uma copia da memoria principal. 
programa pode ser interrompido s e for para transicao a seguir. 

![alt text](image-39.png)

Gerar sinais de controlo memory enable , gerir protocolos de acesso a Ram para que seja facilmente perceptibel, as memorias sao um bocadinho mais complicadas do que isto. Ele tambem tem que se decidir a que tipo de memoria vai aceder nao e, ele vai ter de decidir se o meu endereco estiver na gama que aqui est 

![alt text](image-40.png)

ROM OU RAM chip select . .

Os processadores modernos tem cache significa eu quando estou a aceder , hoje  em dia nao  acede a memoria principal diretamente so acede a memoria cache. 

a memoria ddr tem funcionamento diferente em termos de performance e timings. 

![alt text](image-41.png)

![alt text](image-42.png)

![alt text](image-43.png)

![alt text](image-44.png)

buffers mais sofisticados, ethernet pode ir ate aos 1024 bytes. 

cpu para cpu mais lento, mas tratadas pelo software de comunicacoes, first in first out in termos de bufferizacao, um barramento com o qual eu vou ligar o CPU . 

![alt text](image-45.png)

tecnologia DMA com processador 486 permitia que os perifericos acedessem a emoria sem qualquer interferencia do processador. 

eventos sinalizados atraves das interrupcoes, error handling deteta se e alguma parte do cirsuito se tem algum erro nas comunicacoes de paridade. comandos elevados, tudo isto aparece no status register. 

