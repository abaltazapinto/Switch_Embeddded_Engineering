#include <stdio.h>
#include <pthread.h>

#define NTHREADS 5

void *worker(void *arg)
{
    int *value;

    value = (int *)arg;

    printf("worker received i = %d\n", *value);

    return NULL;
}

int main(void)
{
    pthread_t threads[NTHREADS];
    int i;

    i = 0;
    while (i < NTHREADS)
    {
        pthread_create(&threads[i], NULL, worker, &i);
        i++;
    }

    i = 0;
    while (i < NTHREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    return 0;
}
