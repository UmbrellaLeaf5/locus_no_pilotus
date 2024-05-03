#!/bin/bash

# Create a directory where you want to download it
mkdir -p ~/Downloads/Install_Files/Doxygen
cd ~/Downloads/Install_Files/Doxygen

# download it
wget https://github.com/doxygen/doxygen/releases/download/Release_1_9_7/doxygen-1.9.7.linux.bin.tar.gz

# extract it
tar -xf doxygen-1.9.7.linux.bin.tar.gz

# cd into the extracted directory
# - Note: this directory already has a `bin` dir with prebuilt binary
#   executables. 
cd doxygen-1.9.7

# make and install it
sudo make
sudo make install

# Ensure it's installed
# Example output:
#
#       1.9.7 (ebc57c6dd303a980bd19dd74b8b61c8f3f5180ca)
#
doxygen --version

# Check your man pages available by typing `man doxy` and pressing Tab twice. 
# Output:
#
#       doxygen      doxyindexer  doxysearch   doxywizard  
# 

# View those man pages
man doxygen

# Add doxygen to the PATH
DIR="$HOME/Downloads/Install_Files/Doxygen/doxygen-1.9.7/bin"
if [ -d "$DIR" ]; then
    PATH="$DIR:$PATH"
fi

# Test the new doxygen executables from the `doxygen-1.9.7/bin/` dir
doxygen --version  # should be the same as above