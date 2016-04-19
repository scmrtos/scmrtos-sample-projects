//******************************************************************************
//*
//*      Project:   Any
//*
//*      File:      Vector table
//*
//*      Version 1.0
//*
//*      Copyright (c) 2012-2016, Harry E. Zhurov
//*
//*
//------------------------------------------------------------------------------

                  
#include "exception.h"

//------------------------------------------------------------------------------
#ifdef __ICCARM__
  #pragma language=extended
  #if (__VER__ < 500)
    #pragma segment="CSTACK"
    extern void __program_start();
  #else
    #pragma section="CSTACK"
    extern void __iar_program_start();
  #endif  // #if (__VER__ < 500)
#endif    // #ifdef __ICCARM__

#ifdef __CC_ARM
    extern unsigned int Image$$CSTACK$$ZI$$Limit;
    extern void __main();
#endif
//------------------------------------------------------------------------------
//
//   Vector table
//
typedef void (*intfun_t)();
typedef union 
{ 
    intfun_t intfun;
    void *__ptr;
}
intvec_item_t;
                 
                 
#ifdef __ICCARM__
  #if (__VER__ < 500)
    #pragma location = "INTVEC"
  #else
    #pragma location = ".intvec"
  #endif  // #if (__VER__ < 500)
#endif    // #ifdef __ICCARM__
#ifdef __CC_ARM
  #pragma arm section rodata = "INTVEC"
#endif
                 
                 
extern "C" const intvec_item_t __vector_table[] =
{
#ifdef __ICCARM__

    { .__ptr = __sfe( "CSTACK" ) },

    #if (__VER__ < 500)
        __program_start,
    #else
        __iar_program_start,
    #endif  // #if (__VER__ >= 500)

#endif  // #ifdef __ICCARM__

#ifdef __CC_ARM
    (intfunc) &Image$$CSTACK$$ZI$$Limit,
    __main,
#endif

    //--------------------------------------------------------------------------
    //
    // Cortex-M3 core exceptions 
    // 
    
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    SVC_Handler,
    DebugMon_Handler,
    0,                          // Reserved
    PendSV_Handler,             // The OS context switch interrupt
    SysTick_Handler,            // The OS timer
    
    //--------------------------------------------------------------------------
    //
    // Peripheral interrupts
    // 
    
    WWDG_IRQHandler,            // 0  Window Watchdog
    PVD_IRQHandler,             // 1  PVD through EXTI Line detect
    TAMPER_IRQHandler,          // 2  Tamper
    RTC_IRQHandler,             // 3  RTC
    FLASH_IRQHandler,           // 4  Flash
    RCC_IRQHandler,             // 5  RCC
    EXTI0_IRQHandler,           // 6  EXTI Line 0
    EXTI1_IRQHandler,           // 7  EXTI Line 1
    EXTI2_IRQHandler,           // 8  EXTI Line 2
    EXTI3_IRQHandler,           // 9  EXTI Line 3
    EXTI4_IRQHandler,           // 10 EXTI Line 4
    DMA1_Channel1_IRQHandler,   // 11 DMA1 Channel 1
    DMA1_Channel2_IRQHandler,   // 12 DMA1 Channel 2
    DMA1_Channel3_IRQHandler,   // 13 DMA1 Channel 3
    DMA1_Channel4_IRQHandler,   // 14 DMA1 Channel 4
    DMA1_Channel5_IRQHandler,   // 15 DMA1 Channel 5
    DMA1_Channel6_IRQHandler,   // 16 DMA1 Channel 6
    DMA1_Channel7_IRQHandler,   // 17 DMA1 Channel 7
    ADC1_2_IRQHandler,          // 18 ADC1 and ADC2
    CAN1_TX_IRQHandler,         // 19 CAN1 TX
    CAN1_RX0_IRQHandler,        // 20 CAN1 RX0
    CAN1_RX1_IRQHandler,        // 21 CAN1 RX1
    CAN1_SCE_IRQHandler,        // 22 CAN1 SCE
    EXTI9_5_IRQHandler,         // 23 EXTI Line 9..5
    TIM1_BRK_IRQHandler,        // 24 TIM1 Break
    TIM1_UP_IRQHandler,         // 25 TIM1 Update
    TIM1_TRG_COM_IRQHandler,    // 26 TIM1 Trigger and Commutation
    TIM1_CC_IRQHandler,         // 27 TIM1 Capture Compare
    TIM2_IRQHandler,            // 28 TIM2
    TIM3_IRQHandler,            // 29 TIM3
    TIM4_IRQHandler,            // 30 TIM4
    I2C1_EV_IRQHandler,         // 31 I2C1 Event
    I2C1_ER_IRQHandler,         // 32 I2C1 Error
    I2C2_EV_IRQHandler,         // 33 I2C2 Event
    I2C2_ER_IRQHandler,         // 34 I2C1 Error
    SPI1_IRQHandler,            // 35 SPI1
    SPI2_IRQHandler,            // 36 SPI2
    USART1_IRQHandler,          // 37 USART1
    USART2_IRQHandler,          // 38 USART2
    USART3_IRQHandler,          // 39 USART3
    EXTI15_10_IRQHandler,       // 40 EXTI Line 15..10
    RTCAlarm_IRQHandler,        // 41 RTC alarm through EXTI line
    OTG_FS_WKUP_IRQHandler,     // 42 USB OTG FS Wakeup through EXTI line
    TIM8_BRK_IRQ_Handler,       // 43 TIM8 Break interrupt and TIM12 global interrupt
    TIM8_UP_IRQ_Handler,        // 44 TIM8 Update interrupt and TIM13 global interrupt
    TIM8_TRG_IRQ_Handler,       // 45 TIM8 Trigger and Commutation interrupts and TIM14 global interrupt
    TIM8_CC_IRQ_Handler,        // 46 TIM8 Capture Compare interrupt
    DMA1_Channel8_IRQHandler,   // 47 DMA1 Channel 8
    FSMC_IRQHandler,            // 48 FSMC global interrupt
    SDIO_IRQHandler,            // 49 SDIO global interrupt
    TIM5_IRQHandler,            // 50 TIM5
    SPI3_IRQHandler,            // 51 SPI3
    USART4_IRQHandler,          // 52 UART4
    USART5_IRQHandler,          // 53 UART5
    TIM6_IRQHandler,            // 54 TIM6
    TIM7_IRQHandler,            // 55 TIM7
    DMA2_Channel1_IRQHandler,   // 56 DMA2 Channel1
    DMA2_Channel2_IRQHandler,   // 57 DMA2 Channel2
    DMA2_Channel3_IRQHandler,   // 58 DMA2 Channel3
    DMA2_Channel4_IRQHandler,   // 59 DMA2 Channel4
    DMA2_Channel5_IRQHandler,   // 60 DMA2 Channel5
    ETH_IRQHandler,             // 61 Ethernet
    ETH_WKUP_IRQHandler,        // 62 Ethernet Wakeup through EXTI line
    CAN2_TX_IRQHandler,         // 63 CAN2 TX
    CAN2_RX0_IRQHandler,        // 64 CAN2 RX0
    CAN2_RX1_IRQHandler,        // 65 CAN2 RX1
    CAN2_SCE_IRQHandler,        // 66 CAN2 SCE
    OTG_FS_IRQHandler,          // 67 USB OTG FS
    DMA2_Channel6_IRQHandler,   // 68 DMA2 Channel6
    DMA2_Channel7_IRQHandler,   // 69 DMA2 Channel7
    DMA2_Channel8_IRQHandler,   // 70 DMA2 Channel8
    USART6_IRQHandler,          // 71 USART6
    I2C3_EV_IRQHandler,         // 72 I2C3 event interrupt
    I2C3_ER_IRQHandler,         // 73 I2C3 error interrupt
    OTG_HS_EP1_OUT_IRQHandler,  // 74 USB On The Go HS EP1 Out
    OTG_HS_EP1_IN_IRQHandler,   // 75 USB On The Go HS EP1 In
    OTG_HS_WKUP_IRQHandler,     // 76 USB On The Go Wakeup
    OTG_HS_IRQHandler,          // 77 USB On The Go global interrupt
    DCMI_IRQHandler,            // 78 DCMI global interrupt
    CRYP_IRQHandler,            // 79 Crypto global interrupt
    HASH_RNG_IRQHandler,        // 80 HASH and Rng global interrupt

};

//------------------------------------------------------------------------------

