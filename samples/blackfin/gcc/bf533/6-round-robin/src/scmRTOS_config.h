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
//*     PURPOSE:   Project Level Configuration
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

#ifndef  scmRTOS_CONFIG_H
#define  scmRTOS_CONFIG_H

typedef uint32_t      timeout_t;
typedef uint_fast32_t tick_count_t;
                                            
//------------------------------------------------------------------------------
//
//    Specify scmRTOS Process Count. Must be less then 15
//
//
#define  scmRTOS_PROCESS_COUNT                  6

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Tick Counter Enable
//
//
#define  scmRTOS_SYSTEM_TICKS_ENABLE        1

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Hook.
//
//
#define  scmRTOS_SYSTIMER_HOOK_ENABLE       1

//-----------------------------------------------------------------------------
//
//    scmRTOS Idle Process Hook.
//
//
#define  scmRTOS_IDLE_HOOK_ENABLE           1

//-----------------------------------------------------------------------------
//
//    scmRTOS Idle Process Stack size (in bytes)
//
//
#define scmRTOS_IDLE_PROCESS_STACK_SIZE       768

//-----------------------------------------------------------------------------
//
//    scmRTOS Priority Order
//
//    This macro defines the order of the process's priorities. Default, 
//    the ascending order is used in scmRTOS. Alternatively, the descending priority 
//    order can be used. On Blackfin platform the descending order is preferred
//    because of performance.   
// 
//    Default on Blackfin value of macro is 1 (corresponding to descending order).  
//    Alternative (corresponding to ascending order) value of macro is 0.  
//    Uncomment the macro below to select ascending order of priorities.
//
//#define  scmRTOS_PRIORITY_ORDER 0

//-----------------------------------------------------------------------------
//
//    scmRTOS Context Switch User Hook enable
// 
//    The macro enables/disables user defined hook called from system
//    Context Switch Hook function.
//
//
#define  scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE  1


//-----------------------------------------------------------------------------
//
//    scmRTOS debug enable
// 
//    The macro enables debug mode which allows debug functionality
//    such as finding process's stack slack and some other.
//
//
#define scmRTOS_DEBUG_ENABLE  1

//-----------------------------------------------------------------------------

#endif // scmRTOS_CONFIG_H
