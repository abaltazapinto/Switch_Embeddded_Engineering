#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N_ITEMS 10

#define BUFFER_EMPTY 0
#define BUFFER_AVAILABLE 1

static int buffer_status = BUFFER_EMPTY;
static int buffer_value = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg)
{
	(void)arg;

	for (int i = 1; i <= N_ITEMS; i++) {
		usleep(300000); // simula o tempo para produzir dados

		while (1) {
			pthread_mutex_lock(&mutex);

			if (buffer_status != BUFFER_EMPTY) {
				pthread_mutex_unlock(&mutex);
				usleep(1000);
				continue;
			}

			buffer_value = i;
			buffer_status = BUFFER_AVAILABLE;

			printf("[producer] produced value %d\n", buffer_value);

			pthread_mutex_unlock(&mutex);
			break;
		}
	}
	return NULL;
}

void	*consumer(void *arg)
{
	(void)arg;

	for (int i = 1; i < N_ITEMS; i++) {
		while(1) {
			pthread_mutex_lock(&mutex);

			if (buffer_status != BUFFER_AVAILABLE) {
				pthread_mutex_unlock(&mutex);
				usleep(1000);
				continue;
			}

			int value = buffer_value;
			buffer_status = BUFFER_EMPTY;

			printf("[consumer] consumed value %d\n", value);

			pthread_mutex_unlock(&mutex);
			break;
		}
	}

	return NULL;
}

int	main(void)
{
	pthread_t t_producer;
	pthread_t t_consumer;

	printf("[main] starting producer and consumer\n");

	pthread_create(&t_producer, NULL, producer, NULL);
	pthread_create(&t_consumer, NULL, consumer, NULL);

	pthread_join(t_producer, NULL);
	pthread_join(t_consumer, NULL);

	pthread_mutex_destroy(&mutex);

	return 0;
}
