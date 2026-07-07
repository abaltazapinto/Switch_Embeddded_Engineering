#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 10

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
