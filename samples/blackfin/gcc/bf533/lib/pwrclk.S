//------------------------------------------------------------------------------
//*
//*    Copyright (C) 2003-2006 Analog Devices, Inc. All Rights Reserved.
//*
//*    Facilities for modifying the Phase-Locked Loop, to
//*    alter core/system clocks and the Voltage-Controlled
//*    Oscillator's frequency.
//*
//------------------------------------------------------------------------------
//*    bfin-elf port by Harry E. Zhurov, Copyright (c) 2016-2021


#include <sys/platform.h>
#include <sys/anomaly_macros_rtl.h>

    .text
    .align 2;
//------------------------------------------------------------------------------

#if defined(__ADSPLPBLACKFIN__)
//#if SET_CLOCK_SPEED == 1

/*
** CLKIN == 27MHz on the EZ-Kits.
** D==0 means CLKIN is passed to PLL without dividing.
** MSEL==0x16 means VCO==27*0x16 == 594MHz
** CSEL==0 means CCLK==VCO == 594MHz
** SSEL==5 means SCLK==VCO/5 == 118MHz
*/

// int pll_set_system_clocks(int csel, int ssel)
// returns 0 for success, -1 for error.

    .align 2
    .global _pll_set_system_clocks;
    .type _pll_set_system_clocks, STT_FUNC;
_pll_set_system_clocks:
    P0.H = PLL_DIV >> 16;
    P0.L = PLL_DIV & 0xFFFF;
    R2 = W[P0] (Z);

    // Plant CSEL and SSEL
    R0 <<= 16;
    R0.L = (4 << 8) | 2;    // 2 bits, at posn 4
    R1 <<= 16;
    R1.L = 4;       // 4 bits, at posn 0
    R2 = DEPOSIT(R2, R0);

#if defined(__WORKAROUND_DREG_COMP_LATENCY)
        // Work around anomaly 05-00-0209 which affects the DEPOSIT
        // instruction (and the EXTRACT, SIGNBITS, and EXPADJ instructions)
        // if the previous instruction created any of its operands
        NOP;
#endif

    R2 = DEPOSIT(R2, R1);

    W[P0] = R2;
    SSYNC;
    RTS;
    .size __pll_set_system_clocks, .-__pll_set_system_clocks

// int pll_set_system_vco(int msel, int df, lockcnt)
    .align 2
    .global _pll_set_system_vco;
    .type _pll_set_system_vco, STT_FUNC;
_pll_set_system_vco:
    P0.H = PLL_CTL >> 16;
    P0.L = PLL_CTL & 0xFFFF;
    R3 = W[P0] (Z);
    P2 = R3;        // Save copy
    R3 >>= 1;       // Drop old DF
        R1 = ROT R1 BY -1;      // Move DF into CC
    R3 = ROT R3 BY 1;   // and into ctl space.
    R0 <<= 16;      // Set up pattern reg
    R0.L = (9<<8) | 6;  // (6 bits at posn 9)
        R1 = P2;                // Get the old version
    R3 = DEPOSIT(R3, R0);
    CC = R1 == R3;      // and if we haven't changed
    IF CC JUMP L$done;  // Anything, return

    CC = R2 == 0;       // Use default lockcount if
    IF CC JUMP L$wakeup;    // user one is zero.
    P2.H = PLL_LOCKCNT >> 16;
    P2.L = PLL_LOCKCNT & 0xFFFF;
    W[P2] = R2;     // Set the lock counter
L$wakeup:
    P2.H = SIC_IWR >> 16;
    P2.L = SIC_IWR & 0xFFFF;
    R2 = [P2];
    BITSET(R2, 0);      // enable PLL Wakeup
    [P2] = R2;

    W[P0] = R3;     // Update PLL_CTL
    SSYNC;

    CLI R2;         // Avoid unnecessary interrupts
    IDLE;           // Wait until PLL has locked
    STI R2;         // Restore interrupts.

L$done:
    RTS;
    .size __pll_set_system_vco, .-__pll_set_system_vco
//#endif
#endif /* ADSPLPBLACKFIN */
//------------------------------------------------------------------------------


