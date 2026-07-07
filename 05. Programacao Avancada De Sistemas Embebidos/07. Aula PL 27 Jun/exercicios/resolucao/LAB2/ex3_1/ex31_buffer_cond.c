#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#ifndef N_PRODUCERS
#define N_PRODUCERS 1
#endif

#ifndef N_CONSUMERS
#define N_CONSUMERS 1
#endif

#ifndef ITEMS_PER_PRODUCER
#define ITEMS_PER_PRODUCER 10
#endif

#ifndef P_INTERVAL
#define P_INTERVAL 100000
#endif

#ifndef P_BACKOFF
#define P_BACKOFF 40000
#endif

#ifndef C_INTERVAL
#define C_INTERVAL 100000
#endif

#ifndef C_BACKOFF
#define C_BACKOFF 20000
#endif

typedef enum {
    DATA_EMPTY,
    DATA_READY
} status_t;

typedef struct {
    int value;
    status_t status;
    pthread_mutex_t lock;
 	pthread_cond_t buffer_write_available;
	pthread_cond_t buffer_data_ready;
    int produced_count;
    int consumed_count;
} buffer_t;

static buffer_t buffer = {
    .value = 0,
    .status = DATA_EMPTY,
    .lock = PTHREAD_MUTEX_INITIALIZER,
	.buffer_write_available = PTHREAD_COND_INITIALIZER,
	.buffer_data_ready = PTHREAD_COND_INITIALIZER,
    .produced_count = 0,
    .consumed_count = 0
};

static int random_offset(void)
{
//	return srand(1);
    return (rand() % 11) - 5;
}

void *producer(void *arg)
{
    long id = (long)arg;

    for (int i = 0; i < ITEMS_PER_PRODUCER; ) {
        pthread_mutex_lock(&buffer.lock);

	while (buffer.status != DATA_EMPTY) {
		pthread_cond_wait(&buffer.buffer_write_available, &buffer.lock);
        }

        int old_value = buffer.value;
        int offset = random_offset();

        buffer.value = old_value + offset;
        buffer.status = DATA_READY;
	pthread_cond_signal(&buffer.buffer_data_ready);
	buffer.produced_count++;

        printf("[producer %ld] produced item=%d old=%d offset=%d new=%d\n",
               id, buffer.produced_count, old_value, offset, buffer.value);

        pthread_mutex_unlock(&buffer.lock);

        i++;
        usleep(P_INTERVAL);
    }

    printf("[producer %ld] finished\n", id);
    return NULL;
}

void *consumer(void *arg)
{
    long id = (long)arg;
    int total_items = N_PRODUCERS * ITEMS_PER_PRODUCER;

    while (1) {
        pthread_mutex_lock(&buffer.lock);

        if (buffer.consumed_count >= total_items &&
            buffer.status == DATA_EMPTY) {
            pthread_mutex_unlock(&buffer.lock);
            break;
        }

	while (buffer.status != DATA_READY) {
		pthread_cond_wait(&buffer.buffer_data_ready, &buffer.lock);
        }

        int value = buffer.value;
        buffer.status = DATA_EMPTY;
	pthread_cond_signal(&buffer.buffer_write_available);
        buffer.consumed_count++;

        printf("[consumer %ld] consumed item=%d value=%d\n",
               id, buffer.consumed_count, value);

        pthread_mutex_unlock(&buffer.lock);

        usleep(C_INTERVAL);
    }

    printf("[consumer %ld] finished\n", id);
    return NULL;
}

int main(void)
{
    pthread_t producers[N_PRODUCERS];
    pthread_t consumers[N_CONSUMERS];

    srand(1);

    printf("[main] producers=%d consumers=%d items/producer=%d\n",
           N_PRODUCERS, N_CONSUMERS, ITEMS_PER_PRODUCER);

    printf("[main] P_INTERVAL=%d P_BACKOFF=%d C_INTERVAL=%d C_BACKOFF=%d\n",
           P_INTERVAL, P_BACKOFF, C_INTERVAL, C_BACKOFF);

    for (long i = 0; i < N_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, (void *)i);
    }

    for (long i = 0; i < N_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void *)i);
    }

    for (int i = 0; i < N_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < N_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&buffer.lock);
	pthread_cond_destroy(&buffer.buffer_write_available);
	pthread_cond_destroy(&buffer.buffer_data_ready);
    printf("[main] produced=%d consumed=%d final_value=%d\n",
           buffer.produced_count,
           buffer.consumed_count,
           buffer.value);

    return 0;
}
