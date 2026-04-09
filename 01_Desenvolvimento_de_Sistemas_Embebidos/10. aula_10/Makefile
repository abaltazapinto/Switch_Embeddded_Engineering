obj-m +=blinker.o
KERNEL_DIR=/lib/modules/$(shell uname -r)/build
#KERNEL_DIR=../linux

all:
	make -C ${KERNEL_DIR} M=$(PWD) modules
clean:
	make -C ${KERNEL_DIR} M=$(PWD) clean






