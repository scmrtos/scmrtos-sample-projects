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
//*     PURPOSE:   Peripheral Devices Header File
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
//*     Cortex-M3/IAR sample by Harry E. Zhurov, Copyright (c) 2015-2016

#ifndef PERIPHERAL_DEVICES_H
#define PERIPHERAL_DEVICES_H

#include <stdint.h>
#include <scmRTOS.h>

//------------------------------------------------------------------------------
//
//    Terminal device
//
struct TTerminalDevice
{

    static const uint16_t TX_BUF_SIZE = 2048;
    static const uint16_t RX_BUF_SIZE = 128;

    static usr::ring_buffer<char, TX_BUF_SIZE, uint16_t> TxBuf;
    static char                                          RxBuf[RX_BUF_SIZE];
    static uint16_t                                      RxIndex;
    
    static OS::TEventFlag NewLineIncoming;
    
           static void init();
    INLINE static void send(const char  c);
           static void send(const char *s);
    INLINE static void isr();
    
    
    class TIsrLocker
    {
    public:
        INLINE TIsrLocker()  
        { 
            CR1          = USART2->CR1 & (USART_CR1_TXEIE | USART_CR1_RXNEIE); 
            USART2->CR1 &= ~(USART_CR1_TXEIE | USART_CR1_RXNEIE); 
        }
        INLINE ~TIsrLocker() {  USART2->CR1 |= CR1; }
        
    private:
        uint32_t CR1;
    };
    
};
//------------------------------------------------------------------------------

#endif // PERIPHERAL_DEVICES_H
