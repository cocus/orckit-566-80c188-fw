#pragma once

#include <stdint.h>

void dly_us(uint16_t us);
void dly_ms(uint16_t ms);

#define cin_stat() inb(S0STS)
#define cin_kbhit() (cin_stat() & 0x40)
#define cin_buf() inb(R0BUF)

void cout(uint8_t c);
void print_bin(uint8_t bin);
void serial_hexdump(uint8_t *addr, uint16_t cnt);
void serial_hexnum32(uint32_t n);
void serial_hexnum16(uint16_t n);
void serial_hexnum8(uint8_t n);
void serial_hexnum4(uint8_t n);
void serial_itoa(int n);
void puts(char * str);
void crlf(void);
