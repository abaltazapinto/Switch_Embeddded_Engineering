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

    config = (t_thread_config *)arg;

    printf("worker config: input=%d output=%d add=%d delay=%d\n",
           config->input_index,
           config->output_index,
           config->value_to_add,
           config->delay_seconds);

    return NULL;
}

int main(void)
{
    return 0;
}
