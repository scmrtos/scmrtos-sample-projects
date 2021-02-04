//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3
//*
//*     TOOLKIT:   ARM IAR
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
//*     IAR 8.40.1 LPC1768 Sample by Yury A. Yakimov aka haker_fox, Copyright (c) 2015-2021

#include <scmRTOS.h>

// Process types
typedef OS::process<OS::pr0, 300> TProc0;
typedef OS::process<OS::pr1, 300> TProc1;

// Event Flags to test
OS::TEventFlag ef;
OS::TEventFlag timerEvent;

// Register definitions (you can use CMISIS header or something else)
static uint32_t * const FIO1DIR = reinterpret_cast<uint32_t *>(0x2009'c020);
static uint32_t * const FIO1SET = reinterpret_cast<uint32_t *>(0x2009'c038);
static uint32_t * const FIO1CLR = reinterpret_cast<uint32_t *>(0x2009'c03c);


static const auto LED1_PIN = 24UL;
static const auto LED2_PIN = 25UL;

static void ledPortSetup() {
    *FIO1DIR |= 1UL << LED1_PIN | 1UL << LED2_PIN;
}

static void ledSet( const bool on, const int pin ) {
    if (on)
        *FIO1SET = 1UL << pin;
    else
        *FIO1CLR = 1UL << pin;
}

static void led1Set( const bool on ) {
    ledSet(on, LED1_PIN);
}

static void led2Set( const bool on ) {
    ledSet(on, LED2_PIN);
}

int main() {
    ledPortSetup();
    // run
    OS::run();
}

namespace OS {
    template<>
    OS_PROCESS void TProc0::exec() {
        for (;;) {
            // Here we wait for ef flag signal that gives us the TProc1 process
            ef.wait();
            led1Set(true);
            ef.wait();
            led1Set(false);
        }
    }

    template<>
    OS_PROCESS void TProc1::exec() {
        for (;;) {
            static const auto COUNTER_VALUE = 3;
            static auto counter = COUNTER_VALUE;
            // Instead of sleep we use here OS::TEventFlag service, see function
            // OS::system_timer_user_hook() below
            timerEvent.wait();
            led2Set(true);
            timerEvent.wait();
            led2Set(false);
            if (--counter == 0) {
                counter = COUNTER_VALUE;
                ef.signal(); // send a signal to TProc0
            }
        }
    }
}

#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook() {
    __WFI();
}
#endif

void OS::system_timer_user_hook() {
    static const auto COUNTER_INIT_VALUE = 300;
    static int counter = COUNTER_INIT_VALUE;
    if (--counter == 0) {
        counter = COUNTER_INIT_VALUE;
        timerEvent.signal_isr();
    }
}

// Process objects
TProc0 Proc0;
TProc1 Proc1;
