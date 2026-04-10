// pl4_ex1_gpio_output.c
// Raspberry Pi 4 - user space GPIO output
// gcc -O2 -Wall -o pl4_ex1_gpio_output pl4_ex1_gpio_output.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define PERIPHERAL_BASE 0xFE000000UL
#define GPIO_OFFSET     0x00200000UL
#define GPIO_BASE_PHYS  (PERIPHERAL_BASE + GPIO_OFFSET)
#define BLOCK_SIZE      4096

typedef struct {
    volatile uint32_t GPFSEL[6];
    volatile uint32_t RESERVED0;
    volatile uint32_t GPSET[2];
    volatile uint32_t RESERVED1;
    volatile uint32_t GPCLR[2];
    volatile uint32_t RESERVED2;
    volatile uint32_t GPLEV[2];
} bcm2711_gpio_registers_t;

static void gpio_set_output(bcm2711_gpio_registers_t *gpio, int pin) {
    int reg = pin / 10;
    int shift = (pin % 10) * 3;
    uint32_t v = gpio->GPFSEL[reg];
    v &= ~(0x7u << shift);
    v |=  (0x1u << shift);   // 001 = output
    gpio->GPFSEL[reg] = v;
}

static void setGPIOOutputValue(bcm2711_gpio_registers_t *gpio, int pin, int value) {
    int reg = pin / 32;
    int bit = pin % 32;
    if (value)
        gpio->GPSET[reg] = (1u << bit);
    else
        gpio->GPCLR[reg] = (1u << bit);
}

int main(int argc, char **argv) {
    int pin = 18; // podes mudar se quiseres
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    void *map = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE_PHYS);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    bcm2711_gpio_registers_t *gpio = (bcm2711_gpio_registers_t *)map;
    gpio_set_output(gpio, pin);

    while (1) {
        setGPIOOutputValue(gpio, pin, 1);
        sleep(1);
        setGPIOOutputValue(gpio, pin, 0);
        sleep(1);
    }

    munmap(map, BLOCK_SIZE);
    close(fd);
    return 0;
}