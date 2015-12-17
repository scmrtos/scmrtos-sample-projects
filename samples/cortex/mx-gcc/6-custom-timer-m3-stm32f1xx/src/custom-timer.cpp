//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:  Custom system timer module
//*
//*     Version: v5.0.1
//*
//*
//*     Copyright (c) 2003-2015, scmRTOS Team
//*
//*     Permission is hereby granted, free of charge, to any person
//*     obtaining  a copy of this software and associated documentation
//*     files (the "Software"), to deal in the Software without restriction,
//*     including without limitation the rights to use, copy, modify, merge,
//*     publish, distribute, sublicense, and/or sell copies of the Software,
//*     and to permit persons to whom the Software is furnished to do so,
//*     subject to the following conditions:
//*
//*     The above copyright notice and this permission notice shall be included
//*     in all copies or substantial portions of the Software.
//*
//*     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//*     EXPRESS  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//*     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//*     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//*     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//*     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
//*     THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*
//*     =================================================================
//*     Project sources: https://github.com/scmrtos/scmrtos
//*     Documentation:   https://github.com/scmrtos/scmrtos/wiki/Documentation
//*     Wiki:            https://github.com/scmrtos/scmrtos/wiki
//*     Sample projects: https://github.com/scmrtos/scmrtos-sample-projects
//*     =================================================================
//*
//******************************************************************************
//*     GCC STM32F1xx samples by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2015

#include "stm32f10x.h"
#include <scmRTOS.h>

/**
 * Custom system timer configuration.
 */
extern "C" void __init_system_timer()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	NVIC_SetPriority(TIM4_IRQn, 255);
	NVIC_EnableIRQ(TIM4_IRQn);

	TIM4->PSC = 1;
	TIM4->ARR = 36000;          // 1KHz
	TIM4->EGR = TIM_EGR_UG;     // generate an update event to reload the prescaler value immediately
	TIM4->DIER = TIM_DIER_UIE;  // enable update interrupt
	TIM4->CR1 = TIM_CR1_CEN;    // run timer
}

void LOCK_SYSTEM_TIMER()
{
	TIM4->CR1 &= ~TIM_CR1_CEN;
}

void UNLOCK_SYSTEM_TIMER()
{
	TIM4->CR1 |= TIM_CR1_CEN;
}

/**
 * Interrupt handler.
 * Clears interrupt flags and calls the OS::system_timer_isr();
 */
OS_INTERRUPT void TIM4_IRQHandler()
{
	if (TIM4->SR & TIM_SR_UIF)
	{
		TIM4->SR = ~TIM_SR_UIF;
		OS::system_timer_isr();
	}
}
