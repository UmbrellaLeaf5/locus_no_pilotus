#!/bin/bash

# source: https://askubuntu.com/questions/1291874/how-to-install-doxygen-on-ubuntu

# Create a directory where you want to download it
mkdir -p ~/Downloads/Doxygen
cd ~/Downloads/Doxygen

# download it
wget https://github.com/doxygen/doxygen/releases/download/Release_1_10_0/doxygen-1.10.0.linux.bin.tar.gz

# extract it
tar -xf doxygen-1.10.0.linux.bin.tar.gz

# cd into the extracted directory
# - Note: this directory already has a `bin` dir with prebuilt binary
#   executables. 
cd doxygen-1.10.0

# make and install it
sudo make
sudo make install

# Ensure it's installed
# Example output:
#
#       1.10.0 (ebc57c6dd303a980bd19dd74b8b61c8f3f5180ca)
#
doxygen --version

# View those man pages
man doxygen

# Add doxygen to the PATH
DIR="$HOME/Downloads/Doxygen/doxygen-1.10.0/bin"
if [ -d "$DIR" ]; then
    PATH="$DIR:$PATH"
fi

# Test the new doxygen executables from the `doxygen-1.10.0/bin/` dir
doxygen --version  # should be the same as above