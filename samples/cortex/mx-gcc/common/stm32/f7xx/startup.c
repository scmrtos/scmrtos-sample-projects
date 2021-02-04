/**
*  @file startup.c
*
*  Startup file for STM32F746xx devices
*
*  Copyright © 2017 Anton B. Gusev aka AHTOXA
**/

#include <string.h>
#include "stm32f746xx.h"

extern unsigned char __idata_start[];
extern unsigned char __data_start[];
extern unsigned char __data_end[];
extern unsigned char __bss_start[];
extern unsigned char __bss_end[];

__attribute__ ((weak))
int  __low_level_init();
void __libc_init_array();
int main();


// PLL_VCO = (HS{E,I}_VALUE / PLL_M) * PLL_N
#define PLL_M      25
#define PLL_N      432			// VCO output clock = 432 MHz (1 MHz * 432)

// SYSCLK = PLL_VCO / PLL_P
#define PLL_P      2

// USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ
#define PLL_Q      9

static inline void InitClocks()
{
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY)) ;

	// Enable high performance mode, System frequency up to 216 MHz
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
//	PWR->CR1 |= PWR_CR1_VOS;     // voltage output Scale 1 mode


	RCC->CFGR |= 0
			| RCC_CFGR_HPRE_DIV1   // HCLK = SYSCLK. (Maximum frequency of the AHB domain is 168MHz.)
			| RCC_CFGR_PPRE2_DIV2  // PCLK2 = HCLK/2. (Maximum frequency of the high-speed APB2 domain is 84MHz.)
			| RCC_CFGR_PPRE1_DIV4  // PCLK1 = HCLK/4. (Maximum frequency of the low-speed APB1 domain is 42MHz.)
			;

	// Configure the main PLL
	RCC->PLLCFGR = 0
			| RCC_PLLCFGR_PLLSRC_HSE             // select HSE as PLL source
			| (PLL_M << RCC_PLLCFGR_PLLM_Pos)
			| (PLL_N << RCC_PLLCFGR_PLLN_Pos)
			| (((PLL_P >> 1) - 1) << RCC_PLLCFGR_PLLP_Pos)
			| (PLL_Q << RCC_PLLCFGR_PLLQ_Pos)
			;

	// Enable the main PLL
	RCC->CR |= RCC_CR_PLLON;

	// Wait till the main PLL is ready
	while((RCC->CR & RCC_CR_PLLRDY) == 0) ;

	// Configure Flash prefetch, Instruction cache, Data cache and wait state
	FLASH->ACR = 0
			| FLASH_ACR_PRFTEN
			| FLASH_ACR_LATENCY_7WS
			;
	uint32_t tmpreg;
	do
	{
		tmpreg = FLASH->ACR & 7;
	}while(tmpreg!=7);
	// Select the main PLL as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// Wait till the main PLL is used as system clock source
	while ((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL) ;
	// Enable CPU L1-Cache
	SCB_EnableICache();
	SCB_EnableDCache();
}

void InitHw()
{
#if 1
	// turn on FPU:
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  // set CP10 and CP11 to all ones.

	// ensure default configuration:
	RCC->CR |= RCC_CR_HSION;
	RCC->CFGR = 0;
	RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON);
	RCC->PLLCFGR = 0x24003010;                                  // power-on value
	RCC->CR &= ~(RCC_CR_HSEBYP);
	RCC->CIR = 0;                                               // disable all clock interrupts
//	SCB->VTOR = FLASH_BASE;										/* Vector Table Relocation in Internal FLASH */

	InitClocks();
#endif

	// enable GPIOx peripherals
	RCC->AHB1ENR |=
			0
			| RCC_AHB1ENR_GPIOAEN
			| RCC_AHB1ENR_GPIOBEN
			| RCC_AHB1ENR_GPIOCEN
			| RCC_AHB1ENR_GPIODEN
			| RCC_AHB1ENR_GPIOEEN
			| RCC_AHB1ENR_GPIOFEN
			| RCC_AHB1ENR_GPIOGEN
			| RCC_AHB1ENR_GPIOHEN
			| RCC_AHB1ENR_GPIOIEN
			;

//	NVIC_SetPriorityGrouping(7);	// no preemption,           4 bit of subprio (0..15)
//	NVIC_SetPriorityGrouping(6);	// 1 bit preemption (0..1), 3 bit of subprio (0..7)
	NVIC_SetPriorityGrouping(5);	// 2 bit preemption (0..3), 2 bit of subprio (0..3)
//	NVIC_SetPriorityGrouping(4);	// 3 bit preemption (0..3), 1 bit of subprio (0..1)
//	NVIC_SetPriorityGrouping(3);	// 4 bit preemption(0..15), no subprio
}

void Reset_Handler()
{
    if(__low_level_init())
    {
        memcpy(__data_start, __idata_start, __data_end - __data_start); // copy initialized variables
        memset(__bss_start, 0, __bss_end - __bss_start);                // zero-fill uninitialized variables
    	__asm__ __volatile__ ("cpsid i");
        __libc_init_array();                                            // low-level init & ctor loop
    	__asm__ __volatile__ ("cpsie i");
    }
    main();
}

__attribute__ ((weak))
void _init()
{
	InitHw();
}

int __low_level_init()
{
    return 1;
}

