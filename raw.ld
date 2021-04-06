OUTPUT_FORMAT(binary)

SECTIONS {
	. = 0x0;
	.text : {
		*(.entry.text);
		. = ALIGN(4);
		*(.text);
		*(.text.startup);
		*(.rodata);
		*(.rodata.*);
		*(.data)
	}
	.bss : { *(.bss) *(COMMON) }
	/DISCARD/ : { *(.comment) }
}
