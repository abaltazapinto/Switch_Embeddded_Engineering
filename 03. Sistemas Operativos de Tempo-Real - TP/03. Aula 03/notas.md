professor ricardo nao vai poder assegurar as aulas


![alt text](image.png)

saber resource sharing por ti. 

escalonamento aulas praticas ao sabado, a ideia , fazer fora das aulas e as aulas ao sabaod consigam ter nomeadamente uma politica de escaloonamento e resource sharing. 


![alt text](image-1.png)

![alt text](image-2.png)


avaliacoes, exercicio sobre real time, teste de esclanobilidade , isso e relativamente ssimples, depois tambem vou fazer na proxima aula ... resource sharing e heranca de prioridades e teto de prioridades . problema de inversao de prioridades. 

inversao de prioridade e sistemas de tempo real tem mecanismos para resolver isto. 

exrcicios de real time serao simples. 

Proximo sabado exercicio pratico, programimnhas para criar tarefas e politicas de escalonamento. 

exercicio mais teorico M2 , exercicio escrito com perguntas escolha multipla. 

![alt text](image-3.png)

dia 9 sera o M1, 
fazer o tracing ate determinado ponto. 

dia 30 sera um teste escrito sobre sistema operativos. para o kernel do linux. 

![alt text](image-4.png)

![alt text](image-5.png)

Abordagens de escalonamento, exitem 4=

no linux conseguimos implementar isto temos de usar as prioridades ja defenidas

![alt text](image-6.png)

aqui as tarefas vao mudando d eprioridade. 

prioridades dinamicas e mais complexo que fixas. 

![alt text](image-7.png)

O linux na classe RT usa isto. por niveis dde proiridadsde soft real time defina 100n niveis de prioridade. 

Neste contexto do Real Time, 

![alt text](image-8.png)

muitos algoritmos que nao servem para nada como LLF , 
e um algoritmo de sescalonamento. 

muito overhead com context switching. 
Esta politica de escalonamento tem uma localizacao ao ritmo monotonico !!
EDF earliest deadline first. tempo de excucao , o Deadline e o periodo. 

deadline absoluto ,  

![alt text](image-9.png)

edf no linux utilizar arvore binaria. 

avore binaria ordenadas pelo absoluto deadline. Sempre que ha uma tarefa que aparece. 

![alt text](image-10.png)

![alt text](image-11.png)

edf 100 %

![alt text](image-12.png)

![alt text](image-13.png)

Artigo de 69 ou 67

![alt text](image-14.png)

![alt text](image-15.png)

frameworks , placas grafica, nao preemptivo

analise baseada no tempo de resposta. 

![alt text](image-16.png)

O edf resolve o problema do stravation/ 

![alt text](image-17.png)

num sitema critico nao existe o overrun , ter um sistema em que isso aconteca. 

release logo...........

esclonamento.. 

![alt text](image-18.png)

![alt text](image-19.png)

![alt text](image-20.png)

![alt text](image-21.png)

o linux tem esse escalonamento hierarquico no geral embora o linux apesar de ser um sitema operativo que serve de base para muitos sistemas operativos de tempo real nao e um sitema operativo de tempo real, mas nao dexia de ser um sitema operativo general purpose. 

sistema operativo de tempo real. 

![alt text](image-22.png)

abordagens hierarquicas, diferentes niveis, pode nao ser diferentes prioridades, 

![alt text](image-23.png)

![alt text](image-24.png)

![alt text](image-25.png)

![alt text](image-26.png)

uma das abordagens , focar nas tarefas aperiodicas. 

nao focar no WCET forcr nos nas tarefas aperiodicas . sei que existem mas nao sei nada. uma das abordagens que e so uma tarefa. 

![alt text](image-27.png)

![alt text](image-28.png)

![alt text](image-29.png)

![alt text](image-30.png)

![alt text](image-31.png)

![alt text](image-32.png)

![alt text](image-33.png)

CBS 

![alt text](image-34.png)

usa uma abordagem parecida em termos largura, atribui uma largura de cbanda do CPU. outra caracteristica, mais adoprtada no Linux, 

![alt text](image-35.png)

![alt text](image-36.png)

![alt text](image-37.png)