#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

// #define PERIPHERAL_BASE 0x3F000000  // Pi 2/3
#define PERIPHERAL_BASE 0xFE000000
#define GPIO_OFFSET     0x200000
#define BLOCK_SIZE      4096

#define pwm_base_offset 0x20C000
#define GPFSEL1 1

volatile uint32_t *gpio;


typedef struct {
 uint32_t GPFSEL[7]; /*!< GPIO Function Select */
 uint32_t GPSET[3]; /*!< GPIO Pin Output Set */
 uint32_t GPCLR[3]; /*!< GPIO Pin Output Clear */
 uint32_t GPLEV[3]; /*!< GPIO Pin Level */
 uint32_t GPEDS[3]; /*!< GPIO Pin Event Detect Status */
 uint32_t GPREN[3]; /*!< GPIO Pin Rising Edge Detect Enable */
 uint32_t GPFEN[3]; /*!< GPIO Pin Falling Edge Detect Enable */
 uint32_t GPHEN[3]; /*!< GPIO Pin High Detect Enable */
 uint32_t GPLEN[3]; /*!< GPIO Pin Low Detect Enable */
 uint32_t GPAREN[3]; /*!< GPIO Pin Async. Rising Edge Detect */
 uint32_t GPAFEN[3]; /*!< GPIO Pin Async. Falling Edge Detect */
 uint32_t GPPUD; /*!< GPIO Pin Pull-up/down Enable */
 uint32_t GPPUDCLK[3]; /*!< GPIO Pin Pull-up/down Enable Clock */
} bcm2837_gpio_registers_t;

typedef struct {
 uint32_t CONTROL;
 uint32_t STATUS;
 uint32_t DMAC[2];
 uint32_t CHN0_RANGE; //maximum value for PWM_CHANNEL0_DATA
 uint32_t CHN0_DATA; //Pulse Width for CHANNEL0 (from 0 to PWM_CHN0_RANGE)
 uint32_t FIF1[2]; // PWM FIFO Input
 uint32_t CHN1_RANGE;
 uint32_t CHN1_DATA;
} bmc2711_pwm_registers_t;

volatile bmc2711_pwm_registers_t *pwm;


int main (){

    int mem_fd;
    void *gpio_map;


     mem_fd = open("/dev/mem", O_RDWR|O_SYNC); //O_SYNC ensures written data is flushed
    if(mem_fd < 0){
        perror("open");
        return -1;
    }

    bcm2837_gpio_registers_t *gpio_regs = mmap(
        NULL,
        BLOCK_SIZE, //Number of bytes to be addressed (e.g., number of 8 bit registers)
        PROT_READ|PROT_WRITE,
        MAP_SHARED,
        mem_fd, // File descriptor to physical memory virtual file '/dev/mem’
        PERIPHERAL_BASE + GPIO_OFFSET // Address in physical map that we want to map and access
    );

    //pwm = (bmc2711_pwm_registers_t *)((char *)gpio_regs + pwm_base_offset);



    close(mem_fd);



    if (gpio_regs == MAP_FAILED) {
        perror("mmap");
        return -1;
    }

    //gpio[GPFSEL1] &= ~(7 << 6);
    //gpio[GPFSEL1] |=  (4 << 6);

        // RANGE = 255
    //pwm->CHN0_RANGE = 255;

    // enable PWM (PWM channel 0 + PWM mode)
    //pwm->CONTROL = (1 << 0);   // PWEN0


    int pin = 18;
    //int pos = (pin % 10) * 3;

    int fsel_reg = pin / 10;
    int fsel_shift = (pin % 10) * 3;

    gpio_regs->GPFSEL[fsel_reg] &= ~(7 << fsel_shift); // clear bits

    gpio_regs->GPFSEL[fsel_reg] |=  (1 << fsel_shift); // set as output (001)

    // blink
    while (1) {
        gpio_regs->GPSET[pin / 32] = (1 << (pin % 32));
        sleep(1);
        gpio_regs->GPCLR[pin/32] = (1 << (pin % 32));
        sleep(1);

        /*for (int i = 0; i <= 255; i++) {
            pwm->CHN0_RANGE = i;
            usleep(2000);
        }*/

    }

    //gpio_regs->GPSET[pin / 32] = (1 << (pin % 32));

    //sleep(1);



    if (munmap((void *)gpio_regs, BLOCK_SIZE) < 0) {
        perror("munmap");
        return -1;
    }


    return 0;
}