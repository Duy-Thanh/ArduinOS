# Update MSYS2
pacman -Syu

# Install required packages
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-avr-toolchain
pacman -S make
pacman -S mingw-w64-x86_64-avr-gcc
pacman -S mingw-w64-x86_64-avr-binutils
pacman -S mingw-w64-x86_64-avrdude