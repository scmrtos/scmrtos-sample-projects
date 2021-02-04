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
//*     PURPOSE:   Port Test File (terminal definitions)
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
//*     ADSP-BF533/bfin-elf sample by Harry E. Zhurov, Copyright (c) 2005-2021

#include <list>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "debug.h"
#include "terminal.h"

TTerminalProc TerminalProc("Terminal");       
OS::TEventFlag NewLineIncoming;

char command[16];

const char *command_dict[] = 
{
    "help"   // print avaliable commands list
};

void help(char *s);

void (*fptr[])(char *s) = 
{
    help
};

//------------------------------------------------------------------------------
uint16_t sz[32];
uint16_t idx;
int print(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char buf[TX_BUF_SIZE/2];
    uint16_t size = vsprintf(buf, format, args);
    va_end(args);

    
   // sz[idx++] = size;
    TxBuf.write(buf, size);
    MMR16(UART_IER)  |= ETBEI;

    return size;
}
//---------------------------------------------------------------------------
namespace OS
{

template<> void TTerminalProc::exec()
{
    sleep(1000);
    
    for(;;)
    {
    LBegin:
        NewLineIncoming.wait();
        uint16_t n = strcspn(RxBuf, " \0");
        if(n == 0)
        {
            UART::send("\n\n");
            continue;
        }
        strncpy(command, RxBuf, n);
        command[n] = 0;
        for(uint16_t i = 0; i < sizeof(command_dict)/sizeof(command_dict[0]); i++)
        {
            if(strcmp(command, command_dict[i]) == 0)
            {
                UART::send("... Ok\r");
                char *s = RxBuf + n + 1;
                (*fptr[i])(s);
                goto LBegin;
            }
        }
        UART::send("... error: unknown command\r");
    }
}

}
//---------------------------------------------------------------------------
void help(char *s)
{
    TCritSect cs;
    
    UART::send("Supported commands:\n");
    for(uint16_t i = 0; i < sizeof(command_dict)/sizeof(command_dict[0]); i++)
    {
        UART::send("\n");
        UART::send(command_dict[i]);
    }
    UART::send("\n");
}
//---------------------------------------------------------------------------

