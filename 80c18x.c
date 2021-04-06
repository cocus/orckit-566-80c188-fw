#include "80c186eb.h"
#include "80c18x.h"
#include "arch.h"

void cout(uint8_t c)
{
	while((inb(S0STS) & 8) == 0);
	outb(T0BUF, c);
}

void dly_us(uint16_t us)
{
	us >>= 3;
	while(us--)
	{
		asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
	}
}

void dly_ms(uint16_t ms)
{
	while(ms--)
	{
		dly_us(1000);
	}	
}

void crlf(void)
{
	cout('\r'); cout('\n');
}

void puts(char * str)
{
	while(*str)
	{
		cout(*str);
		str++;
	}
}

void serial_itoa(int n)
{
  char i,j;                    //decade counter
  //char idx=0;                  //string index     
  //int const Div[4] = {      //decades table
  //  1000000000L,100000000L,10000000L,1000000L
  //  100000L,10000L,1000L,100L,10L,1};
  int b;                     //i32 to hold table read                           
  char fdd;                     //first digit detect (suppress leading zero function)
 
  fdd=0;                       //clear detection
  if (n & 0x8000) {        //T: n=negative
    n=(~n)+1;                  //convert to positive
    //s[0]='-';                  //mark the negative number
	cout('-');
    //idx++;
  } 
 
  for (i=0; i<5;i++) {        //do all the decades, start with biggest
    j=0;                       //clear the decimal digit counter
	switch (i)
	{
		case 0: b = 10000; break;
		case 1: b = 1000; break;
		case 2: b = 100; break;
		case 3: b = 10; break;
		case 4: b = 1; break;
	}
    while (n>=b) {             //T: "left-over" still bigger then decade; substr. and count
      j++;
      n-=b;
    } 
    if ((j)||(fdd)) {          //T: decade count!=0 or first digit has been detected
      fdd=1;
	  cout('0' + j);
    } 
  }

  if (!fdd) cout('0');
}

void print_bin(uint8_t bin)
{
    uint8_t i;

    for(i = 0x80; i != 0; i >>= 1)
	{
        cout((bin & i)?'1':'0');
	}
	crlf();
}

void serial_hexnum4(uint8_t n)
{
	if (n > 9)
	{
		n = 'A' + (n - 10);
	}
	else
	{
		n = '0' + n;
	}
	cout(n);
}

void serial_hexnum8(uint8_t n)
{
	serial_hexnum4(n >> 4);
	serial_hexnum4(n & 0xf);
}

void serial_hexnum16(uint16_t n)
{
	serial_hexnum8(n >> 8);
	serial_hexnum8(n & 0xff);
}

void serial_hexnum32(uint32_t n)
{
	serial_hexnum16(n >> 16);
	serial_hexnum16(n & 0xffff);
}

void serial_hexdump(uint8_t *addr, uint16_t cnt)
{
	uint16_t i = 0;
	uint8_t chr_idx = 0;
	uint8_t dsp[17];// = { 0 };

	while (cnt--)
	{
		if (i % 16 == 0)
		{
			if (i != 0)
			{
				puts(" |"); puts(dsp); puts("|");
				for (chr_idx = 0; chr_idx < 16; chr_idx++)
				{
					dsp[chr_idx] = '\0';
				}
			}
			crlf();
			serial_hexnum16((uint16_t)addr); cout(':');
		}
		serial_hexnum8(*addr); cout(' ');
		if ((*addr >= 0x20) &&
			(*addr <= 0x70))
		{
			dsp[i%16] = *addr;
		}
		else
		{
			dsp[i%16] = '.';
		}
		addr++;
		i++;
	}
	puts(" |"); puts(dsp); puts("|");


	crlf();
}