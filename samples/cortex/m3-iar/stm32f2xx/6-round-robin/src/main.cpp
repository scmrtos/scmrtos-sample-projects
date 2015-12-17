//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   EWARM (IAR Systems)
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: v5.0.1
//*
//*
//*     Copyright (c) 2003-2015, scmRTOS Team
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
//*     Cortex-M3/IAR sample by Harry E. Zhurov, Copyright (c) 2015

#include <stdio.h>
#include <scmRTOS.h>
#include <round-robin.h>

#include "main.h"

//---------------------------------------------------------------------------

TMainProc        MainProc;                    
TAuxProc         AuxProc;                    
TBackgroundProc1 BackgroundProc1;                    
TBackgroundProc2 BackgroundProc2;                    

OS::TEventFlag ef;
round_robin_mgr<2> RoundRobinMgr;



void init();


//---------------------------------------------------------------------------
//
void main()
{
  
    init();  
    
    RoundRobinMgr.register_process(BackgroundProc1, 5);
    RoundRobinMgr.register_process(BackgroundProc2, 20);
    
    OS::run();
}
//---------------------------------------------------------------------------
template<> void TMainProc::exec()
{
    for(;;)
    {
        if( ef.wait(5000) )
        {
            print("timeout Ok\r\n");
        }
        else
        {
            print("timeout expired\r\n");
        }
    }
}
//---------------------------------------------------------------------------
template<> void TAuxProc::exec()
{
    timeout_t t = 1000;
    
    for(;;)
    {
        sleep(t);
        t += 1000;
        if( t >= 7000)
        {
            t = 1000;
        }
        ef.signal();
    }
}
//---------------------------------------------------------------------------
template<> void TBackgroundProc1::exec()
{
    uint32_t cnt = 0;

    for(;;)
    {
        PA3::On(); 
        PA3::Off(); 
        if(++cnt == 58000)
        {
           //os::sleep(2);
            cnt = 0;
        }
    }
}
//---------------------------------------------------------------------------
template<> void TBackgroundProc2::exec()
{
    uint32_t cnt = 0;

    for(;;)
    {
        PA4::On(); 
        PA4::Off(); 
        if(++cnt == 61000)
        {
            os::sleep(2);
            cnt = 0;
        }
    }
}
//---------------------------------------------------------------------------
void OS::system_timer_user_hook() 
{ 
    PA5::On();
    RoundRobinMgr.run(); 
    PA5::Off();

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void init()
{
    //-----------------------------------------------------------------------
    //
    //   RCC config
    //
    RCC->PLLCFGR &= ~( (0x1ff << 6) + 0x3f);           // reset PLLN and PLLM
    RCC->PLLCFGR |=  ( 16                               // ref clock divided by 16
                 |   (100ul << 6)                      // multiplied by 100 and then divided by 2 (default): 16/16*100/2 = 50MHz
                 |    RCC_PLLCFGR_PLLSRC );            // PLL source is HSE

    RCC->CR      |= RCC_CR_PLLON | RCC_CR_HSEON;       // PLL and external high-speed ocsillator turn on

    while( (RCC->CR & RCC_CR_HSERDY) == 0 ) { }        // wait for HSE stabilized

    while( (RCC->CR & RCC_CR_PLLRDY) == 0 ) { }        // wait for PLL locked

    FLASH->ACR |= FLASH_ACR_PRFTEN
               |  FLASH_ACR_ICEN
               |  FLASH_ACR_DCEN
               |  FLASH_ACR_LATENCY_1WS
               ;

    //RCC->CFGR |= RCC_CFGR_PPRE2_2                      // divide by 2
    RCC->CFGR |= RCC_CFGR_PPRE1_2                      // divide by 2
              |  RCC_CFGR_SW_1                         // select PLL as system clock
              ;

    while( (RCC->CFGR & RCC_CFGR_SWS_1) == 0 ) { }     // wait for system clock switched to PLL


    //-----------------------------------------------------------------------
    //
    //   Clock control
    //
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;    // AHB1, 50 MHz
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;    // AHB1, 50 MHz
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;    // AHB1, 50 MHz
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;    // AHB1, 50 MHz
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;    // AHB1, 50 MHz

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     // APB1, 50 MHz (APB1 - 25 MHz, but the timers clocked with 50 MHz clock)
    //RCC->AHB3ENR |= RCC_AHB3ENR_FSMCEN;     // AHB,  50 MHz
                                            
    //RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;     // APB2, 50 MHz
    //RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;     // APB2, 50 MHz
    
    //-----------------------------------------------------------------------
    //
    //   Power control
    //
    PA3::Mode(OUTPUT);
    PA4::Mode(OUTPUT);
    PA5::Mode(OUTPUT);

    //-----------------------------------------------------------------------
    //
    //   GPIO config
    //
//  Button_PWR::Mode(INPUT_PULLUP);
//
//  bnEnter::Mode      (INPUT_PULLUP);
//  bnBack::Mode       (INPUT_PULLUP);
//  bnSettings::Mode   (INPUT_PULLUP);
//  bnHelp::Mode       (INPUT_PULLUP);
//  bnMode::Mode       (INPUT_PULLUP);
//  bnDisagnosis::Mode (INPUT_PULLUP);
//  bnReserved::Mode   (INPUT_PULLUP);
        
    //--------------------------------------------------------------------------
    //
    //   USART1 (used as terminal device) config
    //
    TTerminalDevice::init();
    
}
//-----------------------------------------------------------------------------


