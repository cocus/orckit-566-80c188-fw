#include "arch.h"
#include <stdint.h>
#include "80c186eb.h"
#include "80c18x.h"

#include "pff.h"
#include "sd_elm.h"

void init_gcs(uint8_t nbr, uint16_t start, uint16_t end)
{
    outw(0xff80 | (nbr << 2), start | 0xf);
    outw((0xff80 | (nbr << 2)) + 2, end | 0x8);
}


void set_leds(uint8_t leds)
{
	outw(0x2002, leds);
}


void die (/* Stop with dying message */
	FRESULT rc	/* FatFs return value */
)
{
	puts("Failed with rc="); serial_hexnum16(rc); puts(".\r\n");
	//for (;;) ;
}

void sd_test(void)
{
	FATFS fatfs;			/* File system object */
	DIR dir;				/* Directory object */
	FILINFO fno;			/* File information object */
	UINT bw, br, i;
	BYTE buff[64];
    FRESULT rc;

	puts("\r\nMount a volume.\r\n");
	rc = pf_mount(&fatfs);
	if (rc) { die(rc); return; }

	puts("\r\nOpen a test file (message.txt).\r\n");
	rc = pf_open("MESSAGE.TXT");
	if (rc) { die(rc); return; }

	puts("\r\nType the file content.\r\n");
	for (;;) {
		rc = pf_read(buff, sizeof(buff), &br);	/* Read a chunk of file */
		if (rc || !br) break;			/* Error or end of file */
		for (i = 0; i < br; i++)		/* Type the data */
			cout(buff[i]);
	}
	if (rc) { die(rc); return; }

#if PF_USE_WRITE
	printf("\r\nOpen a file to write (write.txt).\r\n");
	rc = pf_open("WRITE.TXT");
	if (rc) { die(rc); return; }

	printf("\r\nWrite a text data. (Hello world!)\r\n");
	for (;;) {
		rc = pf_write("Hello world!\r\r\n", 14, &bw);
		if (rc || !bw) break;
	}
	if (rc) { die(rc); return; }

	printf("\r\nTerminate the file write process.\r\n");
	rc = pf_write(0, 0, &bw);
	if (rc) { die(rc); return; }
#endif

#if PF_USE_DIR
	puts("\r\nOpen root directory.\r\n");
	rc = pf_opendir(&dir, "");
	if (rc) { die(rc); return; }

	puts("\r\nDirectory listing...\r\n");
	for (;;) {
		rc = pf_readdir(&dir, &fno);	/* Read a directory item */
		if (rc || !fno.fname[0]) break;	/* Error or end of dir */
		if (fno.fattrib & AM_DIR)
		{
            puts("   <dir>  "); puts(fno.fname); puts("\r\n");
        }
		else
		{
            serial_hexnum32(fno.fsize); puts("  "); puts(fno.fname); puts("\r\n");
        }
	}
	if (rc) { die(rc); return; }
#endif

	puts("\r\nTest completed.\r\n");
	//for (;;) ;
}

int main(void)
{
    uint8_t counter = 0;
    uint8_t rx;
    uint32_t sector = 0;
    uint8_t res;
    uint8_t buff[512];

	init_gcs(6, 0x2000, 0x2040);
	set_leds(counter);

    puts("\r\r\nlolzor!\r\r\n");
    
    cout('H'); cout('e'); cout('y');




    while(1)
    {
		if (cin_kbhit())
		{
			rx = cin_buf(); 
			cout(rx);
			counter--;
			set_leds(counter);

            switch (rx)
            {
                case 'Q':
                case 'q':
                {
                    asm("jmp $0x0F000,$0x0FFF0");
                    break;
                }
				case 'n':
				{
					sector++;
					puts("sector: "); serial_hexnum32(sector); crlf();
					break;
				}
				case 'p':
				{
					sector--;
					puts("sector: "); serial_hexnum32(sector); crlf();
					break;
				}
                case 's':
                {
                    sd_test();
                    break;
                }
				case 'i':
				{
					res = disk_initialize();
					puts("disk_initialize: 0x"); serial_hexnum8(res); crlf();
					break;
				}
				case 'r':
				{
					res = disk_readp(buff, sector, 100, 512-100);
					puts("SD_Read: "); serial_hexnum8(res); crlf();
					if (res == 0)
						serial_hexdump(buff, 512-100);
					break;
				}
                default:
                    break;
            }
        }
    }
}