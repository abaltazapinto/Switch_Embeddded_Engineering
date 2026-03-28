
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define ADDRESS_RANGE 4096

#define RP_14_PERIPH_BASE 0xFE000000
#define RP_14_GPIO_BASE (RP14_PERIPH_BASE + 0x200000)

typedef struct {
	uint32_t reg0; // offset 0x00
	uint32_t reg1; // offset 0x04
	uint32_t reg2; // offset 0x08
} gpio_t

int main(void)
{
	int mem_fd;
	volatile gpio_t *gpio;

	mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
	gpio = mmap(
		NULL,
		ADDRESS_RANGE,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		mem_fd,
		RPI4_GPIO_BASE
	);
	return 0;
}
