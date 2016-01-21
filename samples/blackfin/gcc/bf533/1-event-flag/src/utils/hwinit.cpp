//******************************************************************************
//*
//*              Hardware Initialization Stuff
//*
//*                  VDSP 4.0/Blackfin
//*
//*      Version 1.0
//*
//*      Copyright (c) 2006, Harry E. Zhurov
//*
//*      $Revision$
//*      $Date$
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#include <stdint.h>
#include <device_def.h>
#include <macro.h>

extern "C" void hwinit();
//---------------------------------------------------------------------------
void hwinit()
{
    //------------------------------------------------------------------------
    //
    //  AMC
    //
    MMR16(EBIU_AMGCTL) = AMBEN_B0_B1;
    //------------------------------------------------------------------------
    //
    //  DMA and SDRAM
    //
    MMR16(EBIU_SDRRC)  = 700;             // Refresh rate = 700 cycles @ 10 ns per cycle
    ssync();

    MMR32(EBIU_SDGCTL)  = SCTLE            // Enable CLKOUT, SRAS, SCAS, SWE, SDQM[1:0]
                        | CL_2             // CAS latency = 2 cycles
                        | TRAS_6           // tRAS = 6 cycles
                        | TRP_2            // PRECHARGE command period = 2 cycles
                        | TRCD_2           // ACTIVE to READ or WRITE delay = 2 cycles
                        | TWR_2            // WRITE recovery time = 2 cycles
                        | PSS              // Enables SDRAM powerup sequence on next SDRAM access
                        | EMREN            // Extended mode register loading enable
                        | CDDBG;           // Control disable during bus grant

    ssync();

    MMR16(EBIU_SDBCTL) = EBE              // SDRAM external bank enable
                       | EBSZ_32          // SDRAM external bank size = 32M
                       | EBCAW_9;         // SDRAM external bank column = 9 bits
    ssync();


    uint16_t dummy = MMR16(0);                // Initialize SDRAM Mode Register
    ssync();
}
//---------------------------------------------------------------------------
void SetCoreVoltage(uint8_t   x)
{
  //MMR16(FIO_FLAG_S) = (1 << 5);

    uint16_t vr = MMR16(VR_CTL) & ~0x00f0;
    vr |= x << 4;
    MMR16(VR_CTL) = vr;
    asm( "cli r0; idle; sti r0;");

    //MMR16(FIO_FLAG_C) = (1 << 5);
}
//---------------------------------------------------------------------------

