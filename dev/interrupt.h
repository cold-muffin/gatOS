#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

extern volatile uint32_t interrupt_count;

void interrupts_init(void);

#endif