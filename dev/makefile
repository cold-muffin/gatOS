run: image
	tmux kill-session -t gatos 2>/dev/null || true
	tmux new-session -d -s gatos "qemu-system-i386 -cdrom '$PWD/gatOS.iso' -display curses"
	tmux attach-session -t gatos
	tmux kill-session -t gatos 2>/dev/null || true
setup:
	set -e
	#tell grub where do do stuff from
	export PATH="$HOME/opt/cross/bin:$PATH"
	echo "Building gatOS..."
compile: setup
	rm -f *.o
	#build grub bootloader
	i686-elf-as boot.s -o boot.o
	# Compile every C file in this directory
	for file in *.c; do
	    i686-elf-gcc -c "$file" -o "${file%.c}.o" \
	        -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	done
link: compile
	#link boot and kernel. Can add more C files here later
	i686-elf-gcc -T linker.ld -o gatOS \
	    -ffreestanding -O2 -nostdlib *.o -lgcc
	#make sure gatOS works with grub multiboot
	if ! grub-file --is-x86-multiboot gatOS; then
	    echo "ERROR: gatOS is not Multiboot!"
	    exit 1 #error
	fi
image: link
	mkdir -p isodir/boot/grub
	cp gatOS isodir/boot/gatOS
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o gatOS.iso isodir >/dev/null 2>&1
clean:
	rm -f *.o

