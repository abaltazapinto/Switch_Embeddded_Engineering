#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NOPERATIONS 500
#define AMOUNT 100

/*
 * Shared global state.
 * Both threads access this same balance.
 */
static int balance = 1000;

/*
 * Mutex protecting balance.
 * Any read-modify-write operation on balance must happen while holding this lock.
 */
static pthread_mutex_t balance_mutex = PTHREAD_MUTEX_INITIALIZER;

void *depositor(void *arg)
{
    int i;
    int local_balance;

    (void)arg;

    i = 0;
    while (i < NOPERATIONS)
    {
        /*
         * Critical section starts here.
         * We protect the full sequence:
         * read -> delay -> write
         */
        pthread_mutex_lock(&balance_mutex);

        local_balance = balance;
        usleep(100);
        balance = local_balance + AMOUNT;

        pthread_mutex_unlock(&balance_mutex);
        /*
         * Critical section ends here.
         */

        i++;
    }

    return NULL;
}

void *withdrawer(void *arg)
{
    int i;
    int local_balance;

    (void)arg;

    i = 0;
    while (i < NOPERATIONS)
    {
        /*
         * Same critical section idea.
         * The withdrawer must not read/write balance while depositor is updating it.
         */
        pthread_mutex_lock(&balance_mutex);

        local_balance = balance;
        usleep(100);
        balance = local_balance - AMOUNT;

        pthread_mutex_unlock(&balance_mutex);

        i++;
    }

    return NULL;
}

int main(void)
{
    pthread_t deposit_thread;
    pthread_t withdraw_thread;

    pthread_create(&deposit_thread, NULL, depositor, NULL);
    pthread_create(&withdraw_thread, NULL, withdrawer, NULL);

    pthread_join(deposit_thread, NULL);
    pthread_join(withdraw_thread, NULL);

    printf("expected balance = %d\n", 1000);
    printf("final balance    = %d\n", balance);

    return 0;
}
