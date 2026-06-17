#include <stdio.h>
#include <pthread.h>

#define NTHREADS 5

void	*worker(void *arg)
{
	(void)arg;

	printf("hello from worker thread: %lu/n", (unsigned long)pthread_self());

	return NULL;
}

int	main(void)
{
	return 0;
}
