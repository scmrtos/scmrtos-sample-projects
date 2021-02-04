//******************************************************************************
//*
//*    Blackfin/bfin-elf support library
//*    
//*    Copyright (c) 2016-2021, Harry E. Zhurov
//*
//******************************************************************************

#ifndef MACRO_H
#define MACRO_H

#include <stdint.h>

#define MMR16(x) ( *((volatile uint16_t*)x) )
#define MMR32(x) ( *((volatile uint32_t*)x) )

//------------------------------------------------------------------------------
#endif  /* MACRO_H */
