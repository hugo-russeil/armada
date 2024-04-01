#!/bin/bash

# Call make, to make sure to be packing the latest version
make

# Create directories for Linux and Windows packages
mkdir -p linux_package
mkdir -p windows_package

# Copy the needed files to the directories
cp main.out linux_package/
cp main.exe windows_package/
cp -r assets linux_package/
cp -r assets windows_package/

# Compress the directories into .zip files
zip -r linux_package.zip linux_package/
zip -r windows_package.zip windows_package/

# Remove the uncompressed directories
rm -rf linux_package/
rm -rf windows_package/

echo "Packaging complete !"
