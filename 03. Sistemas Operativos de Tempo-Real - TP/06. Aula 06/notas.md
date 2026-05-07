vai haver teste a proxima semana,

ha questoes da semna passada que nao sao escalonaveis....
ninguem fez questoes estranho....

![alt text](image.png)

inserir modadiladews sem iniciar o LINUX...

![alt text](image-1.png)

moduilo e o principio basico de ....

explicacao das macros 

![alt text](image-2.png)

programacao de mosulos

![alt text](image-3.png)

ring buffer, ou buffer circular...

buffer circular tem umm teamnho fisico, em modo de operacao e como senao tivesse definido

nao a arrays sem tamnho...
A ideia e simular algo que e circular, 

dessenvolver para o kernel e fazer funcoes, caso do linux, retornar um int

![alt text](image-4.png)

![alt text](image-5.png)

e necessario nos acerdermos ao codigo do kernel. 


![alt text](image-6.png)

explicar o conteudo da makelfile

![alt text](image-7.png)


![alt text](image-8.png)

insmod dentro do directorio dentro do nosso directorio...

![alt text](image-9.png)

lsmod modulos do sistema

ficheiro modules tem os modulos que estao activos inseridos no sistema

![alt text](image-10.png)

![alt text](image-11.png)

todos os simbolos que sao exportados atraves desta macro... Vamos ver esta macro, pode ser usado nos modulos...

No linuxm, existe uma macro que diz qual a tarefa atribuida ao CPU!!!!

![alt text](image-12.png)

as funcoes de inicializacao determinadas estruturas. 

![alt text](image-13.png)

definar variavei como globais, kmalloc vai allocar memoria dentro da area reservada para o kernel. 

estes modulos vao ser removidos e inseridos 

![alt text](image-14.png)

trabalhar com o /proc , vamos criar um ficheiro, penso que voces no shar device drivers, file operations. 

![alt text](image-15.png)

usam apontadores para funcoes, 

o endereco de uma funcao , podemos e devemos usar apontadores para funcoes.

estando no kernel a funcao e a mesma. 


proc
![alt text](image-16.png)

com as permissoes correctas, depois de criar o modulo....

se eu quiser criar directorio, dentro de um determinado directori, coloco o pai. 

![alt text](image-17.png)

![alt text](image-18.png)

remover

![alt text](image-19.png)

![alt text](image-20.png)

![alt text](image-22.png)

![alt text](image-23.png)

em user space na pratica em kernel space, existe efectivamente , um inteiro que represente um indice....

retornado pelo open...

![alt text](image-24.png)

indice de tabela de escritores de ficheiros... 

![alt text](image-25.png)

![alt text](image-26.png)

![alt text](image-27.png)

copy to use re from user, eles validam se pointer se efetivamente esta na memoria

quando for executar o processo nao estar na memoria. 

ele valiada se o apontador evalido.. 

![alt text](image-28.png)

quando nois fazemos entao a copia, em kernel space temos esta struct file . 

se fizer writes e reads. 

4. Advanced concepts 57 minutos no audio..

![alt text](image-29.png)

malloc e kfree

em kernel space alocacao de memoria.... Formas de instruir kmalloc para ter determinado comportamento. 

![alt text](image-30.png)

Listas Ligadas

API para listas ligadas..

![alt text](image-31.png)

tem so dois pointer next e prev... lista ligada permite andar de um lado para outro 

![alt text](image-32.png)

modulo disponibiliza todas as tarefas ativas no sistema. 

Mas e

![alt text](image-33.png)

![alt text](image-34.png)

![alt text](image-35.png)

![alt text](image-36.png)
![alt text](image-37.png)

arvores balanceadas sao self .. operacoes sobre esta arvore. estarem sempre balnceadas, 


![alt text](image-38.png)

estas arvores binarias, e um tipo de arvores binarias , ja tem os mecanismos para fazer essse balanceamento. 

variavel de controlo arvore binaria. 

![alt text](image-39.png)

atraves do rb_entry , utiliza o container of 

![alt text](image-40.png)

muito usado no kernel 

os processos estarem em diferentes listas, coloca m, vai inserir campo nas estruturas, 

![alt text](image-41.png)

api para arvores binarias

CONCURRENCIA

![alt text](image-42.png)

exite concurrencia no lernel do linux. temos de ter algum cuidado. o kernel e um codigo morto. fallamos que o lkernel executa no contexto do processo. 

quando acontece um interrupt, nao tem processo ativo e um ligar corrente num fio. e salte para a rotina que esta associada . De resto executa sempre em contexto de processo. 

![alt text](image-43.png)

Context switch, quando se muda um processo em execucao por outro... 

situacao de round robin, tempo como criterio, time slice. 

num scanf ou digite um input qualquer, nao pode ficar atribuido ao CPU, 

![alt text](image-44.png)

uma das coisa que se pode fazer sera preemptar 

preempt enable e disable. 

![alt text](image-45.png)

![alt text](image-46.png)

desabilito os interrupts, o interrupt nao e perdido . 

![alt text](image-47.png)

recurso partilhado, 

atomicammle implementa e guarda

![alt text](image-48.png)

![alt text](image-49.png)

![alt text](image-50.png)

![alt text](image-51.png)

![alt text](image-52.png)

tipo de dados e atomic_t inteiro que so consegue suportar valores ate 24 bits. 

![alt text](image-53.png)

![alt text](image-54.png)

![alt text](image-55.png)

tarefa pode ser escalonada para executar

no linux nao existe nenhum estado , 
todas as tarefas tem task running. 

![alt text](image-56.png)

isto e o que acontece num semaforo, vmaos  ver ja... 

gravacao 1:29:30

up ao semaforo, vai incrmentar o valor do semaforo.

![alt text](image-57.png)

lista ligada por arviore binaria pode ser implementada,,, e um contentor. o seu estado e alterado. 

![alt text](image-58.png)

atomocidade das operacoes..

![alt text](image-59.png)

![alt text](image-60.png)

SEMAFOROS

![alt text](image-61.png)

![alt text](image-62.png)

mutexes tem owner 

![alt text](image-63.png)

![alt text](image-64.png)

diferencas entre mutex semaforo 

![alt text](image-65.png)

mecanismos de sincronizacao de varias threads, quando chegam ali sao notificados, 

wait queu nao implementada mas usando uma lista... isto acontece muito no kernel..

adaptadas para sistemas de tempo real, todo codigo redundante e simplesmente deleted...

![alt text](image-66.png)

![alt text](image-67.png)

fazer download dos modiules como extraem o ficheiro , a partir de 1.4 implementamos ring buffer, implementa uma fifo. 

printk , API, depois como e o comportamento. e dificil criar varios processos ao mesmo tempo. 


Hoje foi dar overview aquilo que o kernel tem para desenvolvimento. 

vamos ver como kernel gero o tempo, aconselho que voces facam

o exercicio sera fazer timelines, prioridades fizxas ambientes multiprocessadore, recurso partilhados a ultima pergunta, rapidadas