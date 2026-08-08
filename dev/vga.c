#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};


#define VGA_WIDTH   640
#define VGA_WIDTH_B 80
#define VGA_HEIGHT  480
#define VGA_MEMORY  0xA0000 
#define VGA_COLOR   0x02    
/*
VGA_WIDTH_B is /8
pixel: 0xA0000-0xAFFFF, text: 0xB8000-0xBFFFF
0x02 is the layer set
*/


size_t vga_row;
size_t vga_column;
volatile uint8_t* vga_buffer = (volatile uint8_t*)VGA_MEMORY;
volatile uint8_t* vga_color  = (volatile uint8_t*)VGA_COLOR; //just index at 0

//DISPLAY DRIVERR
void vga_reset(uint8_t bg_color) 
{
	vga_row = 0;
	vga_column = 0;
	vga_color[0] = bg_color;
	
    //set constant color
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH_B; x++) { //width /8
			const size_t index = y * VGA_WIDTH_B + x;
			vga_buffer[index] = 0xFF; //
		}
	}
}
//==========================================================================================here
void vga_set_pixel_byte(size_t index, uint8_t color) 
{
    //set bit to zero in all channels
    VGA_COLOR[0] = 15;
    const uint8_t bit = index & 0x7;
    vga_buffer[index >> 3] = vga_buffer[index >> 3] & ~(1 << bit);
    
    
    VGA_COLOR[0] = color;
    vga_buffer[index >> 3] = vga_buffer[index >> 3] + (1 << bit);
    
}

void vga_set_pixel(uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	vga_set_pixrl_byte(index, color);
}
    