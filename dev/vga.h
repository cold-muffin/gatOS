#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>

void vga_set_mode_12h(void);
void vga_prepare_pixels(void);
void vga_clear(uint8_t color);
void vga_set_pixel(uint8_t color, size_t x, size_t y);

#endif