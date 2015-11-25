//******************************************************************************
//*
//*      Project:   TBx
//*
//*      File:      Terminal stuff
//*
//*      Version 1.0
//*
//*      Copyright (c) 2009-2015, scmRTOS Team
//*
//*
//------------------------------------------------------------------------------

#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <stdarg.h>
#include <scmRTOS.h>
#include "macro.h"
#include "uart_dev.h"

int print(char *format, ...);
int print(int id,int cpu,int stack);

#endif // TERMINAL_H

