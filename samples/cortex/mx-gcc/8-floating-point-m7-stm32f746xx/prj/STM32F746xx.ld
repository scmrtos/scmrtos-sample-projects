/**
 * linker script for STM32F74xxx and STM32F75xxx microcontrollers
 */ 

MEMORY
{
	RAM (xrw)	: ORIGIN = 0x20000000, LENGTH =  320K       /* Main RAM (can be accessed by DMA) */
	FLASH (rx)	: ORIGIN = 0x08000000, LENGTH = 1024K       /* Flash */
	BATTRAM (rw): ORIGIN = 0x40024000, LENGTH =    4K       /* Battery backed RAM */
	CCRAM (rw)	: ORIGIN = 0x10000000, LENGTH =   64K       /* Core coupled RAM (can NOT be accessed by DMA) */
	DTCM (rw)   : ORIGIN = 0x10000000, LENGTH =   64K       /* Data tightly coupled memory */
	ITCM (rw)   : ORIGIN = 0x10000000, LENGTH =   16K       /* Instructions tightly coupled memory (0WS access) */
}

INCLUDE "stm32.ld"
