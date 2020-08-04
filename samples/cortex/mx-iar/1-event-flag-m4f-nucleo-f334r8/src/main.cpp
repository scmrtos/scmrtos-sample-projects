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

// Event Flags to test
OS::TEventFlag ef;

// Register defenitions (you can use CMSIS header instead of these definitions)
static uint32_t * const RCC_AHBENR = reinterpret_cast<uint32_t *>(0x40021014);
static uint32_t * const GPIOA_MODER = reinterpret_cast<uint32_t *>(0x4800'0000);
static uint32_t * const GPIOA_BSRR = reinterpret_cast<uint32_t *>(0x4800'0018);
static uint32_t * const GPIOC_IDR = reinterpret_cast<uint32_t *>(0x48000810);
// Register bits defenitions (you can use CMSIS header instead of these definitions)
static const uint32_t RCC_AHBENR_IOPAEN = ( 1 << 17UL );
static const uint32_t RCC_AHBENR_IOPCEN = ( 1 << 19UL );
static const uint32_t GPIOA_MODER_5_MASK = ( 3UL << 5 * 2 );
static const uint32_t GPIOA_MODER_5_OUTPUT_MASK = ( 1UL << 5 * 2 );

static void ledPortSetup() {
    *RCC_AHBENR |= RCC_AHBENR_IOPAEN | RCC_AHBENR_IOPCEN;
    *GPIOA_MODER &= ~GPIOA_MODER_5_MASK;
    *GPIOA_MODER |= GPIOA_MODER_5_OUTPUT_MASK;
}
static void ledLD2Set( const bool on ) {
    static const auto LED_PIN = 5;
    const int lp = ( on ? 0 : 16 ) + LED_PIN;
    *GPIOA_BSRR = ( 1UL << lp );
}

int main() {
    ledPortSetup();
    // run
    OS::run();
}

namespace OS {
    template<>
    OS_PROCESS void TProc0::exec() {
        // Led LD2 on nucleo board blinks every 500 ms. Here we use sleep() function
        for (;;) {
            ledLD2Set(true);
            sleep(500);
            ledLD2Set(false);
            sleep(500);
            if (ef.is_signaled()) {
                ef.clear();
                for ( auto i = 0; i < 10; i++ ) {
                    ledLD2Set(true);
                    sleep(100);
                    ledLD2Set(false);
                    sleep(100);
                }
            }
        }
    }

    template<>
    OS_PROCESS void TProc1::exec() {
        static const auto BUTTON_B1_PIN = 1UL << 13;
        for (;;) {
            // Every time we press USER button this task sends signal to TPpoc0 and
            // it flashes LD2 at higher frequency for a while, then restores original rate.
            // Yes, it's polling here. But TProc1 has the lowest priority, so it's acceptable.
            if (!( *GPIOC_IDR & BUTTON_B1_PIN ))
                ef.signal();
        }
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
