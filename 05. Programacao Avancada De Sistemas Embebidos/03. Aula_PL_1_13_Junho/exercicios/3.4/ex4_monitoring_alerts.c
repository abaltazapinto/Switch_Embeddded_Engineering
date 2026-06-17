#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

static int system_value = 20;

void *sensor_thread(void *arg)
{
    int delta;
    int sleep_time;

    (void)arg;

    while (1)
    {
        delta = (rand() % 7) - 3;
        system_value = system_value + delta;

        printf("sensor changed by %+d, value = %d\n", delta, system_value);

        sleep_time = (rand() % 5) + 1;
        sleep(sleep_time);
    }

    return NULL;
}

void *monitor_thread(void *arg)
{
    int consecutive_alerts;

    (void)arg;
    consecutive_alerts = 0;

    while (1)
    {
        printf("monitor reads value = %d\n", system_value);

        if (system_value > 35)
        {
            printf("WARNING: OVERHEATING DETECTED\n");
            consecutive_alerts++;
        }
        else if (system_value < 0)
        {
            printf("ALERT: FREEZING HAZARD\n");
            consecutive_alerts++;
        }
        else
        {
            consecutive_alerts = 0;
        }

        if (consecutive_alerts >= 3)
        {
            printf("CRITICAL SYSTEM FAILURE: CONTINUOUS ALERT STATE\n");
        }

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
