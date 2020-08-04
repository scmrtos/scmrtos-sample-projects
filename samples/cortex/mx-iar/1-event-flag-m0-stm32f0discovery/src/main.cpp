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
//*     Version: v5.1.0
//*
//*
//*     Copyright (c) 2003-2020, scmRTOS Team
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
//*     IAR 8.40.1 STM32F051 Sample by Yury A. Yakimov aka haker_fox, Copyright (c) 2015-2020

#include <scmRTOS.h>

// Process types
typedef OS::process<OS::pr0, 300> TProc0;
typedef OS::process<OS::pr1, 300> TProc1;
typedef OS::process<OS::pr2, 300> TProc2;

// Event Flags to test
OS::TEventFlag ef;
OS::TEventFlag timerEvent;

// Register defenitions (you can use CMSIS header instead of these definitions)
static uint32_t * const RCC_AHBENR = reinterpret_cast<uint32_t *>(0x40021014);
static uint32_t * const GPIOC_MODER = reinterpret_cast<uint32_t *>(0x48000800);
static uint32_t * const GPIOC_BSRR = reinterpret_cast<uint32_t *>(0x48000818);
static uint32_t * const GPIOA_IDR = reinterpret_cast<uint32_t *>(0x48000010);
// Register bits defenitions (you can use CMSIS header instead of these definitions)
static const uint32_t RCC_AHBENR_IOPCEN = ( 1 << 19UL );
static const uint32_t RCC_AHBENR_IOPAEN = ( 1 << 17UL );
static const uint32_t GPIOC_MODER_8_MASK = ( 3UL << 8 * 2 );
static const uint32_t GPIOC_MODER_9_MASK = ( 3UL << 9 * 2 );
static const uint32_t GPIOC_MODER_8_OUTPUT_MASK = ( 1UL << 8 * 2 );
static const uint32_t GPIOC_MODER_9_OUTPUT_MASK = ( 1UL << 9 * 2 );

static void ledPortSetup() {
    *RCC_AHBENR |= RCC_AHBENR_IOPCEN | RCC_AHBENR_IOPAEN;
    *GPIOC_MODER &= ~(GPIOC_MODER_9_MASK | GPIOC_MODER_8_MASK);
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

int main() {
    ledPortSetup();
    // run
    OS::run();
}

namespace OS {
    template<>
    OS_PROCESS void TProc0::exec() {
        // Led PC 9 on discovery board blinks every 500 ms. Here we use sleep() function
        for (;;) {
            ledPc9Set(true);
            sleep(500);
            ledPc9Set(false);
            sleep(500);
        }
    }

    template<>
    OS_PROCESS void TProc1::exec() {
        for (;;) {
            // Led PC 8 on discovery board blinks every COUNTER_INIT_VALUE (see code
            // below in system_timer_user_hook() function). Here we use OS::TEventFlag service;
            ledPc8Set(true);
            timerEvent.wait();
            ledPc8Set(false);
            timerEvent.wait();
            if (ef.is_signaled()) {
                ef.clear();
                for ( auto i = 0; i < 10; i++ ) {
                    ledPc8Set(true);
                    sleep(100);
                    ledPc8Set(false);
                    sleep(100);
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
            // Yes, it's polling here. But TProc2 has the lowes priority, so it's acceptable.
            if (*GPIOA_IDR & BUTTON_B1_PIN)
                ef.signal();
        }
    }
}

void OS::system_timer_user_hook() {
    static const auto COUNTER_INIT_VALUE = 1000;
    static int counter = COUNTER_INIT_VALUE;
    if (--counter == 0) {
        counter = COUNTER_INIT_VALUE;
        timerEvent.signal_isr();
    }
}

#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook() {
    __WFI();
}
#endif

// Process objects
TProc0 Proc0;
TProc1 Proc1;
TProc2 Proc2;
