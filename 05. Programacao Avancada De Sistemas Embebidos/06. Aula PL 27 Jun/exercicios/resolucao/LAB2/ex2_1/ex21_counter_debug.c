#include <stdio.h>
#include <pthread.h>

#define N_THREADS 4
#define N_INCREMENTS 20000

static int counter = 0;
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg)
{
	long id = (long)arg;

	printf("[worker %ld] started\n", id);

	for (int i = 0; i < N_INCREMENTS; i++) {
		pthread_mutex_lock(&counter_mutex);
		counter++;
		pthread_mutex_unlock(&counter_mutex);
	}

	printf("[worker %ld] finished\n", id);

	return NULL;
}

int main (void)
{
	pthread_t threads[N_THREADS];

	for (long i = 0; i < N_THREADS; i++) {
		printf("[main] creating worker %ld\n",i);
		pthread_create(&threads[i], NULL, worker, (void *)i);
	}
	for (int i = 0; i < N_THREADS; i++) {
		printf("[main] waiting for worker %d\n", i);
		pthread_join(threads[i], NULL);
		printf("[main] worker %d joined\n", i);
	}

	printf("Final counter	= %d\n", counter);
	printf("Expected	= %d\n", N_THREADS * N_INCREMENTS);

	pthread_mutex_destroy(&counter_mutex);

	return 0;
} 
