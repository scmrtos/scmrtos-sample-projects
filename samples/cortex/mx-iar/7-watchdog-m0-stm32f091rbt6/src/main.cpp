//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M0
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
//*     IAR 8.40.1 STM32F091 Sample by Yury A. Yakimov aka haker_fox, Copyright (c) 2015-2021

#include <scmRTOS.h>
#include <watch_dog_os_ext.h>

// Process types
typedef OS::process<OS::pr0, 300> TProc0;
typedef OS::process<OS::pr1, 300> TProc1;
typedef OS::process<OS::pr2, 300> TProc2;

// Event Flags to test
OS::TEventFlag ef;
OS::TEventFlag timerEvent;

// Here all our tasks (excluding IDLE) are under watchdog service
OS::WatchdogExtension wdg;

// Register defenitions (you can use CMSIS header instead of these definitions)
static volatile uint32_t * const RCC_AHBENR     = reinterpret_cast<uint32_t *>(0x40021014);
static volatile uint32_t * const GPIOC_MODER    = reinterpret_cast<uint32_t *>(0x48000800);
static volatile uint32_t * const GPIOC_BSRR     = reinterpret_cast<uint32_t *>(0x48000818);
static volatile uint32_t * const GPIOA_IDR      = reinterpret_cast<uint32_t *>(0x48000010);
static volatile uint32_t * const IWDG_KR        = reinterpret_cast<uint32_t *>(0x40003000);
// Register bits defenitions (you can use CMSIS header instead of these definitions)
static const uint32_t RCC_AHBENR_IOPCEN         = ( 1 << 19UL );
static const uint32_t RCC_AHBENR_IOPAEN         = ( 1 << 17UL );
static const uint32_t GPIOC_MODER_8_MASK        = ( 3UL << 8 * 2 );
static const uint32_t GPIOC_MODER_9_MASK        = ( 3UL << 9 * 2 );
static const uint32_t GPIOC_MODER_8_OUTPUT_MASK = ( 1UL << 8 * 2 );
static const uint32_t GPIOC_MODER_9_OUTPUT_MASK = ( 1UL << 9 * 2 );

void OS::wdg_feed_user_hook() {
    static const uint16_t RELOAD_KR         = 0xaaaa;
    *IWDG_KR = RELOAD_KR;
}

void OS::wdg_force_reboot_user_hook( const TPriority pr ) {
    const auto failedProcPrio = pr;
    (void)failedProcPrio; // you can log this variable that contains the priority of failed process
}

void OS::wdg_init_user_hook() {
    // IWDG enabled in option byte and start immediately after power up of microcontroller
}

static void ledPortSetup() {
    *RCC_AHBENR |= RCC_AHBENR_IOPCEN | RCC_AHBENR_IOPAEN;
    *GPIOC_MODER &= ~( GPIOC_MODER_9_MASK | GPIOC_MODER_8_MASK );
    *GPIOC_MODER |= GPIOC_MODER_9_OUTPUT_MASK | GPIOC_MODER_8_OUTPUT_MASK;
}
static void ledPc9Set( const bool on ) {
    static const auto LED_PIN = 9;
    const int lp = ( on ? 0 : 16 ) + LED_PIN;
    *GPIOC_BSRR = ( 1UL << lp );
}
static void ledPc8Set( const bool on ) {
    static const auto LED_PIN = 8;
    const int lp = ( on ? 0 : 16 ) + LED_PIN;
    *GPIOC_BSRR = ( 1UL << lp );
}

namespace OS {
    template<>
    OS_PROCESS void TProc0::exec() {
        // Led PC 9 on discovery board blinks every 500 ms. Here we use sleep() function
        for (;;) {
            ledPc9Set(true);
            sleep(500);
            wdg.alive();
            ledPc9Set(false);
            sleep(500);
            wdg.alive();
        }
    }

    template<>
    OS_PROCESS void TProc1::exec() {
        for (;;) {
            // Led PC 8 on discovery board blinks every COUNTER_INIT_VALUE (see code
            // below in system_timer_user_hook() function). Here we use OS::TEventFlag service;
            ledPc8Set(true);
            timerEvent.wait();
            wdg.alive();
            ledPc8Set(false);
            timerEvent.wait();
            wdg.alive();
            if (ef.is_signaled()) {
                ef.clear();
                for ( auto i = 0; i < 10; i++ ) {
                    ledPc8Set(true);
                    sleep(100);
                    ledPc8Set(false);
                    sleep(100);
                    wdg.alive();
                }
            }
        }
    }

    template<>
    OS_PROCESS void TProc2::exec() {
        static const auto BUTTON_B1_PIN = 1UL << 0;
        for (;;) {
            // Every time we press USER button this task sends signal to TPpoc1 and
            // it flashes PC 8 at higher frequency for a while, then restores original rate.
            if (*GPIOA_IDR & BUTTON_B1_PIN)
                ef.signal();
            wdg.alive();
            sleep(10); // this need to give some time for idle task, so it can feed 'her watchdog'
        }
    }
}

void OS::system_timer_user_hook() {
    wdg.run();
    static const auto COUNTER_INIT_VALUE = 1000;
    static int counter = COUNTER_INIT_VALUE;
    if (--counter == 0) {
        counter = COUNTER_INIT_VALUE;
        timerEvent.signal_isr();
    }
}

#if scmRTOS_IDLE_HOOK_ENABLE == 1
void OS::idle_process_user_hook() {
    __WFI();
    wdg.alive();
}
#endif

// Process objects
// Note: object declaration and the main() are here because of Error[Pe1449] that gives IAR 8.40.1
TProc0 Proc0;
TProc1 Proc1;
TProc2 Proc2;

int main() {
    ledPortSetup();
    wdg.register_process(Proc0, 510);
    wdg.register_process(Proc1, 1010);
    wdg.register_process(Proc2, 15);

    // you also may not add idle task
    extern OS::TIdleProc IdleProc;
    wdg.register_process(OS::IdleProc, 100);

    // run
    OS::run();
}
