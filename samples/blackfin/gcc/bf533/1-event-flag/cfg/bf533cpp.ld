

OUTPUT_FORMAT("elf32-bfin", "elf32-bfin", "elf32-bfin")
OUTPUT_ARCH(bfin)
ENTRY(__start)

              
MEMORY
{
    MEM_L1_CODE    : ORIGIN = 0xFFA00000, LENGTH = 64K + 16K  /* L1 code + cache */
    MEM_L1_SCRATCH : ORIGIN = 0xFFB00000, LENGTH = 4K
    MEM_L1_DATA_B  : ORIGIN = 0xFF900000, LENGTH = 32K - 256  /* 256 bytes reserved for stack */
    MEM_L1_DATA_A  : ORIGIN = 0xFF800000, LENGTH = 32K - 16   /* 0xFF807FEF-0xFF807FFF used by boot-loader for 0.3 and later sil */
    MEM_STACK      : ORIGIN = 0xff907f00, LENGTH = 256        /* Stack - 256; Located in L1 Data B bank */

    /* External Memory Spaces */
    MEM_ASYNC3     : ORIGIN = 0x20300000, LENGTH = 1M         /* Async Bank 3 - 1MB */
    MEM_ASYNC2     : ORIGIN = 0x20200000, LENGTH = 1M         /* Async Bank 2 - 1MB */
    MEM_ASYNC1     : ORIGIN = 0x20100000, LENGTH = 1M         /* Async Bank 1 - 1MB */
    MEM_ASYNC0     : ORIGIN = 0x20000000, LENGTH = 1M         /* Async Bank 0 - 1MB */
    MEM_SDRAM0     : ORIGIN = 0x00000000, LENGTH = 16M * 2    /* SDRAM Bank 0 - 16M 16-bit words */
}


SECTIONS
{    
    /*.startup :
    {
        . = ALIGN(4);
        KEEP ( *(.startup*) )
    } >MEM_L1_CODE*/
       
    .text :
    {   
        /* Startup code */
        . = ALIGN(4);
        KEEP ( *crt*.o( .text .text.* ) )

        /* Code  */

        *(.text .text.* .l1.text .l1.text.*)
        
        KEEP (*(.text.*personality*))
        /* .gnu.warning sections are handled specially by elf32.em.  */
        *(.gnu.warning)
    } >MEM_L1_CODE 
    
    .init :
    {
        KEEP (*(.init))
    } >MEM_L1_CODE
    
    .fini :
    {
        KEEP (*(.fini))
    } >MEM_L1_CODE
    
    .rodata : 
    { 
        *(.rodata .rodata.*) 
    } >MEM_L1_DATA_A
    
    .bss :
    {
        . = ALIGN(4);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    } >MEM_L1_DATA_A
    
    .data :
    {
        /* Dynamic initialization table (class object constructors addresses) */
        . = ALIGN(4);
        ___init_array_start = .;
        *(.ctors)
        ___init_array_end = .;
        KEEP(SORT(*)(.ctors))        

        . = ALIGN(4);
        *(.data .data.* .l1.data .l1.data.*)
        KEEP (*(.*personality*))
    } >MEM_L1_DATA_B
    
    
    . = ALIGN(32 / 8);
    . = ALIGN(32 / 8);
    
    __end = .; PROVIDE (_end = .);
    __stack_start = ORIGIN(MEM_STACK);
    __stack_end   = ORIGIN(MEM_STACK) + LENGTH(MEM_STACK);
    
    
    .sdram :
    {
        KEEP( *(.sdram *sdram.*) )

    } >MEM_SDRAM0


    /DISCARD/ : { *(.note.GNU-stack) }
}
                                                                                          
                                                               




