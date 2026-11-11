#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "graphics.h"
#include "cat.h"
#include "interrupt.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

typedef enum {
    BLACK         = 0x0,
    BLUE          = 0x1,
    GREEN         = 0x2,
    CYAN          = 0x3,
    RED           = 0x4,
    MAGENTA       = 0x5,
    BROWN         = 0x6,
    LIGHT_GRAY    = 0x7,
    DARK_GRAY     = 0x8,
    LIGHT_BLUE    = 0x9,
    LIGHT_GREEN   = 0xA,
    LIGHT_CYAN    = 0xB,
    LIGHT_RED     = 0xC,
    LIGHT_MAGENTA = 0xD,
    YELLOW        = 0xE,
    WHITE         = 0xF
} VGAColor;
void delay_loops(volatile unsigned long count) {
    while (count > 0) {
        count--;
    }
}

void kernel_main() 
{
    vga_set_mode_12h();
    vga_prepare_pixels();
    vga_clear(0);
    graphics_draw_text("GATOS IS MUY BIEN\n\nNECESITAMOS INVESTOROS\n EFRAT es el Goatos!!!", 200,50,30,RED);
    
    interrupts_init();

    uint32_t before = interrupt_count;

    __asm__ volatile ("int $0x30");

    if (interrupt_count == before + 1) {
        graphics_draw_text("yay", 300,300,30,GREEN);
    } else {
        graphics_draw_text("nay", 300,300,30,RED);
    }
}
