#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NOPERATIONS 500
#define AMOUNT 100

/*
 * Shared global state.
 * Both threads access this same variable.
 */
static int balance = 1000;

/*
 * Depositor thread:
 * repeats 500 times:
 *   1. reads balance
 *   2. waits 100 microseconds
 *   3. writes balance + 100
 */
void *depositor(void *arg)
{
    int i;
    int local_balance;

    (void)arg;

    i = 0;
    while (i < NOPERATIONS)
    {
        local_balance = balance;          // read shared state
        usleep(100);                      // simulate delay between read and write
        balance = local_balance + AMOUNT; // write new state

        i++;
    }

    return NULL;
}

/*
 * Withdrawer thread:
 * repeats 500 times:
 *   1. reads balance
 *   2. waits 100 microseconds
 *   3. writes balance - 100
 */
void *withdrawer(void *arg)
{
    int i;
    int local_balance;

    (void)arg;

    i = 0;
    while (i < NOPERATIONS)
    {
        local_balance = balance;          // read shared state
        usleep(100);                      // simulate delay between read and write
        balance = local_balance - AMOUNT; // write new state

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
