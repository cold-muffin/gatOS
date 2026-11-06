#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "graphics.h"
#include "cat.h"

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

void kernel_main(void) 
{
    vga_set_mode_12h();
    vga_prepare_pixels();
    vga_clear(0);
    graphics_draw_text("GATOS IS MUY BIEN\n\nNECESITAMOS INVESTOROS\n EFRAT es el Goatos!!!", 200,50,20,RED);
        
    for (int i = 0; i < 500; i++) {
        
    
        vga_set_pixel(15, 100, 100);
        vga_set_pixel(15, 101, 100);
        vga_set_pixel(15, 102, 100);
        

        draw_cat(i,300,70,MAGENTA);
        //delay_loops(100);
        draw_cat(i,300,70, BLACK);
    }
}

