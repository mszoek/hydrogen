/*OUTPUT_FORMAT("binary")*/
ENTRY(start)

SECTIONS
{
    . = 0x600010;
	.text :
	{
		*(.text)
		. = ALIGN(4096);
	}

	.data :
	{
		*(.data)
		. = ALIGN(4096);
	}

	.rodata : 
	{
		*(.rodata)
	}

	.bss :
	{
		*(.bss)
		*(COMMON)
		. = ALIGN(4096);
	}

    .init :
    {
        *(.init)
		*(.init_array)
        . = ALIGN(4096);
    }

    .fini :
    {
        *(.fini)
		*(.fini_array)
        . = ALIGN(4096);
    }

	/DISCARD/ :
	{
		*(.comment)
	}
}
