#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;

int done = 0;

void *child(void *arg)
{
    (void)arg;

    printf("child: started\n");
    sleep(1);
    printf("child: finished work\n");

    pthread_mutex_lock(&lock);

    done = 1;
    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    pthread_t t;

    printf("parent: begin\n");

    pthread_create(&t, NULL, child, NULL);

    pthread_mutex_lock(&lock);

    while (done == 0) {
        printf("parent: waiting...\n");
        pthread_cond_wait(&cond, &lock);
    }

    pthread_mutex_unlock(&lock);

    pthread_join(t, NULL);

    printf("parent: end\n");

    return 0;
}
