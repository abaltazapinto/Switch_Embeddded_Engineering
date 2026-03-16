
// ver o tamanho dos bits
ls -l build
avr-size build/main.elf

lsusb 

rular o programa 

    avr-objsump -d build/main.elf | less

make clean
make
