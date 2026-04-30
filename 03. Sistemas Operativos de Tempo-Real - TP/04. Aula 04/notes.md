![alt text](image.png)

![alt text](image-1.png)

![alt text](image-2.png)

switch quando esta sobrecarregdo. 

abordagem MCS. 

tendo a possibilidadde numa situacao de aperto nao executamos aquela. 


Resource sharing

![alt text](image-3.png)

exclusao mutua porque depois existem outras abordagens, sao consifderados leitores , nao esta a alterar a informacao. 

as tarefas para poderem executar, tem de obter 1 coisa. 

essas zinas sao designadas como seccoes criticas ...

![alt text](image-4.png)

para executar isto so pode fazer uma tarefa de cada vvez, 

importante explicar este slide todo. 

![alt text](image-5.png)

deaclock qunado uma tarefa tem um recusrso e outro tarefa tem outro recurso a outra quer o recusrdo do primeiro. a plicacao nao consegue seguir a aplicacao com deadlocks. 

![alt text](image-6.png)

inversao d eprioridades qiando uma tarrefa mais alta prioridade esta a espera/ 

![alt text](image-7.png)

![alt text](image-8.png)

![alt text](image-9.png)

o maximo block in time nao e detreministico. 

nao e possivel fazer contas. 

![alt text](image-10.png)

![alt text](image-11.png)

![alt text](image-12.png)
melhor algoritmo OCPP

![alt text](image-13.png)

![alt text](image-14.png)

imediate faz a mesma coisa atribui teto de prioridade, estar ou nao estar bloqueado, as tarefas herdam a prioriadade maxima de um determinado recurso,. Aqui nao qui cpomeca a exutar com  aprioridade maxima. 

![alt text](image-15.png)

SRP e muito parecido ICPP tambem as vezes PCP

![alt text](image-16.png)

OCPP e CPP funcionam com prioridades estaticas, rate monotonoco deadline monotonico, nao funcionam com prioridades dinamicas, por exemplo EDF

![alt text](image-17.png)

Linux iomplementa em termos de algoritmos SCHED_DEADLINE 

![alt text](image-18.png)

contudo o LINUX, implementa uma heraanca de prioridades para resolver alguns problemas, e dos mais faceis de impolementar mas nao e eficiente. 

SCHED FIFO
SCHED DEADLINE

Sistemas multiprocessador. 

![alt text](image-19.png)

sistemas multicore varios processadores no mesmo sitio.

existem algumas abordagens, existem processadores com diferentes caracaterisitcas. 

Mas na maior parte dos casos sao sistemas identicos.

![alt text](image-20.png)

os processadores para funciionar tem de colocar as instrucoes na memoria. o codigo tem de viajhar da memoria ate aos regustos do processador. 

o problema e que maior parte dos casos nos temos barramento partilhado, portanto eu posso ter varios processadores, mas smepre que quer aceder a memoria os outros nao podem. 


sistemas em que memoria e distribuida. 

![alt text](image-21.png)

os multiprocessadores ainda sao usados com algum criterio. !
!
!

nao era facil transpor a teoria inerente ao uniprocessados para os sistemas multiprocessador. 

O facto quando temos de decidir entre 2 ou mais, adiciona complexidade. 

heuristica, e preciso no scomputadores implica processamento/

![alt text](image-22.png)

para simplificar a memoria e partilhada por todos. 

Migracao 

![alt text](image-23.png)

escalonador ??

se tiver muitos cores e muitos tarefas, sempre que  se ...

atomica, tirar uma tarfea e o outro selecionou essa tarefa. uma tarefa nao pode ser executada em 2 CPUS ao mesmo tempo 

![alt text](image-24.png)

Dhall effect n processado n + 1 tarfas !!!

uma tarefa pede deadlines. dhall effect. 

![alt text](image-25.png)

Particao , imaginem que tenho n tarefas e tem taza de utilizacao de 50 por cento mais ujm cabelinho. 

![alt text](image-26.png)

Bin packing, e considerado um problema hard. 

![alt text](image-27.png)

usando o first fit, assumindo que a capacidade do caixote e de 15, 

![alt text](image-28.png)

mais dois modelos de escalonamento. 

![alt text](image-29.png)

![alt text](image-30.png)

exercico para nos realizarmos, esqueci me de fazer o da ultima aula, temos de fazer o timeline de execucao ate ao 30 milisegundos, usandio duas abordagens de bin packing. 

![alt text](image-31.png)

![alt text](image-32.png)

matar o processo temos de lhe dar o identificador PID

![alt text](image-33.png)

temos que perceber como e que se criam os processos/ 

![alt text](image-34.png)

duplicnsdo o processo pai. 

![alt text](image-35.png)

![alt text](image-36.png)

![alt text](image-37.png)

as funcoes exec() permitem fazer mudar instrucoes aquele processo

🔥 exec() = substituição completa do processo


O processo continua com o mesmo PID
Mas:
código (text segment) → substituído
memória → substituída
stack/heap → substituídos

👉 É literalmente:

“mata o programa atual e carrega outro no mesmo processo”

🔁 Relação com fork()

Fluxo típico:

fork() → cria cópia (pai + filho)
filho chama exec() → substitui-se por outro programa

👉 Resultado:

Pai → continua igual
Filho → torna-se outro programa

⚙️ Ligação com o teu slide

No teu slide:

Disco → RAM → CPU (fetch/decode/execute)

Quando fazes exec():

👉 estás a dizer ao OS:

“carrega outro programa da RAM neste processo”

Ou seja:

novo conjunto de instruções
novo ciclo fetch/decode/execute

![alt text](image-38.png)

![alt text](image-39.png)

recompilar o kernel na proxima semana

mais usado como sistema operatovo. 

porque conseguimos dizer o que queremos colocar no sistema operativo. 

sistemas embebidos ou tem linux ouderivados de Linux. 

A funcao fork vai dupolicar o seu processo igual a si e dpois das funcoes exec vamos substituir as instrucoes. 

a funcao wait permite esperar pelo processo. 

![alt text](image-40.png)

![alt text](image-41.png)


pid do processo

![alt text](image-42.png)

getpid()

o que e uma thread. ||

e um processo, no kernel nao ha distincao entre uma thread e um processo. 

a forma como o kernel os cria. 

entidades isoladas. 

as threads vao partilhar a memoria do processo. 

Ao criar uma thread nao vou ter de alocar muita memoria para a thread porque a memoria vai ser partilhada aquel thread. 

A gestao da emoria e a mais complicada ...

![alt text](image-43.png)

![alt text](image-44.png)

criacao das threads 

![alt text](image-45.png)

![alt text](image-46.png)

![alt text](image-47.png)

tentar perceber como e que conjunto de tarefas como aquilo executa. 