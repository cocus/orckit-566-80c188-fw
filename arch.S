//------------------------------------------------------------------------------
// SYS86 project
// Miscellaneous architecture specifics
//------------------------------------------------------------------------------

	.code16

	.text

//------------------------------------------------------------------------------

// Halt processor and wait for interrupt

	.global halt

halt:

	hlt
	ret

//------------------------------------------------------------------------------

// I/O helpers


	.global inb

inb:

	mov     %sp,%bx
	mov     2(%bx),%dx
	in      %dx,%al
	ret

	.global outb

outb:

	mov     %sp,%bx
	mov     2(%bx),%dx
	mov     4(%bx),%ax
	out     %al,%dx
	ret

	.global inw

inw:

	mov     %sp,%bx
	mov     2(%bx),%dx
	in      %dx,%ax
	ret

	.global outw

outw:

	mov     %sp,%bx
	mov     2(%bx),%dx
	mov     4(%bx),%ax
	out     %ax,%dx
	ret

//------------------------------------------------------------------------------
