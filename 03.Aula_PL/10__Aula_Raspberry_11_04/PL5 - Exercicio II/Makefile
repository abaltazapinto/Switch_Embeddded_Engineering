obj-m += blinker-rpi4.o
blinker-rpi4-objs := blinker.o gpio.o

KERNEL_DIR = ../linux-source-6.12
CCC_ARGS = ARCH=arm64 CROSS_COMPILE=/home/USERNAME/arm-gnu-toolchain-15.2.rel1-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-

all:
	make -C ${KERNEL_DIR} M=$(PWD) modules $(CCC_ARGS)

clean:
	make -C ${KERNEL_DIR} M=$(PWD) clean