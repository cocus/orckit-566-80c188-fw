// SYS86 project
// Miscellaneous architecture specifics

#pragma once

#include <stdint.h>

#ifndef _ASSEMBLY

void halt (void);

uint8_t inb (uint16_t p);
void outb (uint16_t p, uint8_t w);

uint16_t inw (uint16_t p);
void outw (uint16_t p, uint16_t w);

#endif // !_ASSEMBLY
