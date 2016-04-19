//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADSP-BF533 (Analog Devices Inc.)
//*
//*     TOOLKIT:   bfin-elf (GCC)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: v5.1.0
//*
//*
//*     Copyright (c) 2003-2016, scmRTOS Team
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
//*     ADSP-BF533/bfin-elf sample by Harry E. Zhurov, Copyright (c) 2005-2016

//---------------------------------------------------------------------------
#include <scmRTOS.h>
#include "macro.h"
//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 1024> TProc1;
typedef OS::process<OS::pr1, 1024> TProc2;
typedef OS::process<OS::pr2, 1024> TProc3;
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
OS::TEventFlag ef;               //

struct TMamont                   //  data type for sending by message
{                                //
    enum TSource
    {
        PROC_SRC,
        ISR_SRC
    } 
    src;
    int data;                    //
};                               //

TMamont Mamont;                  // global test object for recieve data from message

OS::message<TMamont> MamontMsg;  // OS::message object



EX_INTERRUPT_HANDLER(timer0_isr)  __attribute__ ((interrupt_handler));

OS::TEventFlag ef_timer0;

//---------------------------------------------------------------------------
//#pragma noreturn

int main()
{                 
    //----------------------------------------------------------------------
    //
    //    Set Pcocessor Core clock to 200 MHz, peripheral clock - to 100 MHz
    //    Set Processor Core voltage at 0.85 v
    //
    pll_set_system_vco(8, 0, 0x300);
    pll_set_system_clocks(0, 2);
    ssync();
    
    /////////////////////////////////////////////////////////////////////
    //
    //    System resources setup
    // 
    //-------------------------------------------------------------------
    //
    //  System Timer setup and start
    //
    MMR32(TCNTL)   = 1;        // turn on the timer
    MMR32(TSCALE)  = 0;        //
    MMR32(TPERIOD) = 200000;   // 5ns * 200 000 = 1 ms
    MMR32(TCNTL)   = 0x07;     // run timer 
    //-------------------------------------------------------------------
    //
    //    Register System Interrupt Handlers
    //
    //
    register_handler_ex(ik_timer, OS::system_timer_isr, 1);
    register_handler_ex(ik_ivg14, context_switcher_isr, 1);
    //-------------------------------------------------------------------
    /////////////////////////////////////////////////////////////////////


    MMR16(FIO_DIR) |= (1 << 8) + (1 << 9);

    register_handler_ex(ik_ivg11, timer0_isr, 1);
    MMR32(SIC_IMASK)     = (1 << 16);             // enable Timer0 interrupt
    MMR16(TIMER0_CONFIG) = PWM_OUT  
                         + IRQ_ENA 
                         + PERIOD_CNT 
                         + OUT_DIS; 

    MMR32(TIMER0_PERIOD) = 10011;
    MMR32(TIMER0_WIDTH)  = 5000;
    MMR16(TIMER_ENABLE)  = TIMEN0;                 // timer0 enable

    OS::run();
}
//---------------------------------------------------------------------------
namespace OS 
{
template<> void TProc1::exec()
{
    for(;;)
    {
        //--------------------------------------------------
        //
        //            Message test
        //
        //
        //     Receive data as message
        //
        MamontMsg.wait();                                     // wait for message
        MamontMsg.out(Mamont);                                // read message content to global test object 
        if(Mamont.src == TMamont::PROC_SRC)
        {
            MMR16(FIO_FLAG_C) = (1 << 9);
        }
        else
        {
            MMR16(FIO_FLAG_C) = (1 << 9);
            MMR16(FIO_FLAG_S) = (1 << 9);
            MMR16(FIO_FLAG_C) = (1 << 9);
        }
    }     
}
//---------------------------------------------------------------------------
template<> void TProc2::exec()
{
    for(;;)
    {
        sleep(20);
    }
}
//---------------------------------------------------------------------------
template<> void TProc3::exec()
{
    for(;;)
    {
        sleep(1);
        TMamont m;                     // create message content

        m.src  = TMamont::PROC_SRC;
        m.data = 5;
        MamontMsg = m;                 // put the content to the OS::message object
        MMR16(FIO_FLAG_S) = (1 << 9);
        MamontMsg.send();              // send the message
    }
}

}
//---------------------------------------------------------------------------
//void OS::system_timer_user_hook() { }
//---------------------------------------------------------------------------
void OS::idle_process_user_hook() { }
//---------------------------------------------------------------------------
EX_INTERRUPT_HANDLER(timer0_isr)
{
    OS::TISRW ISR;
    MMR16(TIMER_STATUS) = TIMIL0;

    //--------------------------------------------------
    //
    //            Message test
    //
    //     Send data as message
    //
    TMamont m;                     // create message content

    m.src  = TMamont::ISR_SRC;
    m.data = 10;
    MamontMsg = m;                 // put the content to the OS::message object
    MMR16(FIO_FLAG_S) = (1 << 9);
    MamontMsg.send_isr();          // send the message
}
//---------------------------------------------------------------------------


