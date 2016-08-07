#!/bin/bash

# Grab a handle for the install directory.
INSTALL_DIR="$(dirname $(readlink -f $0))/install.d"
cd $INSTALL_DIR

for script in `ls [0-4]?-*.sh`
do
    sudo ./$script
    cd $INSTALL_DIR
done

for script in `ls [5-9]?-*.sh`
do
    . $script
    cd $INSTALL_DIR
done

# Source the changes.
. ~/.bashrc

# Move back into the script directory.
cd ..

unset INSTALL_DIR