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

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

//hardware communication

#define VGA_MISC_WRITE 0x3C2;

#define VGA_SEQ_INDEX 0x3C4
#define VGA_SEQ_DATA 0x3C5

#define VGA_CRTC_INDEX 0x3D4
#define VGA_CRTC_DATA 0x3D5

#define VGA_GC_INDEX 0x3CE
#define VGA_GC_DATA 0x3CF

#define VGA_AC_INDEX 0x3C0
#define VGA_INSTAT_READ 0x3DA  

//SEQ = sequencer controls how mem is read
//CRTC controls scan timing and resolution so it acts like a crt
//GC = graphics controller controls plane write
//AC = Attribute contoller maps pixel values to pallete

static const uint8_t mode12_seq[5] =
{   //basic settings for vga
    0x03,      //0x00::00000011 : 000000:sync rst:async rst. ;; both on ;; normal operation
    0x01,      //0x01::character clock 8 dot setting (???)
    0x0F,      //0x02::MASK!!! COLORS 0x02 // all 4 open
    0x00,      //0x03::character map (none)
    0x06       //0x04::00000110 (00000:Chain-4 off(0):odd/even-disable(1):extended-memory(1):0)
};

static const uint8_t mode12_crtc[25] =
{
    0x5F, 0x4F, 0x50, 0x82,
    0x54, 0x80, 0x0B, 0x3E,
    0x00, 0x40, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xEA, 0x8C, 0xDF, 0x28,
    0x00, 0xE7, 0x04, 0xE3,
    0xFF
};

static const uint8_t mode12_gc[9] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x05,
    0x0F,
    0xFF
};

static const uint8_t mode12_ac[21] =
{
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B,
    0x0C, 0x0D, 0x0E, 0x0F,

    0x01,
    0x00,
    0x0F,
    0x00,
    0x00
};
