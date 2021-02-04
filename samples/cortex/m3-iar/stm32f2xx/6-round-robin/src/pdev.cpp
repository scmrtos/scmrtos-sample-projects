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
//*     PURPOSE:   Peripheral Devices File
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
//*     Cortex-M3/IAR sample by Harry E. Zhurov, Copyright (c) 2015-2021


#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <scmRTOS.h>
#include "main.h"
                                           
//---------------------------------------------------------------------------
//
//    Terminal device (USART1) code
//
usr::ring_buffer<char, TTerminalDevice::TX_BUF_SIZE, uint16_t> TTerminalDevice::TxBuf;
char                                                           TTerminalDevice::RxBuf[TTerminalDevice::RX_BUF_SIZE];
uint16_t                                                       TTerminalDevice::RxIndex;
OS::TEventFlag                                                 TTerminalDevice::NewLineIncoming;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TTerminalDevice::init()
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  // APB1, 25 MHz
    
    //  USART1 pins
    TerminalDeviceTx::Mode(ALT_OUTPUT);  
    TerminalDeviceTx::Alternate(7);       // USART1

    TerminalDeviceRx::Mode(ALT_INPUT);   
    TerminalDeviceRx::Alternate(7);       // USART1

    //  Common UART control
    //
    USART2->CR1 |= USART_CR1_UE;

    //   Baud Rate
    //
    //   BRR = fCK/(16*fBR) = 50MHz/(16*9600) = 325.521
    //   BRR.M = 325
    //   BRR.F => 0.521 = x/16 => x = BRR.F = 0.521*16 = 8
    //USART1->BRR  = (325ul << 4) + 8; // 9600 @ 50MHz

    USART2->BRR  = (162ul << 4) + 12; // 9600 @ 25MHz

    //   Transmitter and Receiver enable
    //
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;

    NVIC_SetPriority(USART2_IRQn, 10);
    NVIC_EnableIRQ(USART2_IRQn);
    
}
//---------------------------------------------------------------------------
void TTerminalDevice::send(const char c)
{
    USART2->DR   = c;
    USART2->CR1 |= USART_CR1_TXEIE;
}
//---------------------------------------------------------------------------
void TTerminalDevice::send(const char* s)
{
    uint16_t i = 0;
    while(s[i])
    {
        TxBuf.push(s[i++]);
    }

    USART2->CR1 |= USART_CR1_TXEIE;
}
//---------------------------------------------------------------------------
void TTerminalDevice::isr()
{
    OS::TISRW ISR;

    uint32_t status = USART2->SR;

    //-----------------------------------------
    //
    //    Rx
    //
    if(status & USART_SR_RXNE)
    {
        uint32_t data = USART2->DR;            // read data and clear RXNE flag

        switch(data)
        {
        case 27:                               // Esc - kill line
            send("\\\r\n");
            RxIndex = 0;
            break;
        case '\n':
        break;
        case '\b':                             // backspace
            if(RxIndex)
            {
                --RxIndex;
                send("\b \b");                 // erase char
            }
            else
            {
                send('\a');                    // beep instead of echo
            }
            break;
        default:
            RxBuf[RxIndex++] = data;           // place char to buffer
            send(data);                        // echo
            if(RxIndex < sizeof(RxBuf) - 1)
            break;                             // else buffer overflow
        case '\r':                             // CR - execute
            RxBuf[RxIndex] = 0;
            RxIndex = 0;
            NewLineIncoming.signal_isr();
        }       
    }

    //-----------------------------------------
    //
    //    Tx
    //
    if(status & USART_SR_TXE)
    {
        if( TxBuf.get_count() )
        {
            USART2->DR = TxBuf.pop();
        }
        else
        {
            USART2->CR1 &= ~USART_CR1_TXEIE;
        }
    }
    
}
//---------------------------------------------------------------------------
OS_INTERRUPT void USART2_IRQHandler()
{
    TTerminalDevice::isr();
}
//---------------------------------------------------------------------------

