ENTRY(_start) /* start.S中自定义的entry为入口点 */

SECTIONS {
	/**
	* _pmem_start and _entry_offset are defined in LDFLAGS
	* --defsym=_pmem_start=0x80000000 --defsym=_entry_offset=0x0
	* "." 是地址计数器, 用于表示当前的地址, 可以被赋值和修改
	× ". = 0x80000000" 表示当前地址修改为 0x80000000, 后面的节 ".text" 从地址 0x80000000 开始装入
	× 如果 SECTION 命令一开始不指定当前地址 ".", 则按照 0 地址开始
	**/
	. = _pmem_start + _entry_offset;
	/* 定义输出节 ".text", 它由输入节构成, 即后面的{}内部的节构成 */
	.text : {
		*(entry)		/* start.S中自定义的entry节 */
		*(.text*)		/* 其它所有目标文件的.text节 */
	}

	/* etext, edata, end - end of program segments */

	/* the first address past the end of the text segment (the program code) */
	etext = .; 
	_etext = .;

	.rodata : {
		*(.rodata*)
	}
	.data : {
		*(.data)
	}
	/* the first address past the end of the initialized data segment */
	edata = .;
	_data = .;
	
	.bss : {
	_bss_start = .;
		*(.bss*)
		*(.sbss*)
		*(.scommon)
	}
	_stack_top = ALIGN(0x1000);
	. = _stack_top + 0x8000;
	_stack_pointer = .;
	/* the first address past the end of the uninitialized data segment (also known as the BSS segment) */
	end = .;
	_end = .;
	
	_heap_start = ALIGN(0x1000);
}
