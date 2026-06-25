#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int counter = 0;
pthread_mutex_t mtx_counter = PTHREAD_MUTEX_INITIALIZER;

// Function executed by threads
void	*thread_function(void *arg) {
/*
int *num = (int *)arg; // Casting to int pointer
	printf("Thread %d is running.\n", *num);
	pthread_exit(NULL); // Thread exit with no return value
*/
	(void)arg;
	for (int i = 0; i < 100000; i++) {
		pthread_mutex_lock(&mtx_counter);
		counter++;
		pthread_mutex_unlock(&mtx_counter);
	}
	pthread_exit(NULL);
}

int	main() {
	pthread_t threads[3]; // Array of thread IDs
	int args[3] = {1, 2, 3}; // Arguments to pass to each thread
	for (int i = 0; i < 3; i++) {
		if(pthread_create(&threads[i], NULL, thread_function, (void *)&args[i]) != 0) {
			printf("Error creating thread %d\n", i);
			return 1;
		}
	}
	// Waiting for each thread to finish
	for (int i = 0; i<3; i++) {
		pthread_join(threads[i], NULL);
		printf("Applied join on thread %d\n",i);
	}
	printf("All threads completed.\n");
	printf("Final counter %d\n", counter);
	return 0;
}

