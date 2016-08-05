#!/bin/bash

echo -e "\e[31mInstalling requisite external packages\e[0m"

# Install boost.
if [ -d ~/Packages/boost ]; then
    echo -e "\e[31mBoost is already installed.\e[0m"
else
    echo -e "\e[31mInstalling boost.\e[0m"
    cd ~/Packages
    git clone --recursive https://github.com/boostorg/boost

    cd boost
    ./bootstrap.sh
    ./b2 install
fi