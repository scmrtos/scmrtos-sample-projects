//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: MSP430 (Texas Instruments)
//*
//*     TOOLKIT:   mspgcc (GNU)
//*
//*     PURPOSE:   Project Level Target Extensions Config
//*
//*     Version: v5.2.0
//*
//*
//*     Copyright (c) 2003-2021, scmRTOS Team
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
//*     mspgcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2008-2021

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

#ifdef __MSPGCC__
#include <msp430.h>
#include <legacymsp430.h>
#else
#include <io.h>
#include <signal.h>
#endif	// __MSPGCC__

#define CONTEXT_SWITCH_ISR_VECTOR COMPARATORA_VECTOR


#ifndef __ASSEMBLER__
//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
#define SYSTEM_TIMER_VECTOR WDT_VECTOR

namespace OS
{
interrupt (SYSTEM_TIMER_VECTOR)
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
	SystemTimer_ISR();
#else
    SystemTimer_ISR();
#endif // scmRTOS_CONTEXT_SWITCH_SCHEME
}

#define  LOCK_SYSTEM_TIMER()    ( IE1 &= ~0x01 )
#define  UNLOCK_SYSTEM_TIMER()  ( IE1 |=  0x01 )
//------------------------------------------------------------------------------
//
//       Context Switch ISR stuff
//
//
namespace OS
{
#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void IdleProcessUserHook();
#endif

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

    INLINE void raise_context_switch() { CACTL1 |= (CAIFG|CAIE); } // set flag and enable interrupt

    class TNestedISRW
    {
    public:
        TNestedISRW() : State(CACTL1) { CACTL1 &= ~(CAIFG|CAIE); __enable_interrupt(); }
        ~TNestedISRW() { __disable_interrupt(); CACTL1 = State; }

    private:
        uint8_t State;
    };

    #define ENABLE_NESTED_INTERRUPTS() OS::TNestedISRW NestedISRW

#else

    #define ENABLE_NESTED_INTERRUPTS() __enable_interrupt()

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

}
//------------------------------------------------------------------------------
//
//       Space to reserve in main stack when using TISRW_SS
//
#define TISRW_SS_STACK_PAD  (4)
//------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#endif // __ASSEMBLER__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------

