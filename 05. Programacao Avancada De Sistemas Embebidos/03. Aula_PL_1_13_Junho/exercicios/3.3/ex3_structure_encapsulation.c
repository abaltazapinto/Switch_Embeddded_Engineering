#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NCELLS 3
#define NTHREADS 3

static int shared_array[NCELLS] = {0, 0, 0};

typedef struct s_thread_config
{
    int input_index;
    int output_index;
    int value_to_add;
    int delay_seconds;
} t_thread_config;

void *worker(void *arg)
{
    t_thread_config *config;
    int value;

    config = (t_thread_config *)arg;

    while (1)
    {
        value = shared_array[config->input_index];
        shared_array[config->input_index] = 0;
        shared_array[config->output_index] = value + config->value_to_add;

        sleep(config->delay_seconds);
    }

    return NULL;
}

int main(void)
{
    pthread_t threads[NTHREADS];
    t_thread_config configs[NTHREADS];
    int i;

    printf("initial shared_array = [%d, %d, %d]\n",
           shared_array[0],
           shared_array[1],
           shared_array[2]);

    configs[0].input_index = 0;
    configs[0].output_index = 1;
    configs[0].value_to_add = 10;
    configs[0].delay_seconds = 1;

    configs[1].input_index = 1;
    configs[1].output_index = 2;
    configs[1].value_to_add = 20;
    configs[1].delay_seconds = 2;

    configs[2].input_index = 2;
    configs[2].output_index = 0;
    configs[2].value_to_add = 30;
    configs[2].delay_seconds = 3;

    i = 0;
    while (i < NTHREADS)
    {
        pthread_create(&threads[i], NULL, worker, &configs[i]);
        i++;
    }

    i = 0;
/*
    while (i < NTHREADS)
    {
	//pthread_join(threads[i], NULL);
	//i++;
	
    }
*/

while (1)
{
    printf("shared_array = [%d, %d, %d]\n",
           shared_array[0],
           shared_array[1],
           shared_array[2]);

    sleep(1);
}

    return 0;
}

