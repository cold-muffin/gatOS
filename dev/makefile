export PATH := $(HOME)/opt/cross/bin:$(PATH)

.PHONY: run compile link image clean

run: image
	qemu-system-i386 -cdrom gatOS.iso -display gtk
compile:
	@set -e; \
	rm -f *.o; \
	i686-elf-as boot.s -o boot.o; \
	for file in *.c; do \
		i686-elf-gcc -c "$$file" -o "$${file%.c}.o" \
			-std=gnu99 -ffreestanding -O2 -Wall -Wextra; \
	done; \
	for file in *.s; do \
		[ "$$file" = "boot.s" ] && continue; \
		i686-elf-as "$$file" -o "$${file%.s}.o"; \
	done

link: compile
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
