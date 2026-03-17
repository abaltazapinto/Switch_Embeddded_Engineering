TESTE dia 9 de Abril, 

o teste vai ser online...


Em termos de interrupcoes 


![alt text](image.png)

O estado do processador vai ser alterado, os parametros que tinha o processador ....

Codigo maquina... e aqui que se utiliza codigo maquina , minimo de linhas possiveis para nao se ter qualquer interferencia.

o rato e uma fonte de interrupcao. 

tambem temos interrupcoes ligados com comunicacoes. 

ISR interrupt service routine

fazer enable ou disable de interrupts. 
sistema em funcionar em bare metal nao ha sitema operativo... eles controlam os interrupts

Grava os registos do CPU do programa. 

Softwares 

tentar aceder a memoria que nao pertence aquele processo. 

INterrupt vector Lookup 

e uma tabela que tem todos interrupts... 

![alt text](image-1.png)

tabela de interrupcoes do  X86

tenho aqui as varias interrupcoes...

Agora em hardware e um pouco dificil sem ser bastante complicado..

interrupcao 0 que e o tiemer do sitema. alt text

![alt text](image-2.png)

vectores de interrupcao servem para o evento. o x86 externas sao 15. 
Tambem serve para essa parte para a prioridade das interrupcoes. 

sistema de poooling por vezes ate se utiliza...

![alt text](image-3.png)

interrupt controler e no fundoi mais yuum hardware os interrupts que vem do exterior com o processador. 

![alt text](image-4.png)

![alt text](image-5.png)
![alt text](image-6.png)
a latencia e basicamente o tempo do interruptor,
o controlador de interrupts, o numero de registos que vao ter de ser guardados, h instrucoes de codigo maquina que demoram muitos ciclos de relogio. 

![alt text](image-7.png)
![alt text](image-8.png)

sitema operativo com muitos processos esta solucao nao funciona, normalmente nos sitemas operativos serao quase sempre assincronas. 

Vai permitir que haja varios

![alt text](image-9.png)
![alt text](image-10.png)

![alt text](image-11.png)

direct memory access - e um mecanismo de interrupcoes tem um problema e preciso por o sistema a funcionar , 

![alt text](image-12.png)

quando nons temos dispositivos de alta performance. nao conseguimos trabalhar da mesma forma que anteriormente. 
so conseguimos transferir a taxa de 1kb opor segundo que uma taxa muito baixsa. 

![alt text](image-13.png)

![alt text](image-14.png)

cache , significa que o meu programa em vez de tar semore a ir ler os dados na memoria principal vai fazer iosso diretamente na cache. 

![alt text](image-15.png)

tornar transferencias de grandes quantidades de dados 

operea cao em dual mode permite me que o cpu seja executado em modos de=iferente 

![alt text](image-16.png)

kernel mode porque as rotinas dor kernell executam sempre neste modod 

![alt text](image-17.png)

![alt text](image-18.png)

o que me acontece no user mode ha muitas coisas restritas, como excutar todas as interrupcoes do CPU...

![alt text](image-19.png)

isto depende arquitetura para arquitetura. 

![alt text](image-20.png)

consequencias -> na coinsegue aceder a rotinal do kernel. 

![alt text](image-21.png)

![alt text](image-22.png)

se um processo em kernel mode escrever para ao endereco errado pode estar a acorromper o outro processo . em linux e possivel coorrer processos de tempo real 

quando ha um crash total emuito deificil de recuperar.

![alt text](image-23.png)

![alt text](image-24.png)

![alt text](image-25.png)

![alt text](image-26.png)

este e o exemplo do windows , o sistema operativo do windows mais complexo que o linux. 

hardware astraciton layer , kernel mode, sistema de ficheiros
API -> nos podemos atraves do user mode chamar interrupcoes, as interrupcoes nao correm como user mode mas correr m copmo user mode. 

![alt text](image-27.png)

![alt text](image-28.png)

fork e uma rotina dos istema oiperativo que me permite criar mais um processo. 

![alt text](image-29.png)

![alt text](image-30.png)

Se nos tivermos a excutar como os arduinos nao seguem bem isto. 

![alt text](image-31.png)

se tivermos sum programa em user mode e tivermos um nprocessador sofisticado nao pode ligar aqueles pin. 

![alt text](image-32.png)

proteccao de memoria e falar de memoria, e muito compliocada e uito chata. 

x86 foi projectado 1 mB de memoria o senhor a IBM 640n  k e mais que suficiente neinguem vai fazer programas que 200k

![alt text](image-33.png)

ROM na parte mais alta da memoria nao em baixo ->erro

![alt text](image-34.png)

vieram os pentihium consegui omos aceder a muito mnais memoria, deopis  d3cidioram abandoar o primeiro mega byte da memoria. 

Cada programa na minha memoria vai ter uma zona de memoria que lhe esta atribuida, imaginemos que temos uma memoria linear , se por alguma razao este tentar aceder a uma zona de memoria tentar aceder a umna zona dora da sua memoria

![alt text](image-35.png)

fora do zona de memoria vai gerar uma excep[cao. 

![alt text](image-36.png)

![alt text](image-37.png)

core dump dizem que eu sai da zona de m emoria que me estava reservada, 

![alt text](image-38.png)

este timer vai permitir detetar coisas como um programa de utilizador que esta parado num ciclo infinito

desde que haja uma interrupcao de timer de x em x tempo 

![alt text](image-39.png)

relativamente aon armazenamento dos dados, memoria principal e memoria secundaria que normalmente e nao volatil cD rom dvds fitas magneticas, e o meio maios bartro de o fazer.

![alt text](image-40.png)

ke uma memoria que e extremamente rapida .

![alt text](image-41.png)

a memoria cache esta aa uns nanometros do processador.

![alt text](image-42.png)
![alt text](image-43.png)

l1 mais pequena l2 iuntermedia
l3 

para ram podemos precisar de 300 ciclos. 90 e qualquer cosa por cento do programa. 

o principio da localizacao do codigo. 

entre a memoria ca he e a memoria principa; ==

![alt text](image-44.png)

![alt text](image-45.png)

O MMU

a cahce transfere pequenoos sblocos de cache por veze a64 bytes

A ram e utilizada quase como lixo grandes dados d ememoria


impacto nos sistemas embebidos
![alt text](image-46.png)

performance pode aumentar mas o determinismo e muito maior posso ter caches misse s os meu dados estar na cache. 

imprevisivel 

quando queremos calcular o tempo de execucao .. soma eu tenho o tepmpo que o programa demora a executar. Se eu for pessimista fou ter um slow pass. 

Vai estar previosto correr copm a pior performance possivel. 

![alt text](image-47.png)

em alguns sistemas embeb idos ate se desliga a cache.... 

![alt text](image-48.png)

![alt text](image-49.png)

impossivel comprar algo so com um core. 

arduinos ja com dois processadores, os smulticores ..

![alt text](image-50.png)

Podemos ter auqi kuma economia de escala que nos componentes e perifericos . a performance foi exponential ate os anos de 200. ate que deixa e comeca a linearizar... a unica forma a velocidade de processamento foi colocar , estavam nos limites da velocidade dos reloogios... 

![alt text](image-51.png)

software e mais complexo.... 

![alt text](image-52.png)

![alt text](image-53.png)

podemos ter dois tipos de sistemas operativos => simetrico ou assimetrico...

apenas as threads corriam em processadopres diferentess// 

Incialmente havia um big kernel lock => ele cloqueava a execucao em qualquer siti, mas veio a ser reduzido, 

![alt text](image-54.png)

![alt text](image-55.png)
em termos de acesso a memoria

![alt text](image-56.png)

pdoemos por aqui mais processadores svai haver contencao de acesso a memoria, quer dizer que este tipo de arquiteteura e muito limiada. 

![alt text](image-57.png)

com o aparecimento das caches reduzimo quase 90 por cento os acessos aos barramentos. 

![alt text](image-58.png)

existe aqui algoritmos complexos nos acessos a memoria. 

![alt text](image-59.png)

![alt text](image-60.png)

ja esta antiga ate de uma kalray mais para sistema embebidos isto e mais um processador que um microcontrolador. 

Cada um  deste cluster tinha uma memoria sprivada.. memoria cache do processador tambem aqui dentro. 

Varios barramentos jkque permitem aos processadores cpmunicarem. 

![alt text](image-61.png)

![alt text](image-62.png)

![alt text](image-63.png)

conceito lei de amadahl no funcdi e uma formula que nalisa os ganhos de performance...

![alt text](image-64.png)

vai resultar numa penalizacao grande mesmo com mullticore..

![alt text](image-65.png)

cada modulo e no funcdoi um conjunto de funcuonalidades 

![alt text](image-66.png)

parte da gestao de memoria quero colocar espaco para um vetror de um kilobyte... 

este modo de getao de memoria tem que fazer essas operacoes todas..

![alt text](image-67.png)

![alt text](image-68.png)

![alt text](image-69.png)

![alt text](image-70.png)

chamada ao sistema passa a trabalhar em kernel mode 

![alt text](image-71.png)

conceito importante...

Gestao de Processos.