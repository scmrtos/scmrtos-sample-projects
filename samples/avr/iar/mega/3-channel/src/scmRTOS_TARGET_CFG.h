//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   EWAVR (IAR Systems)
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
//*     AVR/IAR sample by Harry E. Zhurov, Copyright (c) 2003-2021

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H

#include <ioavr.h>

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

#  if defined(SPM_READY_vect)
#    define CONTEXT_SWITCH_ISR_VECTOR  SPM_READY_vect
#  elif defined(SPM_RDY_vect)
#    define CONTEXT_SWITCH_ISR_VECTOR  SPM_RDY_vect
#  else
#    error "SPM ready interrupt vector not defined"
#  endif

#endif


#ifndef __IAR_SYSTEMS_ASM__

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

#define SPM_CONTROL_REG SPMCR

#endif


//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
#ifdef  TIMER0_OVF0_vect
#define TIMER0_OVF_vect TIMER0_OVF0_vect
#endif

#define SYSTEM_TIMER_VECTOR TIMER0_OVF_vect
#define LOCK_SYSTEM_TIMER()    ( TIMSK &= ~(1 << TOIE0) )
#define UNLOCK_SYSTEM_TIMER()  ( TIMSK |=  (1 << TOIE0) )

namespace OS
{
    #pragma vector=SYSTEM_TIMER_VECTOR
    OS_INTERRUPT void OS_SystemTimer_ISR();
}

//------------------------------------------------------------------------------
//
//       Context Switch ISR stuff
//
//
namespace OS
{

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

    // enable (and raise) SPM interrupt
    INLINE void raise_context_switch() { SPM_CONTROL_REG |= (1 << SPMIE);  }
    // disable SPM interrupt
    INLINE void block_context_switch() { SPM_CONTROL_REG &= ~(1 << SPMIE); }

    class TNestedISRW              
    {                              
    public:                        
        INLINE TNestedISRW() : State(SPM_CONTROL_REG) { block_context_switch(); __enable_interrupt(); } 
        INLINE ~TNestedISRW() 
        { 
            __disable_interrupt(); 
            SPM_CONTROL_REG = State;
        }
                                                                             
    private:                                                                 
        uint8_t State;                                                          
    };

#  if scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE != 1
#    error scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE must be 1\
          for SPM_READY interrupt context switcher
#  endif

    INLINE void context_switch_user_hook() { block_context_switch(); }

    #define ENABLE_NESTED_INTERRUPTS() OS::TNestedISRW NestedISRW

#else

    #define ENABLE_NESTED_INTERRUPTS() __enable_interrupt()

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME
}
//-----------------------------------------------------------------------------
#else  // __IAR_SYSTEMS_ASM__

#endif // __IAR_SYSTEMS_ASM__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------

