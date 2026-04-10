make
scp dimmer-rpi4.ko pi@IP_DO_PI:/home/pi/
ssh pi@IP_DO_PI
sudo insmod dimmer-rpi4.ko duty_cycle=25
sudo rmmod dimmer_rpi4