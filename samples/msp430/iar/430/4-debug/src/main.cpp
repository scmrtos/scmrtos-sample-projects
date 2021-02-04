//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: MSP430 (Texas Instruments)
//*
//*     TOOLKIT:   EW430 (IAR Systems)
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
//*     MSP430/IAR sample by Harry E. Zhurov, Copyright (c) 2003-2021

#include <scmRTOS.h>
#include "debug.h"
#include "terminal.h"

//---------------------------------------------------------------------------
class TProcProfiler : public TProfiler<SUM_SHIFT>
{
public:
    TProcProfiler() {}
    void get_results(timeout_t acquire_period);
};

//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
TBackgroundProc BackgroundProc;
//---------------------------------------------------------------------------
const uint32_t TIMER_B_PERIOD = 10000;

uint16_t Timer_B_Ticks;

tick_count_t T;                  // global variable for OS::GetTickCount testing
                                 //
OS::TEventFlag ef;               //
OS::TEventFlag Timer_B_Ovf;
TProcProfiler Profiler;

//---------------------------------------------------------------------------
#pragma diag_suppress=Pe951      // suppress return type warning 
void main()
{
    P1DIR |= (1 << 4);
    P5DIR |= (1 << 4);
    P5SEL |= ( (1 << 4) + (1 << 6) );     // MCLK and ACLK out turn on
    P5DIR |= ( (1 << 4) + (1 << 6) );     


    TBCTL = MC_1+ID_0+TBSSEL_2+TBCLR;     // Mode Continuous Up to CCR0, Divider/1, Source SMCLK, Reset TA
    TBCCR0  = TIMER_B_PERIOD;
    TBCCTL0 &= ~CCIFG;                    // Clear flag
    TBCCTL0 |=  CCIE;                     // int. enable

    //------------------------------------------------------
    //
    //    Target platform specific actions.
    //
    //    DCO is used as source for MCLK
    //    Set internal DCO clock at max speed (~5 MHz @ 20 Deg C)
    //
    BCSCTL1 |= ( RSEL0 + RSEL1 + RSEL2 );     
    DCOCTL  |= ( DCO0  + DCO1  + DCO2  );

    //------------------------------------------------------
    //
    //    System Timer start
    //
    //    WatchDog Timer is used as System Timer.
    //
    //    WatchDog Mode: Interval Timer Mode
    //    Enable Watchdog timer interrupts
    //
    WDTCTL  = ( (0x5a << 8) + WDTTMSEL + WDTCNTCL + WDTIS0); 
    IE1    |= 0x01;

    UART::init();

    OS::run();
}
//---------------------------------------------------------------------------
template<> void TProc1::exec()
{
    for(;;)
    {
        ef.wait();
    }     
}
//---------------------------------------------------------------------------
template<> void TProc2::exec()
{
    for(;;)
    {
        Timer_B_Ovf.wait();
        P1OUT &= ~(1 << 4);
    }
}
//---------------------------------------------------------------------------
template<> void TProc3::exec()
{
    for(;;)
    {
        sleep(2);
        ef.signal();
    }
}
//---------------------------------------------------------------------------
template<> void TBackgroundProc::exec()
{
    for(;;)
    {
        Profiler.get_results(1000);
    }
}
//---------------------------------------------------------------------------
void OS::system_timer_user_hook() { /*Profiler.advance_counters();*/ }
//---------------------------------------------------------------------------
void OS::idle_process_user_hook() { }
//---------------------------------------------------------------------------
void OS::context_switch_user_hook() { Profiler.advance_counters(); }
//---------------------------------------------------------------------------
template<uint_fast8_t sum_shift> 
uint32_t TProfiler<sum_shift>::time_interval()
{
    static uint16_t  Timer;
    static uint16_t  TickCount;
    
    uint16_t T            = TBR;
    uint32_t PrevTime     = TickCount*TIMER_B_PERIOD + Timer;
    uint32_t CurTime      = Timer_B_Ticks*TIMER_B_PERIOD + T;
    uint32_t TimeInterval = CurTime - PrevTime;

    if(CurTime < PrevTime)
    {
        TimeInterval += TIMER_B_PERIOD;
    }

    Timer     = T;
    TickCount = Timer_B_Ticks;

    return TimeInterval;
}
//---------------------------------------------------------------------------
void TProcProfiler::get_results(timeout_t acquire_period)
{
    OS::sleep(acquire_period);
    TProfiler::process_data();
    print("------------------------------\n");
    for(uint_fast8_t i = 0; i < OS::PROCESS_COUNT; ++i)
    {
        print("Proc %d | CPU %5.2f | Slack %d\n", i, Profiler.get_result(i)/100.0, OS::get_proc(i)->stack_slack() );
    }
}
//---------------------------------------------------------------------------
#pragma vector = TIMERB0_VECTOR
OS_INTERRUPT void timer_b_isr()
{
    OS::TISRW ISRW;

    ++Timer_B_Ticks;

    ENABLE_NESTED_INTERRUPTS();

    P1OUT |= (1 << 4);
    Timer_B_Ovf.signal_isr();
}
//-----------------------------------------------------------------------------


