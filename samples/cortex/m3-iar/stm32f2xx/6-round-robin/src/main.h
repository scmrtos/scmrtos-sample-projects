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
//*     Version: 5.0.0
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

#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <stdio.h>
#include <string.h>
#include <stm32f2xx.h>
#include <pins.h>
#include <scmRTOS.h>

//---------------------------------------------------------------------------
//
//      Common settings
//
const uint32_t SYS_CLK   = 50000000;
const uint32_t APB1_CLK  = 25000000;
const uint32_t APB2_CLK  = 50000000;
const uint32_t TIMER_CLK = 50000000;


//---------------------------------------------------------------------------
//
//      Project includes
//
#include "pdev.h"
#include "terminal.h"

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 1024> TTerminalProc;   
typedef OS::process<OS::pr1, 1024> TMainProc;        
typedef OS::process<OS::pr2, 1024> TAuxProc;        
typedef OS::process<OS::pr3, 1024> TBackgroundProc1;
typedef OS::process<OS::pr4, 1024> TBackgroundProc2;

//---------------------------------------------------------------------------
//
//      Pin definitions
//

typedef Pin<'D',  5, 'H', PIN_SPEED_100MHZ> TerminalDeviceTx;
typedef Pin<'D',  6, 'H', PIN_SPEED_100MHZ> TerminalDeviceRx;



//------------------------------------------------------
//
//      I/O
//
typedef Pin<'A',  3, 'H', PIN_SPEED_100MHZ> PA3;  // pin 26
typedef Pin<'A',  4, 'H', PIN_SPEED_100MHZ> PA4;  // pin 29
typedef Pin<'A',  5, 'H', PIN_SPEED_100MHZ> PA5;  // pin 30




//---------------------------------------------------------------------------

#endif // CONTROL_PANEL_H

