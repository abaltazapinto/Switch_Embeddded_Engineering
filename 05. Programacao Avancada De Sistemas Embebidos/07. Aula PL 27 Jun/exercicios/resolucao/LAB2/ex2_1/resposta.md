## Exercicio 2.1 - Thread-Safe Shared Counter

Neste exercicio foi implementado um contador global partilhado por varias threads.
Foram criadas 4 threads, e cada thread incrementou  o contador 20 000 vezes. Assim, o 4 * 20 000 = 80 000.

O programa foi executado varias vezes com o comando : 

	for n in {1..5}; do ./ex21_counter_mutex; done

Em todas as execucoes, o resultado obtido foi:

	Final counter	= 80000
	Expected	= 80000

Isso mostra que o acesso ao contador foi corretamente sincronizado

A variavel 'counter' e partilhada por todas as threads. A operacao 'counter++' nao deve ser tratada como uma operacao atomica, porque internamente pode ser vista como tres passos:

1. ler o valor atual de 'counter';
2. somar 1;
3. escrever o novo valor em memoria. 

Se as duas threads executarem estes passos ao mesmo tempo sem protecao, pode ocorrer uma race condition. Por exemplo, duas threads ler o mesmo valor antigo e depois excrever o mesmo valor atualizado, perdendo um incremento. 

Para evitar esse problema, foi usado um 'pthread_mutex_t'. O mutex protege a seccao critica. 

pthread_mutex_lock(&counter_mutex);
counter++;
pthread_mutex_unlock(&counter_mutex);

Desta forma, apenas uma thread de cada vez pode modificar o contador. Mesmo que o scheduler do sistema operativo altere a execucao das threads, o resultado final mantem se correto.

Tambem foi usado 'pthread_join()' para garantir que a thread principal espera que todas as worker threads terminem antes de imprimir o valor final. 

Concluise que a utilizacao do mutex tornou o acesso ao contador thread-safe, eliminando a race condition observada quando multiplas threads acedem a mesma variavel global sem sincronizacao.
