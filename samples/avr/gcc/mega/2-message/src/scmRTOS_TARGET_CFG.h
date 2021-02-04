//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: AVR (Atmel)
//*
//*     TOOLKIT:   avr-gcc (GNU)
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
//*     avr-gcc port by Oleksandr O. Redchuk, Copyright (c) 2007-2021

#ifndef  scmRTOS_TARGET_CFG_H
#define  scmRTOS_TARGET_CFG_H


#include <avr/io.h>
#include <avr/interrupt.h>

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

#if defined(ANA_COMP_vect)
#  define CONTEXT_SWITCH_ISR_VECTOR  ANA_COMP_vect
#elif  defined(ANALOG_COMP_vect)
#  define CONTEXT_SWITCH_ISR_VECTOR  ANALOG_COMP_vect
#else
#  error "Analog comparator vector not defined"
#endif


#endif

#ifndef __ASSEMBLER__

#include <pin_macros.h>

//------------------------------------------------------------------------------
//
//       System Timer stuff
//
//
#if defined(TIMER0_OVF0_vect)
#  define SYSTEM_TIMER_VECTOR TIMER0_OVF0_vect
#elif defined(TIMER0_OVF_vect)
#  define SYSTEM_TIMER_VECTOR TIMER0_OVF_vect
#else
#  error "Timer0 overflow vector not defined"
#endif

#if defined(TIMSK0)
#  define TIMER0_IE_REG TIMSK0
#elif defined(TIMSK)
#  define TIMER0_IE_REG TIMSK
#else
#  error "Timer0 interrupt mask register not defined"
#endif

#if defined(TCCR0B)
#  define TIMER0_CS_REG TCCR0B
#elif defined(TCCR0)
#  define TIMER0_CS_REG TCCR0
#else
#  error "Timer0 control register for CS bits not defined"
#endif

#define LOCK_SYSTEM_TIMER()    ( TIMER0_IE_REG &= ~(1 << TOIE0) )
#define UNLOCK_SYSTEM_TIMER()  ( TIMER0_IE_REG |=  (1 << TOIE0) )


//------------------------------------------------------------------------------
//
//       Context Switch ISR stuff
//
//


namespace OS
{

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 1

#define RAISE_PIN D,7,H

    INLINE void raise_context_switch() {
      #if PORT_TOGGLE_BY_PIN_WRITE
        CPL(RAISE_PIN);
      #else
        ON(RAISE_PIN); OFF(RAISE_PIN);
      #endif
    } // set flag

    INLINE void block_context_switch() { ACSR &= ~(1 << ACIE); } // disable interrupt

    class TNestedISRW
    {
    public:
        INLINE TNestedISRW() : State(ACSR) { block_context_switch(); sei(); }
        INLINE ~TNestedISRW()
        {
            cli();
            ACSR = State;
            if(State & (1 << ACI)) raise_context_switch();
        }

    private:
        uint8_t State;
    };


    #define ENABLE_NESTED_INTERRUPTS() OS::TNestedISRW NestedISRW

#else

    #define ENABLE_NESTED_INTERRUPTS() sei()

#endif // scmRTOS_CONTEXT_SWITCH_SCHEME
}
//-----------------------------------------------------------------------------
#endif // __ASSEMBLER__


#endif // scmRTOS_TARGET_CFG_H
//-----------------------------------------------------------------------------
