#!/bin/bash

# Run clang-tidy on the source files to check for errors, code smells, etc. Sends the output to a log file.
clang-tidy -checks=-modernize-*,cppcoreguidelines-* -header-filter=src/.* src/*.cpp -- -Iinclude > clang-tidy.log

# Call make, to make sure to get the latest version of the program
make

# Create directories for Linux and Windows packages
mkdir -p linux_package
mkdir -p windows_package

# Copy the needed files to the directories
cp main.out linux_package/main # Copy the linux executable without the .out extension, which is only needed for gitingore
cp main.exe windows_package/
cp -r assets linux_package/
cp -r assets windows_package/

# Compress the directories into .zip files
zip -r linux_package.zip linux_package/
zip -r windows_package.zip windows_package/

# Remove the uncompressed directories
rm -rf linux_package/
rm -rf windows_package/

# The packages are ready
echo "Packaging complete !"
