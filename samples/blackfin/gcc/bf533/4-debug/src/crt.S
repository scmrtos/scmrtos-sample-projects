#include <sys/platform.h>
#include <sys/anomaly_macros_rtl.h>

    .text
    .align 2;
    .global __start;
    .type __start, STT_FUNC;
__start:
    //-------------------------------------------------------------------------
    // Avoid BF532 Anomaly #42 and turn on cycle conter
    r1     = 0x32; // default state + cycle counter enable
    syscfg = r1;

#if WA_05000229
   // Avoid Anomaly 05-00-0229: DMA5_CONFIG and SPI_CTL not cleared on reset.
   R1 = 0x400;
#if defined(__ADSPBF538__) || defined(__ADSPBF539__)
   P0.L = SPI0_CTL & 0xFFFF;
   P0.H = SPI0_CTL >> 16;
   W[P0] = R1.L;
#else
   P0.L = SPI_CTL & 0xFFFF;
   P0.H = SPI_CTL >> 16;
   W[P0] = R1.L;
#endif
   P0.L = DMA5_CONFIG & 0xFFFF;
   P0.H = DMA5_CONFIG >> 16;
   R1 = 0;
   W[P0] = R1.L;
#endif

    //-------------------------------------------------------------------------
    //
    // Set loop counters to zero, to make sure that hw loops are disabled 
    //                      and
    // Set DAG Length register to zero to avoid wrapping around with I-regs using
    //
    r0  = 0;
    lc0 = r0;
    lc1 = r0;
    l0  = r0;
    l1  = r0;
    l2  = r0;
    l3  = r0;
    //-------------------------------------------------------------------------
    //
    // Initialize the Event Vector table.
    //
    p0.h = EVT0 >> 16;
    p0.l = EVT0 & 0xffff;
    //-------------------------------------------------------------------------
    //
    // Install __unknown_exception_occurred in EVT so that 
    // there is defined behaviour.
    //
    p0 += 2*4;      // Skip Emulation and Reset
    p1 = 13;
    r0.l = __unknown_exception_occurred;
    r0.h = __unknown_exception_occurred;
    lsetup (load_def_handler, load_def_handler) lc0 = p1;
load_def_handler:   
    [p0++] = r0;
    //-------------------------------------------------------------------------
    //
    // Switch to supervisor mode at the lowest priority
    // 
    p1.h = LPSM;
    p1.l = LPSM;
    [p0] = p1;

    // Initialise the stack.
    sp.l=__stack_end;
    sp.h=__stack_end;

    // We're still in supervisor mode at the moment, so the FP
    // needs to point to the supervisor stack.
    fp = sp;

    // Move the processor into user mode.
    p0.l = WaitForContinue;
    p0.h = WaitForContinue;
    reti = p0;
    r0.l = 0x8000; // IVG 15 mask
    sti r0;
    raise 15;

WaitForContinue:
    rti;
                                                  
    //-------------------------------------------------------------------------
    //
    // The Lowest Priority Supervisor Mode                 
    //
LPSM:    
    //-------------------------------------------------------------------------
    //
    // Zero fill .bss section
    // 
    r0.l = __bss_start;
    r0.h = __bss_start;
    r1.l = __bss_end;
    r1.h = __bss_end;
    r1   = r1 - r0;
    p1   = r1;
    p0   = r0;
    r0   = 0;
    
    lsetup (zerofill_bss, zerofill_bss) lc0 = p1;
zerofill_bss:    
    B[p0++] = r0;

    [--sp] = reti;  // re-enables the interrupt system
    sp += 4;        // increment on one 32-bit word
    sp += -12;      // And leave space for incoming "parameters"

    r0 = 0;         // load up R0 and R1 and call _main()
    r1 = r0;
    call.x ___libc_init_array;

    sp += 12;       // Restore space for incoming parameters
    jump.x _main;


//------------------------------------------------------------------------------
//
//
//
    .align 2
    .type __unknown_exception_occurred, STT_FUNC;
__unknown_exception_occurred:
    // This function is invoked by the default exception
    // handler, if it does not recognise the kind of
    // exception that has occurred. In other words, the
    // default handler only handles some of the system's
    // exception types, and it does not expect any others
    // to occur. If your application is going to be using
    // other kinds of exceptions, you must replace the
    // default handler with your own, that handles all the
    // exceptions you will use.
    //
    // Since there's nothing we can do, we just loop here
    // at what we hope is a suitably informative label.
    IDLE;
    CSYNC;
    JUMP __unknown_exception_occurred;
    RTS;
    .size __unknown_exception_occurred, .-__unknown_exception_occurred
//------------------------------------------------------------------------------


