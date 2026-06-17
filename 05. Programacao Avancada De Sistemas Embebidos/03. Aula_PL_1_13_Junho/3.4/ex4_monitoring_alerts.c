#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

static int system_value = 20;

void *sensor_thread(void *arg)
{
    (void)arg;

    while (1)
    {
        printf("sensor alive, value = %d\n", system_value);
        sleep(1);
    }

    return NULL;
}

void *monitor_thread(void *arg)
{
    (void)arg;

    while (1)
    {
        printf("monitor reads value = %d\n", system_value);
        sleep(1);
    }

    return NULL;
}

int main(void)
{
    pthread_t sensor;
    pthread_t monitor;

    srand(time(NULL));

    pthread_create(&sensor, NULL, sensor_thread, NULL);
    pthread_create(&monitor, NULL, monitor_thread, NULL);

    pthread_exit(NULL);
}
