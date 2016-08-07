#!/bin/bash

echo -e "\e[31mInstalling requisite yum packages\e[0m"

yum -y install openssh-clients openssh-server libusb1-devel mysql-devel \
    python-devel libpng-devel qt-devel PyQt4 tkinter cmake lapack blas \
    libsodium-devel libXpm-devel devtoolset-2-gcc devtoolset-2-gcc-c++ \
    fftw-devel unixODBC

if [ "$(grep '/opt/rh/devtoolset-2/root/usr/bin' ~/.bashrc)" ]; then
    echo -e "\e[31mdevtoolset already in PATH\e[0m"
else
    echo -e "\e[31mAdding devtoolset to PATH\e[0m"
    echo -e "\nexport PATH=/opt/rh/devtoolset-2/root/usr/bin:\$PATH\n" >> ~/.bashrc
fi