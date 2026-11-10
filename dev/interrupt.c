#include <stdint.h>
//cpu format
typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t offset_high;
} __attribute__((packed)) IDTEntry;
//packed means no adding crap by the compiler

static IDTEntry idt[256];

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) IDTPointer;

static IDTPointer idt_pointer;

static void idt_set_gate(uint8_t vector, uint32_t address, uint16_t selector, uint8_t attributes) {
    idt[vector].offset_low = address & 0xFFFF;
    idt[vector].offset_high = (address >> 16) & 0xFFFF;

    idt[vector].selector = selector;
    idt[vector].reserved = 0;
    idt[vector].attributes = attributes;
}
/*
idt_set_gate(
    48,
    handler_address,
    code_segment,
    0x8E  //1000 1110 : privelege kernel 32 bit interrupt gate present
);
*/
extern void interrupt_test_stub(void);
volatile uint32_t interrupt_count = 0;

void interrupt_test_handler(void) {
    interrupt_count++;
}

void interrupts_innit(void) {
    //disable hardware interrupts in setup
    __asm__ volatile ("cli");
    //configure IDT ptr
    idt_pointer.limit = sizeof(idt)-1;
    idt_pointer.base = (uint32_t)idt;
    //read current segment
    
}


