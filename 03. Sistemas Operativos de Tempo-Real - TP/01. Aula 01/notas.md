alunos familiarizados

![alt text](image.png)

![alt text](image-1.png)

![alt text](image-2.png)

livros

![alt text](image-3.png)

alan burns 

![alt text](image-4.png)


Avaliacao 

![alt text](image-5.png)

1 e um exercicio de laboratorio para responder a um enunciado. 

sera no sabado da terceira semana de aulas. 

![alt text](image-6.png)

![alt text](image-7.png)

conceitos fundamentais de sistemas de tempo real ..

![alt text](image-8.png)

![alt text](image-9.png)

se ha um sitema critico ha sistema de tempo real....

safety do sistema e sao sistemas que interagem com o ambiente . Interaccao critica com o humanos. 

tempo real com o restantes e o aspeto temporal da aplicacao computational para alem de ser correcto tem de ser entregue durante um periodo bem defenido. Requesito importantissimo, 

tesla e sensores , ou maquina de raio x que pode entregar demasiada radiacao , tem consequencias que podera levar a morte. 

![alt text](image-10.png)

![alt text](image-11.png)

podemos separa em soft e hard time. os hard sao os mais criticos. 

sonda espaciais, pathfinder. seria interessante no seguimento desta aula com a sonda que posou em Marte. 

Case study....

vamos sempre pelo pior caso. 


![alt text](image-12.png)

sistema de cintrolo  LOGGER , casi piloto automatico, alarmes que serao entregues. tem de correr tudo na mesma plataforma. 

Requisitos de criticidade diferentes, tipo de estrategia 

![alt text](image-13.png)

jitter  ....

![alt text](image-14.png)

aeronave subir , descer - exemplo deste tipo de coisas.

![alt text](image-15.png)

![alt text](image-16.png)

sitema de controlo da retirada de agua de uma  mina, interessante analisar ..

![alt text](image-17.png)

![alt text](image-18.png)

![alt text](image-19.png)

sensor do monoxido de carbono de ve ser lido ...

conceito de periodo, periocidade. 

![alt text](image-20.png)

delay e variavel e otal jitter

periodo efectivo, 

![alt text](image-21.png)

modelo aplicado na robotica... sense-compute-actuate. 

![alt text](image-22.png)

estas tarefas podem ser comunicarem sincronizaram entre elas... 

periodico e esporadicas. 

![alt text](image-23.png)

neste modello de computacao ja a definicao de alguns conceitos. 

![alt text](image-24.png)

que algoritmos usar para gerir isto. 

job e instancia de execucao da tarefa. 

![alt text](image-25.png)

overheads este tipo sao agora incorporados no worst casa execution time. 

cache aceco ao cache.. as optimizacoes , sao deligados porque muitas vezes introduzem variacoes, que noa podem ser pr calculadas, e nao conseguimos calcular nao conseguimos calcular o worst case. 

![alt text](image-26.png)

![alt text](image-27.png)

![alt text](image-28.png)

avtivation instant... define o offset da tarefa e o seu finishing time.....

![alt text](image-29.png)

![alt text](image-30.png)

prremcao decorre do facto varias traefas parltiplharem o mesmo CPU, a tarfa em execucao pode ser substitiuida por outra tarefa. 

deadlocks....

nao podemos escrever ao mesmo tempo. 

![alt text](image-31.png)

context swithcing, overhead mnudaanca de estancia, tmepos de execuca menores mais faceis de calcular, pegamos sempre no worst casse.

o deadlocmk e termos uma de baixa prioriade impede uma high quando a baiza temn o lock que a outra prescisa. 

gravacao 2

![alt text](image-32.png)

![alt text](image-33.png)

![alt text](image-34.png)

![alt text](image-35.png)

![alt text](image-36.png)

topicos mais desenvolvidos na comunidade de tempo real de algoritmos... 

![alt text](image-37.png)

![alt text](image-38.png)

o mesmo tipo de inouts leva ao mesmo tipo de outputs. 

![alt text](image-39.png)

durante as aulas vamos focar aborgagens hibridas que sap aquelas que conhecemos a priori, 

vamos usar estatico e completamente online!!

![alt text](image-40.png)

![alt text](image-41.png)

pequena alteracao reannraja todo escalonamento !!

![alt text](image-42.png)

75% nao e muito bom, temopo de processamento que nao e utilizado o idela e sempre ao maximo. 

![alt text](image-43.png)

major cycle e o menor possivel....

![alt text](image-44.png)

![alt text](image-45.png)

![alt text](image-46.png)

round obin em comunicacoes, existe token e uma fila e quem executa e quem tem quantum , tem a prioridade para executar. 

![alt text](image-47.png)

problema de round robin imopede que tarefas mais urgentes sejam excutadas. 

![alt text](image-48.png)

is real-time always fast ? 

Can late results be wrong ? 

is average enough ?

