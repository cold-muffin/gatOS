export PATH := $(HOME)/opt/cross/bin:$(PATH)

.PHONY: run compile link image clean

run: image
	qemu-system-i386 -cdrom gatOS.iso -display gtk
link: boot.o cat.o graphics.o interpreter.o interrupt_asm.o interrupt.o io.o kernel.o keysnmouse.o vga.o
	i686-elf-gcc -T linker.ld -o gatOS \
		-ffreestanding -O2 -nostdlib *.o -lgcc
	@if ! grub-file --is-x86-multiboot gatOS; then \
		echo "ERROR: gatOS is not Multiboot!"; \
		exit 1; \
	fi

image: link
	mkdir -p isodir/boot/grub
	cp gatOS isodir/boot/gatOS
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o gatOS.iso isodir >/dev/null 2>&1

clean:
	rm -f *.o gatOS gatOS.iso



boot.o: boot.s
	i686-elf-as boot.s -o boot.o
interrupt_asm.o: interrupt.s
	i686-elf-as interrupt.s -o interrupt_asm.o
io.o: io.s
	i686-elf-as io.s -o io.o

graphics.o: graphics.c
	i686-elf-gcc -c grahpics.c -o grahpics.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
cat.o: cat.c
	i686-elf-gcc -c cat.c -o cat.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
interpreter.o: interpreter.c
	i686-elf-gcc -c interpreter.c -o interpreter.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
interrupt.o: interrupt.c
	i686-elf-gcc -c interrupt.c -o interrupt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
kernel.o: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
keysnmouse.o: keysnmouse.c
	i686-elf-gcc -c keysnmouse.c -o keysnmouse.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
vga.o: vga.c
	i686-elf-gcc -c vga.c -o vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

