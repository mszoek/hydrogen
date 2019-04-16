OUTPUT_FORMAT("elf64-x86-64")
ENTRY(start)

phys = 0x100000;
base = 0x7C00000000;

SECTIONS
{
	. = phys;

	.header :
	{
		KEEP(*(.header))
	}

	.inittext :
	{
		*(.multiboot)
		*(.inittext)
	}

	. += base;
	.text : AT(ADDR(.text) - base)
	{
		code = .;
		*(.text)
		. = ALIGN(4096);
	}

	.data : AT(ADDR(.data) - base)
	{
		data = .;
		*(.data)
		. = ALIGN(4096);
		dataend = .;
	}

	.rodata : AT(ADDR(.rodata) - base)
	{
		*(.rodata)
	}

	.bss : AT(ADDR(.bss) - base)
	{
		bss = .;
		*(.bss)
		*(COMMON)
		. = ALIGN(4096);
	}
	end = .;

	/DISCARD/ :
	{
		*(.comment)
	}
}
