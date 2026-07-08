#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 10
#ifndef ITEMS_PER_PRODUCER
#define ITEMS_PER_PRODUCER 10
#endif

#ifndef P_SLEEP_MIN_MS
#define P_SLEEP_MIN_MS 100
#endif

#ifndef P_SLEEP_MAX_MS
#define P_SLEEP_MAX_MS 1000
#endif

typedef struct {
    int value;
    char sensor[12];
} sample_t;

typedef struct {
    sample_t samples[BUFFER_SIZE];

    int count;
    int read_idx;
    int write_idx;

    pthread_mutex_t lock;
    pthread_cond_t buffer_can_read;
    pthread_cond_t buffer_can_write;
} buffer_t;

 static buffer_t buffer = {
    .count = 0,
    .read_idx = 0,
    .write_idx = 0,
    .lock = PTHREAD_MUTEX_INITIALIZER,
    .buffer_can_read = PTHREAD_COND_INITIALIZER,
    .buffer_can_write = PTHREAD_COND_INITIALIZER
};

static int random_between(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}


void *producer(void *arg)
{
    long id = (long)arg;

    for (int i = 0; i < ITEMS_PER_PRODUCER; i++) {
        sample_t sample;

        sample.value = random_between(0, 1000);
        snprintf(sample.sensor, sizeof(sample.sensor), "sensor-%ld", id);

        pthread_mutex_lock(&buffer.lock);

        /*
         * TODO:
         * while buffer cheio:
         *     esperar em buffer_can_write
         */ 
        while (buffer.count == BUFFER_SIZE) {
            pthread_cond_wait(&buffer.buffer_can_write, &buffer.lock);
        }
        /*
         * TODO:
         * escrever sample em samples[write_idx]
         * avançar write_idx circularmente
         * aumentar count
         * sinalizar buffer_can_read
         */

        pthread_mutex_unlock(&buffer.lock);

        int sleep_ms = random_between(P_SLEEP_MIN_MS, P_SLEEP_MAX_MS);
        usleep(sleep_ms * 1000);
    }

    printf("[producer %ld] finished\n", id);
    return NULL;
}