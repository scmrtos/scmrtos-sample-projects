
#include <sys/platform.h>


//------------------------------------------------------------------------------
//
//   Data and code global and extern labels
//
//

    .section .text;
    .align 2
/*
    .global rtinit_start;          
    .type crt_init_start, STT_FUNC;
*/
    .global __start;
    .type   __start, STT_FUNC;


//------------------------------------------------------------------------------

//crt_init_start:
__start:
 
    [--sp] = astat;         //save regs onto stack
    [--sp] = rets;
    [--sp] = (r7:0);
    [--sp] = (p5:0);
    [--sp] = i0;
    [--sp] = i1;
    [--sp] = i2;
    [--sp] = i3;
    [--sp] = b0;
    [--sp] = b1;
    [--sp] = b2;
    [--sp] = b3;
    [--sp] = m0;
    [--sp] = m1;
    [--sp] = m2;
    [--sp] = m3;
    [--sp] = l0;
    [--sp] = l1;
    [--sp] = l2;
    [--sp] = l3;

    sp += -12;      // And leave space for incoming "parameters"
            
    call.x _hwinit;    
    call.x _main;

    sp += 12;       // Restore space for incoming parameters

    l3 = [sp++];
    l2 = [sp++];    
    l1 = [sp++];
    l0 = [sp++];
    m3 = [sp++];
    m2 = [sp++];
    m1 = [sp++];
    m0 = [sp++];
    b3 = [sp++];
    b2 = [sp++];
    b1 = [sp++];
    b0 = [sp++];
    i3 = [sp++];
    i2 = [sp++];
    i1 = [sp++];
    i0 = [sp++];
    (p5:0) = [sp++];        //restore regs from stack
    (r7:0) = [sp++];
    rets = [sp++];
    astat = [sp++];
//------------------------------------------------------------------------------

    rts;

rtinit_start.end:
