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


#define VGA_WIDTH   640
#define VGA_HEIGHT  480
#define VGA_BYTES_PER_ROW 80

#define VGA_MEMORY ((volatile uint8_t *)0xA0000)

static const uint8_t mode12_seq[5] =
{   //basic settings for vga
    0x03,      //0x00::00000011 : 000000:sync rst:async rst. ;; both on ;; normal operation
    0x01,      //0x01::character clock 8 dot setting (???)
    0x0F,      //0x02::MASK!!! COLORS 0x02 // all 4 open
    0x00,      //0x03::character map (none)
    0x06       //0x04::00000110 (00000:Chain-4 off(0):odd/even-disable(1):extended-memory(1):0)
};

static const uint8_t mode12_crtc[25] =
{//a crt works like a tracer and these are basically settings for controlling that. Chatgpt explained this: https://chatgpt.com/s/t_6a77c33e37b081919ccd4f13639a9e3b
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

//WRITERS/READERS:
static void vga_seq_write(uint8_t reg, uint8_t value)
{
    outb(0x3C4, reg);
    outb(0x3C5, value);
}

static uint8_t vga_seq_read(uint8_t reg)
{
    outb(0x3C4, reg);
    return inb(0x3C5);
}

static void vga_gc_write(uint8_t reg, uint8_t value)
{
    outb(0x3CE, reg);
    outb(0x3CF, value);
}

static uint8_t vga_gc_read(uint8_t reg)
{
    outb(0x3CE, reg);
    return inb(0x3CF);
}

static void vga_crtc_write(uint8_t reg, uint8_t value)
{
    outb(0x3D4, reg);
    outb(0x3D5, value);
}

//Attribute controller flip flop handling::
static void vga_ac_write(uint8_t reg, uint8_t value) 
{
    //reset (output to nothing)
    (void)inb(0x3DA);
    //set reg num
    outb(0x3C0, reg);
    //value
    outb(0x3C0, value);
    
}

//initialization:::
void vga_set_mode_12h() 
{
    //misc out reg
    outb(0x3C2, 0xE3);
    
    //sequencer
    for (uint8_t i = 0; i < 5; i++) {
        vga_seq_write(i, mode12_seq[i]);
    }
    
    //unlock protected regs
    outb(0x3D4, 0x11);
    uint8_t value = inb(0x3D5);
    outb(0x3D5, value & 0x7F);
    //CRTC
    for (uint8_t i = 0; i < 25; i++) {
        vga_crtc_write(i, mode12_crtc[i]);
    }
    //graphics controller
    for (uint8_t i = 0; i < 9; i++) {
        vga_gc_write(i, mode12_gc[i]);
    }
    //attribute controller
    for (uint8_t i = 0; i < 21; i++) {
        vga_ac_write(i, mode12_ac[i]);
    }
    //reset AC flip flop then disp output enable
    (void)inb(0x3DA);
    outb(0x3C0, 0x20);
}
//go from text to graphics mode
void vga_prepare_pixels() 
{
    //allow writes to all planes
    vga_seq_write(0x02, 0x0F);
    
    //get write mode
    uint8_t mode = vga_gc_read(0x05);
    mode &= ~0x03; //mask all but last 2 bits
    mode |= 0x02; //set last 2 bits to 10 (write mode 2)
    vga_gc_write(0x05, mode);
    
    //graphics ctl no replace operation; allow all 8 px in each byte
    vga_gc_write(0x03, 0x00);
    vga_gc_write(0x08, 0xFF);
}
void vga_set_pixel(uint8_t color, size_t x, size_t y) 
{
    if (x >= VGA_WIDTH || y >= VGA_HEIGHT) {return;}
    
    size_t offset = y * VGA_BYTES_PER_ROW + (x >> 3);
    
    //VGA px order is reversed. bit 7 is x%8=0
    uint8_t mask = 0x80 >> (x & 7); // 0x10000000 >> x%8
    
    //modify this pixel and no other pixel
    vga_gc_write(0x08, mask);
    
    volatile uint8_t dummy = VGA_MEMORY[offset];
    (void)dummy;
    
    VGA_MEMORY[offset] = color & 0x0F;
}
//simmilarly, clear does this but says modify every pixel.
void vga_clear(uint8_t color) 
{
    //allow all 8 to change
    vga_gc_write(0x08, 0xFF);
    for (size_t i = 0; i < VGA_BYTES_PER_ROW * VGA_HEIGHT; i++) {
        VGA_MEMORY[i] = color & 0x0F;
    }
}