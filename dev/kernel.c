#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <vga.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


void kernel_main(void) 
{
    vga_set_mode_12h();
    vga_prepare_pixels();

    vga_clear(0);

    vga_set_pixel(15, 100, 100);
    vga_set_pixel(15, 101, 100);
    vga_set_pixel(15, 102, 100);
}
