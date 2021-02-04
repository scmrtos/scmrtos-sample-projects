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
//*     PURPOSE:   Port Test File
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

//---------------------------------------------------------------------------
//      Sample target
//  The sample is intended for atmega32 (atmega32A) AVR microcontroller.
//  Some changes in register names may be needed for other AVRs.
//
//  The sample is also intended to show how to use scmRTOS v3.xx oriented
//  sources with scmRTOS v4.00
//  1. Add
//      #include "scmRTOS_310_compat.h"
//     into scmRTOS_CONFIG.h
//  2. Rename process functions from Exec() to exec()
//

//---------------------------------------------------------------------------
#include <scmRTOS.h>
//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 120, 32> TProc1;
typedef OS::process<OS::pr1, 160, 32> TProc2;
typedef OS::process<OS::pr2, 120, 32> TProc3;

template<> void TProc1::exec();
template<> void TProc2::exec();
template<> void TProc3::exec();

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
//---------------------------------------------------------------------------
tick_count_t T;                  // global variable for OS::GetTickCount testing
                                 //

//------------------------------------------------------------------------------
//
//   Message "body"
// 
// 
class TSlon
{
public:
    TSlon() { }
    virtual void eat() = 0;      // feed the slon. For non-russians: slon == elephant ;)
};
//------------------------------------------------------------------------------
class TAfricanSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs; 

        PORTB |= (1 << 4);
        PORTB &= ~(1 << 4);
    }
};
//------------------------------------------------------------------------------
class TIndianSlon : public TSlon
{
public:
    virtual void eat()
    {
        TCritSect cs; 

        PORTB |= (1 << 4);
        PORTB &= ~(1 << 4);
        PORTB |= (1 << 4);
        PORTB &= ~(1 << 4);
    }
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

TAfricanSlon African;   
TIndianSlon  Indian;    
    
OS::channel<TSlon*, 8> SlonQueue; // OS::channel object for 8 'TSlon*' items

OS::TEventFlag Timer1_Ovf;

//---------------------------------------------------------------------------
int main()
{
    DDRB |= (1 << 4); 

    TCCR1B |= (1 << WGM12);   // CTC mode
    OCR1A   = 10005;          // 
    TCCR1B |= (1 << CS10);    // Timer1 run with prescaling 1
    TIMSK  |= (1 << OCIE1A);  // Timer1 OC interrupt enable

    TCCR0 = 0x03;             // Start System Timer
    TIMSK |=  (1 << TOIE0);   //

    OS::run();
}
//---------------------------------------------------------------------------
template<> void TProc1::exec()
{
    for(;;)
    {
        Timer1_Ovf.wait();
        SlonQueue.push(&African);
    }
}
//---------------------------------------------------------------------------
template<> void TProc2::exec()
{
    for(;;)
    {
        T += OS::get_tick_count();

        sleep(1);
        SlonQueue.push(&Indian);
    }
}
//---------------------------------------------------------------------------
template<> void TProc3::exec()
{
    for(;;)
    {
        //--------------------------------------------------
        //
        //            Channel test
        //
        //
        //     Get data through channel
        //
        TSlon *p;
        SlonQueue.pop(p);     // get pointer from queue
        p->eat();             // feed the appropriate Slon
    }
}
//---------------------------------------------------------------------------
#if  scmRTOS_SYSTIMER_HOOK_ENABLE
void OS::system_timer_user_hook() { }
#endif
//---------------------------------------------------------------------------
#if  scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook() { }
#endif
//---------------------------------------------------------------------------
#pragma vector=TIMER1_COMPA_vect
OS_INTERRUPT void Timer1_period_ISR()
{
    OS::TISRW_SS ISRW;

    ENABLE_NESTED_INTERRUPTS();

    Timer1_Ovf.signal_isr();
}
//---------------------------------------------------------------------------


