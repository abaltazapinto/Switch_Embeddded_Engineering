#include <stdio.h>
#include <stdint.h>
#include <time.h>

uint64_t get_system_time(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (uint64_t)ts.tv_sec * 1000ULL + (uint64_t)ts.tv_nsec / 1000000ULL;
}

#define T1_PERIOD 10
#define T2_PERIOD 100

int main(void)
{
    uint64_t current_time;
    uint64_t t1;
    uint64_t t2;

    current_time = get_system_time();
    t1 = current_time;
    t2 = current_time;

    while (1) {
        current_time = get_system_time();

        if (current_time - t1 >= T1_PERIOD) {
            printf("servo at time %lu ms\n", current_time);
            t1 = t1 + T1_PERIOD;
        }

        if (current_time - t2 >= T2_PERIOD) {
            printf("display at time %lu ms\n", current_time);
            t2 = t2 + T2_PERIOD;
        }
    }
}
