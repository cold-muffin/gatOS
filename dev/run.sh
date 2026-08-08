#!/bin/bash

#this builds 

set -e
#tell grub where do do stuff from
export PATH="$HOME/opt/cross/bin:$PATH"

echo "Building gatOS..."

rm -f *.o

#build grub bootloader
i686-elf-as boot.s -o boot.o
i686-elf-as vga_io.s -o vga_io.o

# Compile every C file in this directory

for file in *.c; do
    echo "Compiling $file"
    i686-elf-gcc -c "$file" -o "${file%.c}.o" \
        -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wno-error=implicit-function-declaration
done

#link boot and kernel. Can add more C files here later
i686-elf-gcc -T linker.ld -o gatOS \
    -ffreestanding -O2 -nostdlib *.o -lgcc
#make sure gatOS works with grub multiboot
if ! grub-file --is-x86-multiboot gatOS; then
    echo "ERROR: myos is not Multiboot!"
    exit 1 #error
fi

#where the .iso is
#the os is named myos as in the bare bones tutorial
mkdir -p isodir/boot/grub
cp gatOS isodir/boot/gatOS
cp grub.cfg isodir/boot/grub/grub.cfg
#
grub-mkrescue -o gatOS.iso isodir >/dev/null 2>&1


#print stuff
echo "Build successful."
echo
echo "Starting gatOS..."
echo "To quit: press Ctrl+B, release them, then press D"
echo


#use tmux to escape easily

tmux kill-session -t gatos 2>/dev/null || true

tmux new-session -d -s gatos \
    "qemu-system-i386 -cdrom '$PWD/gatOS.iso' -display curses"

tmux attach-session -t gatos

tmux kill-session -t gatos 2>/dev/null || true

echo "QEMU closed."

rm -f *.o
