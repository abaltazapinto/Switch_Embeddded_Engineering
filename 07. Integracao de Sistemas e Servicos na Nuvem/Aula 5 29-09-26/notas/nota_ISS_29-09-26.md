# vamos falar de orquestracao de contentores

dentro dessa bolha vamos colocar ... dependencias e tudo necessario.

Quando temos v arios nos!!!

![alt text](image.png)
Podemos ter varios nos com varias replicas desse contentor.
Escalamento horizontal, se houver mais procurar fazer mais contetnore.
self healing conseguir auto curar o contentor.
![alt text](image-1.png)
Cluster: fisicas ou virtuais, poderemos ter uma solucao hibrida !!!
Anatomia de um cluster.

hoje vamos tar virados para docker sworm.
![alt text](image-2.png)
nos master so correm normalmente software de gestao !!!
o trabalho correm nos worker nodes, que estao dispnivel para maquinas de trabalho !!!
worker nodes tem de informar master nodes a cerca da susa saude, carga quanti dis meus recursoss estao a ser utilizado, e tem de dizer que estao vivos de fora ao master saber que eles (worker node) esta disponivel !!!

![alt text](image-3.png)

O Desired state , e um plano que e disponibilizxado ao orquestrador como uma configuracao de uma implantacao ! !
ou seja o orquestrador tem de tentar chegar ao desired state, mas existe o estado actual e emensuravel pelas quantidade de cnotetores a correr.
![alt text](image-4.png)
![alt text](image-5.png)
![alt text](image-6.png)
hoje vamos falar do docker sworm
![alt text](image-7.png)
kubernetes e o orchestrador mais usado, mas a curva de aprendizagem e muita agreste.
O docker sworm e mais facil de aprender, mas e menos poderoso que o kubernetes. Kubernetes e o paraiso da orchestracao.
Para um uso menos exigente o docker sworm e porreiro.
![alt text](image-8.png)
o docker sworm tem ja o manual tls mtls b default

 entanto nao permite tanta personilaizacao.
 ![alt text](image-9.png)
 docker swarm init --advertise-addr 192.168.1.10
 o docker swarm e sempre arrancado num master !!!
# docker swarm init
> Converts standalone engine to Manager node and initializes the Raft state data base.

# --advertise-addr
> Defines the manager's IP

![alt text](image-10.png)
![alt text](image-11.png)
> docker swarm join-token worker

	Retrieve token for joining as worker

> docker swarm join-token manager

	Retrieve token for joining as a Manager

![alt text](image-12.png)
![alt text](image-13.png)
![alt text](image-15.png)
no gestor -> servidor de um api, pedidos para realizar accoes. motor de consenso, alllocador -> atribui iP , dispatcher -> cordena tarefas, aquele que sabe estado actual das tarefas.
![alt text](image-16.png)
Nos de gestao tem de chegar a um consenso.
Quorum e o numero minimo que e necessario para tomar uma decisao.
Quorum / 2 + 1. floor ou truncar.
> if active managers drop below the Quorum, it will stop to accept new configurations.

![alt text](image-17.png)
deve ser sempre usado um numero impar.
![alt text](image-18.png)
![alt text](image-19.png)
precisamo d eunidades atomicas de trabalho. O contentor e a minha unidade basica de orchestracao eu posso trabalhar coim unidades de contetor, e indivisvel.
![alt text](image-20.png)
![alt text](image-21.png)
![alt text](image-22.png)
> docker service ps
![alt text](image-23.png)
Um servico precisa de 400 megas de memoria ! o swarm scheduler vai ver entre os contentores qual e que tera disponivel!
![alt text](image-24.png)
![alt text](image-25.png)
Maquinas como raspberry pi pode se colcar o docker, orquestracao de ocntentores raspberrypi.
Regra da autocura continua.
Docker swarm modelo declarativo. COmparada a declaracao com estado desejado com o estado actual !!!
provas de vida heart beats atraves do porto de gewstao com provas de vida. Um unknow nao deve estar saudavel. Uma tarefa que esta perdida descarta se e comeca se uma nova.!
![alt text](image-26.png)
se fizer docker node ls, consigo ver quais sao os nos e o estado declarado para esse nos !!!
![alt text](image-27.png)
