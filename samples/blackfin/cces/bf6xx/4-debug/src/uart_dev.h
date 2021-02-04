//******************************************************************************
//*
//*      Project:   TBx
//*
//*      File:      UART device 
//*
//*      Version 1.0
//*
//*      Copyright (c) 2009-2021, scmRTOS Team
//*
//*
//------------------------------------------------------------------------------

#ifndef UART_DEV_H
#define UART_DEV_H

#include <stdint.h>
#include <services\int\adi_int.h>
namespace UART
{
    void init();
    void send(const char  c);
    void send(const char *s);
}

const uint16_t TX_BUF_SIZE = 512;
const uint16_t RX_BUF_SIZE = 128;


extern usr::ring_buffer<char, TX_BUF_SIZE, uint16_t> TxBuf;
extern OS::TEventFlag NewLineIncoming;
extern char RxBuf[RX_BUF_SIZE];

#endif // UART_DEV_H
