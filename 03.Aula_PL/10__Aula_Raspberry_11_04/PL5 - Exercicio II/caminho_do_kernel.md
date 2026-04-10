wget http://archive.raspberrypi.com/debian/pool/main/l/linux/linux-source-6.12_6.12.75-1+rpt1_all.deb
dpkg-deb --extract linux-source-6.12_6.12.75-1+rpt1_all.deb /tmp/linux-source
tar xvf /tmp/linux-source/usr/src/linux-source-6.12.tar.xz
rm -rf /tmp/linux-source
cd linux-source-6.12
KERNEL=kernel8
MYCC=/home/USERNAME/arm-gnu-toolchain-15.2.rel1-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
make ARCH=arm64 CROSS_COMPILE=$MYCC bcm2711_defconfig
make ARCH=arm64 CROSS_COMPILE=$MYCC modules_prepare