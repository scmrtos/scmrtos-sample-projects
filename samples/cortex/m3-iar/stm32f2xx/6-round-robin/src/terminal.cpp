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
//*     PURPOSE:   Terminal Support File
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
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
  
TTerminalProc TerminalProc;       

char command[16];

char *command_dict[] = 
{
    "help",              // print avaliable commands list
    "gd",                // get debug
};

void help(char *s);
void gd(char *s);

void (*fptr[])(char *s) = 
{
    help,
    gd
};

//------------------------------------------------------------------------------
uint16_t sz[32];
uint16_t idx;
int print(char *format, ...)
{
    va_list args;
    va_start(args, format);
    static char buf[TTerminalDevice::TX_BUF_SIZE/4];
    uint16_t size = vsprintf(buf, format, args);
    va_end(args);

    {
        TTerminalDevice::TIsrLocker IsrLocker;
        TTerminalDevice::TxBuf.write(buf, size);
    }
    USART2->CR1 |= USART_CR1_TXEIE;

    return size;
}
//---------------------------------------------------------------------------
template<> void TTerminalProc::exec()
{
    sleep(1000);
    
    for(;;)
    {
    LBegin:
        TTerminalDevice::NewLineIncoming.wait();
        uint16_t n = strcspn(TTerminalDevice::RxBuf, " \0");
        if(n == 0)
        {
            TTerminalDevice::send("\r\n");
            continue;
        }
        strncpy(command, TTerminalDevice::RxBuf, n);
        command[n] = 0;
        for(uint16_t i = 0; i < sizeof(command_dict)/sizeof(command_dict[0]); i++)
        {
            if(strcmp(command, command_dict[i]) == 0)
            {
                TTerminalDevice::send("... Ok\r\n");
                char *s = TTerminalDevice::RxBuf + n + 1;
                (*fptr[i])(s);
                goto LBegin;
            }
        }
        TTerminalDevice::send("... error: unknown command\r\n");
    }
}
//---------------------------------------------------------------------------
void help(char *s)
{
    TCritSect cs;
    
    TTerminalDevice::send("Supported commands:\r\n");
    for(uint16_t i = 0; i < sizeof(command_dict)/sizeof(command_dict[0]); i++)
    {
        TTerminalDevice::send("\r\n");
        TTerminalDevice::send(command_dict[i]);
    }
    TTerminalDevice::send("\r\n");
}
//---------------------------------------------------------------------------
void gd(char *s)
{
    print("------------------------------\r\n");
    for(uint_fast8_t i = 0; i < OS::PROCESS_COUNT; ++i)
    {
        print("Proc %d | Slack %d\n", i, OS::get_proc(i)->stack_slack() );
    }
}
//---------------------------------------------------------------------------

