![alt text](image.png)

so numeros estas imagens..

![alt text](image-1.png)

![alt text](image-2.png)

![alt text](image-3.png)

flatten e reorganizar os valores...

![alt text](image-4.png)

numpy e usado para flattened input...................

3 entradas duas saidas.... 

isto e um fully connected, isto e cada neuronio da layer a seguir e conectado a todos neurosnios da camada anterior.. 

![alt text](image-5.png)

wight and biases 

como contamos os parametros numa camada densa !! mais dois vbiases , estamos a falar nesta rede temos 8 parametros 

![alt text](image-6.png)


neste parametro esta o treino, 


cada rede neuronal trabalho com um input de cada vez. 

![alt text](image-7.png)

vector x contem 784 piceix que e uma image flatened

![alt text](image-8.png)

o peso da nossa rede de coisas treinavei vao ser 7850 parametros

softmax a saida, flatten a entrada, apenas formas de converter os dados. 

o que que estas camadas sescondidas.... 

![alt text](image-9.png)

o que esta camada pode ajudar a reconhecer as classes.

and OR XOR....

![alt text](image-10.png)

![alt text](image-11.png)

relu funcao de ativacao !!!! quando valor negativo da output de 0,, 

![alt text](image-12.png)

first layer neste exemplo a proimeira camada calcula 2x + 1 , 
i=uma funcao de ativacao continua a ser linear !!! 

![alt text](image-13.png)

![alt text](image-14.png)

custo de diferentes arquitecturas....

saber se podemos sempre reduzir em sistemas embebido


![alt text](image-15.png)

foward pass passar da entrada para a saida !!!!

![alt text](image-16.png)

![alt text](image-17.png)

no primeiro neuronio temos 0.56 - -.15 

![alt text](image-18.png)

![alt text](image-19.png)

cross entropy mede o erro de previsao 

![alt text](image-20.png)

accuracy podes acertar no alvo, o quao bom esta nos acertos e nos loss e nao a accuracy 

![alt text](image-21.png)

![alt text](image-22.png)

![alt text](image-23.png)

![alt text](image-24.png)

learning rate e para rexde inteira 

![alt text](image-25.png)

o adam e uma das maiores inovacoes qeu fex andar muito mais rapido !!!

redes 100 bilioes de parametros,,,,,,,,,,,,

placas graficas bom para fazer calculos pesados !!!

![alt text](image-26.png)

exemplos que poderemos usar!!!

![alt text](image-27.png)

dataset qe tamos usar, nao vamos treinar a cada foward pass, definimos mase um batch size... 


o que e uma epoch e o que nao e...

![alt text](image-28.png)

diferentes batches e diferentes epoch. loga a loss vai ser diferente , 

parametros pesos e biase, 

hyperparametro sao parametros que nos humanos definimos!!! 

![alt text](image-29.png)

como garantimos que o nosso algoritmo funciona... 

depede da relacao com os dados de treino. 

![alt text](image-30.png)

![alt text](image-31.png)

![alt text](image-32.png)

ops nosso ddados de validacao ja nao estao a conseguir melhores resultados.

underfitting

![alt text](image-33.png)

![alt text](image-34.png)

exemplo mais ou menos. uma gap enorme estamos a fazer um overfitting

dados de trino esta a aprender mas nao validar. 

![alt text](image-35.png)

lambda controla a intensidade do que estamos a fazer !!!

quando esta a fazer overfitting 

![alt text](image-36.png)

mais um conceito , durante o treino podem fazer dropouts, activar e desativar neuronios !!

![alt text](image-37.png)

dados importam mais que muitas camadas !!!

quandi se ois redes neuronais a detetar pessoas!!! pessoas com pigmentacao mais escuras nao estavam representadas no dataset !! logo a rede precisa de estar equilibrada, senao fazer data augmentation. to have plausible inputs and outputs/. 

![alt text](image-38.png)

confusion matrix, das 42, gostei de aprender a confusion matrix.. 

![alt text](image-39.png)

![alt text](image-40.png)