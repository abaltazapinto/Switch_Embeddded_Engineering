#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N_OPERATIONS 500
#define AMOUNT 100

static int balance = 1000;
static pthread_mutex_t balance_mutex = PTHREAD_MUTEX_INITIALIZER;

void *depositor(void *arg)
{
    (void)arg;

    printf("[depositor] started\n");

    for (int i = 0; i < N_OPERATIONS; i++) {
        pthread_mutex_lock(&balance_mutex);

        int old_balance = balance;
        usleep(100);
        int new_balance = old_balance + AMOUNT;
        balance = new_balance;

        if (i % 100 == 0) {
            printf("[depositor] i=%d old=%d new=%d\n",
                   i, old_balance, new_balance);
        }

        pthread_mutex_unlock(&balance_mutex);
    }

    printf("[depositor] finished\n");
    return NULL;
}

void *withdrawer(void *arg)
{
    (void)arg;

    printf("[withdrawer] started\n");

    for (int i = 0; i < N_OPERATIONS; i++) {
        pthread_mutex_lock(&balance_mutex);

        int old_balance = balance;
        usleep(100);
        int new_balance = old_balance - AMOUNT;
        balance = new_balance;

        if (i % 100 == 0) {
            printf("[withdrawer] i=%d old=%d new=%d\n",
                   i, old_balance, new_balance);
        }

        pthread_mutex_unlock(&balance_mutex);
    }

    printf("[withdrawer] finished\n");
    return NULL;
}

int main(void)
{
    pthread_t t_depositor;
    pthread_t t_withdrawer;

    printf("[main] initial balance = %d\n", balance);

    printf("[main] creating depositor thread\n");
    pthread_create(&t_depositor, NULL, depositor, NULL);

    printf("[main] creating withdrawer thread\n");
    pthread_create(&t_withdrawer, NULL, withdrawer, NULL);

    printf("[main] waiting for depositor\n");
    pthread_join(t_depositor, NULL);
    printf("[main] depositor joined\n");

    printf("[main] waiting for withdrawer\n");
    pthread_join(t_withdrawer, NULL);
    printf("[main] withdrawer joined\n");

    printf("Final balance = %d\n", balance);
    printf("Expected      = %d\n", 1000);

    pthread_mutex_destroy(&balance_mutex);

    return 0;
}
