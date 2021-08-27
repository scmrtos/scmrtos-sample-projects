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
#include <watch_dog_os_ext.h>

// Process types
typedef OS::process<OS::pr0, 300> TProc0;
typedef OS::process<OS::pr1, 300> TProc1;

// Event Flags to test
OS::TEventFlag ef;
OS::TEventFlag timerEvent;

OS::WatchdogExtension wdg;

// Register definitions (you can use CMISIS header or something else)
static volatile uint32_t * const FIO1DIR    = reinterpret_cast<uint32_t *>(0x2009'c020);
static volatile uint32_t * const FIO1SET    = reinterpret_cast<uint32_t *>(0x2009'c038);
static volatile uint32_t * const FIO1CLR    = reinterpret_cast<uint32_t *>(0x2009'c03c);
static volatile uint32_t * const WDMOD      = reinterpret_cast<uint32_t *>(0x4000'0000);
static volatile uint32_t * const WDTC       = reinterpret_cast<uint32_t *>(0x4000'0004);
static volatile uint32_t * const WDFEED     = reinterpret_cast<uint32_t *>(0x4000'0008);
static volatile uint32_t * const WDCLKSEL   = reinterpret_cast<uint32_t *>(0x4000'0010);


static const auto LED1_PIN = 24UL;
static const auto LED2_PIN = 25UL;

void OS::wdg_feed_user_hook() {
    {
        TCritSect cs;
        *WDFEED = 0xaa;
        *WDFEED = 0x55;
    }
}

void OS::wdg_force_reboot_user_hook( const TPriority pr ) {
    const auto failedProcPrio = pr;
    (void)failedProcPrio; // you can log this variable that contains the priority of failed process
    TCritSect cs;
    *WDFEED  = 0xaa;
    *WDMOD   = 0; // incorrect access to WDMOD causes an immediate reset
}

void OS::wdg_init_user_hook() {
    *WDCLKSEL    = 0; // IRC is choosen as clock source
    *WDTC        = 10000; // as clock sources is IRC, then reload timeout
                          // will be 4 * Twdclk * 2000 = 4 * 1/4000000 * 10000 = 10 ms.
    *WDMOD       = 1UL << 0    // WDEN
                   | 1UL << 1; // WDRESET
    wdg_feed_user_hook(); // run WDT
}

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

namespace OS {
    template<>
    OS_PROCESS void TProc0::exec() {
        for (;;) {
            // Here we wait for ef flag signal that gives us the TProc1 process
            ef.wait();
            led1Set(true);
            wdg.alive();
            ef.wait();
            led1Set(false);
            wdg.alive();
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
            wdg.alive();
            timerEvent.wait();
            led2Set(false);
            wdg.alive();
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
    wdg.run();
}

// Process objects
// Note: object declaration and the main() are here because of Error[Pe1449] that gives IAR 8.40.1
TProc0 Proc0;
TProc1 Proc1;

int main() {
    ledPortSetup();

    wdg.register_process(Proc0, 1850);
    wdg.register_process(Proc1, 310);

    // run
    OS::run();
}
