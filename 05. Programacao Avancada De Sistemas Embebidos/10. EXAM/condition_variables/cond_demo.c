#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 10

int slot = 0;      // dado produzido
int count = 0;     // variável de estado: 0 = vazio, 1 = cheio

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t data_ready = PTHREAD_COND_INITIALIZER;
pthread_cond_t space_available = PTHREAD_COND_INITIALIZER;

void *producer(void *arg)
{

	(void)arg;
    for (int i = 1; i <= N; i++) {
        pthread_mutex_lock(&m);

        while (count == 1) {
            printf("PRODUCER: buffer cheio -> vou dormir\n");
            pthread_cond_wait(&space_available, &m);
        }

        slot = i;
        count = 1;

        printf("PRODUCER: produzi %d\n", slot);

        pthread_cond_signal(&data_ready);
        pthread_mutex_unlock(&m);

        sleep(5);
    }

    return NULL;
}

void *consumer(void *arg)
{
	(void)arg;
    for (int i = 1; i <= N; i++) {
        pthread_mutex_lock(&m);

        while (count == 0) {
            printf("CONSUMER: buffer vazio -> vou dormir\n");
            pthread_cond_wait(&data_ready, &m);
        }

        int value = slot;
        count = 0;

        printf("CONSUMER: consumi %d\n", value);

        pthread_cond_signal(&space_available);
        pthread_mutex_unlock(&m);

        sleep(2);
    }

    return NULL;
}

int main(void)
{
    pthread_t prod, cons;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    printf("MAIN: terminou\n");
    return 0;
}
