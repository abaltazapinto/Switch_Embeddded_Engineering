#include <stdio.h>
#include <pthread.h>

#define NTHREADS 5

void *worker(void *arg)
{
    (void)arg;

    printf("hello from worker thread: %lu\n", (unsigned long)pthread_self());

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
        printf("main created thread: %lu\n", (unsigned long)threads[i]);
        i++;
    }
/*
    i = 0;
    while (i < NTHREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
*/
    printf("goodbye from main\n");

    return 0;
}
