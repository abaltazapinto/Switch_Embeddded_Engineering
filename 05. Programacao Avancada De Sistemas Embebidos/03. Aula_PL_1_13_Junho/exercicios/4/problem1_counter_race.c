#include <stdio.h>
#include <pthread.h>

#define NTHREADS 3
#define NINCREMENTS 100000

static int counter = 0;
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg)
{
    int i;

    (void)arg;

    i = 0;
    while (i < NINCREMENTS)
    {
        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_mutex_unlock(&counter_mutex);

        i++;
    }

    return NULL;
}
int main(void)
{
    pthread_t threads[NTHREADS];
    int i;

    i = 0;
    while (i < NTHREADS)
    {
        pthread_create(&threads[i], NULL, worker, NULL);
        i++;
    }

    i = 0;
    while (i < NTHREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    printf("expected counter = %d\n", NTHREADS * NINCREMENTS);
    printf("final counter    = %d\n", counter);

    return 0;
}
