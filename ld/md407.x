/*
	Default linker script for MD407 (STM32F407)
	All code and data goes to RAM.
*/

MEMORY
{
  RAM (xrw) : 
  ORIGIN = 0x20000000, LENGTH = 108K
}

SECTIONS
{
 .text :
 {
  . = ALIGN(4);
  *(.start_section)	
  *(.text) 			
  *(.text.*)                 
  *(.data)
  *(.data.*)
  *(.rodata)
  *(.rodata.*)
  . = ALIGN(4);	    
   __bss_start__ = .; 
  *(.bss)	
  *(COMMON)
  . = ALIGN(4);
   __bss_end__ = .; 
  . = ALIGN(4096); 
  heap_low = .; 
  . = . + 0x800; 
  heap_top = .; 
  . = . + 0x800; 
  stack_top = .;  
 } >RAM
}