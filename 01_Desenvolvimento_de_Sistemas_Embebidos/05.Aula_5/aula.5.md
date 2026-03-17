Aula 5

Falaram de SPI e I2C na ultima aula de fundamentos nao se entra em grandes detalhes. 

O arduino e uma plataforma que foi criada para iniciantes 

![alt text](image.png)

de certa forma ja acaba por evoluir para umsegmento profissional , ja a simplificacao e abstracao

quando se fala de arduino e composto pelas plcas, 
has=rdware, placas de expansao, que permitem adicionar modulos adicionais que permitem adicionar modulos ao microcontrolador base. 

tudo isto ha clones do que os da marca arduino . 

Arduino e bom para fazer prototipagem rapida. 

esta a falar de tool chains. 

![alt text](image-1.png)

unidade de gestao dememoria e linux

![alt text](image-2.png)

outra arquitectura MIPS, tem suporte no IDE o que permite inciar facilmente um prototipo no sistema. 
![alt text](image-3.png)

![alt text](image-4.png)

![alt text](image-5.png)

do ponto de vist ade software, a ideia e que iuu m programa em arduino, tem uma sfuncao de steup e depois o loop , que um funcao chamada repetidamente. ||

Portanto , mas isso e uma simplificacao a funcao main esta la . 

![alt text](image-6.png)

o ficheiro binario que  vai ser transferido para la/. 

o ciclo e erepetido caso estejam definidas sao chamadas. serialEventRun*( pseudo assicrona, op professor nunca usou a funcao. 

![alt text](image-7.png)

![alt text](image-8.png)

![alt text](image-9.png)

fazem parate do mapa de memoria, e possivel obter um pointer para esse registos, e isso que esta ffuncao faz.

a posicao de memoria corresponde a posicao de mormoria que corresponde a ess porto.

desativar as interrupcoes cli

isso e guardado numa variavel temporaria, esta instrucao . 

o mesmo tipo de analise pode=ia se fazer neste PIn mode, 
![alt text](image-10.png)

para que o pull up fique activo. 

![alt text](image-11.png)

a biblioteca em arduino imlementa este tipo de codigo !!

![alt text](image-12.png)

![alt text](image-13.png)

wire penso que es estatica e de c++;

para calcular o ![alt text](image-14.png)

![alt text](image-15.png)

depois para fazer a transmissao propriamente dita, que tinha passar por varias fases, 

![alt text](image-16.png)

![alt text](image-17.png)

![alt text](image-18.png)

acknioledge. obriga uma certa sequencia 
![alt text](image-19.png)

![alt text](image-20.png)

estou perdido para entender isto 

![alt text](image-21.png)

codigo de arduino para dispositivos I2c muito mais simples com 3 linhas de codigo que faz exctamente a mema coisa.

![alt text](image-22.png)

esp 32 ja ha microcontroladores com mais do  que um nucleo ou mucrocontrolador de low core que tem outros perifericos, 

![alt text](image-23.png)

![alt text](image-24.png)
o aspecto que queria menciona em sistemas de microcontroladores com mais que um  nucleo .

todo o partu=ido , 

arquitetura de memori apartilhada, para sistemas mais complexos ja e usa sistema operativos para arduino, FREERTOS que vamos usar, sera bom aprender isso antes. 

Linux sistemas operativos semaforos acesso a recursol[s se essas variaveis , 

Tem de haver maneira de arbitrar esse acesso. 

![alt text](image-25.png)

a transicao para o ambiente linux. 

![alt text](image-26.png)

main cpp 

![alt text](image-27.png)
![alt text](image-28.png)
![alt text](image-29.png)


o nucleo e so um nucleo do sistema operativo. 


p[ara sistemas embebidos usamos linux queremos distribuicao tenha o consjunto minimo de software. 

![alt text](image-30.png)


![alt text](image-31.png)

![alt text](image-32.png)

uso de sistema operativo oferece nivel de abstracao maior. 

a nivel das bibliotecas , 

intrepretador para php esta escrito em C

![alt text](image-33.png)

![alt text](image-34.png)

constituicao dos sistemas linux os componentes tipicos sao estes aqui -> kernel
-> 

o boot loader e um programa auxiliar. 
nos computadores dos ultimos 20 anos ja sao sistema UEFI , BIOS 
![alt text](image-35.png)

![alt text](image-36.png)

o firmaware ate pode carregar o proprio kernel , o linux tem suporte para permitir o carregamento automatico por sistemas do tipo ..


![alt text](image-37.png)

![alt text](image-38.png)

![alt text](image-39.png)

sistemD definir quais os programs devem ser lancados no incio do sistema, existe um conjunto de regras, nos prmeiros sistemas linux, inspirado nos sistemas unnix soriginais, e mantido init scomo systemd,

![alt text](image-40.png)

ilustracao de dependencia de processos, 