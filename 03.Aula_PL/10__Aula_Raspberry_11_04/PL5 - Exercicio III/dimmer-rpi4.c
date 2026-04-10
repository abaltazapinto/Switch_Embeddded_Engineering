// dimmer-rpi4.c

#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include "gpio.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Software PWM on GPIO12");

static struct hrtimer pwm_timer;
static int new_period = 1;
static int duty_cycle = 50;

module_param(duty_cycle, int, 0666);
MODULE_PARM_DESC(duty_cycle, "Duty cycle 0..100");

static enum hrtimer_restart pwm_cb(struct hrtimer *t)
{
    ktime_t interval;

    if (duty_cycle < 0) duty_cycle = 0;
    if (duty_cycle > 100) duty_cycle = 100;

    if (new_period) {
        if (duty_cycle > 0) {
            gpio12_set(1);
            interval = ktime_set(0, (u64)duty_cycle * 1000000ULL / 100ULL);

            if (duty_cycle < 100)
                new_period = 0;
            else
                interval = ktime_set(0, 1000000); // 1 ms high
        } else {
            gpio12_set(0);
            interval = ktime_set(0, 1000000); // 1 ms full low
        }
    } else {
        gpio12_set(0);
        interval = ktime_set(0, (u64)(100 - duty_cycle) * 1000000ULL / 100ULL);
        new_period = 1;
    }

    hrtimer_forward_now(&pwm_timer, interval);
    return HRTIMER_RESTART;
}

static int __init dimmer_init(void)
{
    int ret = gpio12_init_output();
    if (ret)
        return ret;

    new_period = 1;
    hrtimer_init(&pwm_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    pwm_timer.function = pwm_cb;
    hrtimer_start(&pwm_timer, ktime_set(0, 1000000), HRTIMER_MODE_REL); // 1 ms

    return 0;
}

static void __exit dimmer_exit(void)
{
    hrtimer_cancel(&pwm_timer);
    gpio12_set(0);
    gpio12_cleanup();
}

module_init(dimmer_init);
module_exit(dimmer_exit);