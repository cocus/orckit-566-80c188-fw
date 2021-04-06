# Based off SYS86 project (https://github.com/mfld-fr/sys86)
# Global Makefile

CC = ia16-elf-gcc
# ES only for segment please!
CFLAGS = -Os -ffreestanding -mcmodel=tiny -mprotected-mode -mtune=i80186 -march=i80186

AS = ia16-elf-as

LD = ia16-elf-ld
LDFLAGS = -nostdlib -T raw.ld

EXE = _a.bin

OBJS= \
	entry.o \
	arch.o \
	main.o \
	80c18x.o \
	sd_elm.o \
	sd_asm.o \
	pff.o \
	udivsi3.o \
	divsi3.o \
	ia16-ldivmodu.o \
	ia16-ldivmods.o
	# end of list

.PHONY : all clean

all: $(EXE).hex

$(EXE).hex: $(EXE)
	@echo "== BIN->HEX $< -> $(@)"
	@srec_cat $< -Binary -offset 0 -Output $@ -Intel

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) -M -o $(EXE) $(OBJS) > $(EXE).map

clean:
	rm -f $(EXE) $(OBJS) $(EXE).map
