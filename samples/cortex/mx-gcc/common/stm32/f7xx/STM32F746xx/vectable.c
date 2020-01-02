//******************************************************************************
//*
//*      STM32F746XX vector table
//*
//*      Version 1.1
//*
//*      Copyright (c) 2016, emb-lib Project Team
//*
//*      This file is part of the arm-none-eabi-startup project.
//*      Visit https://github.com/emb-lib/arm-none-eabi-startup for new versions.
//*
//*      Permission is hereby granted, free of charge, to any person
//*      obtaining  a copy of this software and associated documentation
//*      files (the "Software"), to deal in the Software without restriction,
//*      including without limitation the rights to use, copy, modify, merge,
//*      publish, distribute, sublicense, and/or sell copies of the Software,
//*      and to permit persons to whom the Software is furnished to do so,
//*      subject to the following conditions:
//*
//*      The above copyright notice and this permission notice shall be included
//*      in all copies or substantial portions of the Software.
//*
//*      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//*      EXPRESS  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//*      MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//*      IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//*      CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//*      TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
//*      THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*
//------------------------------------------------------------------------------

#include "exhandler.h"

//------------------------------------------------------------------------------
__attribute__ ((used))
__attribute__ ((section(".isr_vector")))
const __vector_table_t __vector_table =
{
    __top_of_stack,
    
    {
    Reset_Handler,

    //--------------------------------------------------------------------------
    //
    // Cortex-M core exceptions 
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
    WWDG_IRQHandler,                  // Window WatchDog                                        
    PVD_IRQHandler,                   // PVD through EXTI Line detection                        
    TAMP_STAMP_IRQHandler,            // Tamper and TimeStamps through the EXTI line            
    RTC_WKUP_IRQHandler,              // RTC Wakeup through the EXTI line                       
    FLASH_IRQHandler,                 // FLASH                                           
    RCC_IRQHandler,                   // RCC                                             
    EXTI0_IRQHandler,                 // EXTI Line0                                             
    EXTI1_IRQHandler,                 // EXTI Line1                                             
    EXTI2_IRQHandler,                 // EXTI Line2                                             
    EXTI3_IRQHandler,                 // EXTI Line3                                             
    EXTI4_IRQHandler,                 // EXTI Line4                                             
    DMA1_Stream0_IRQHandler,          // DMA1 Stream 0                                   
    DMA1_Stream1_IRQHandler,          // DMA1 Stream 1                                   
    DMA1_Stream2_IRQHandler,          // DMA1 Stream 2                                   
    DMA1_Stream3_IRQHandler,          // DMA1 Stream 3                                   
    DMA1_Stream4_IRQHandler,          // DMA1 Stream 4                                   
    DMA1_Stream5_IRQHandler,          // DMA1 Stream 5                                   
    DMA1_Stream6_IRQHandler,          // DMA1 Stream 6                                   
    ADC_IRQHandler,                   // ADC1, ADC2 and ADC3s                            
    CAN1_TX_IRQHandler,               // CAN1 TX                                                
    CAN1_RX0_IRQHandler,              // CAN1 RX0                                               
    CAN1_RX1_IRQHandler,              // CAN1 RX1                                               
    CAN1_SCE_IRQHandler,              // CAN1 SCE                                               
    EXTI9_5_IRQHandler,               // External Line[9:5]s                                    
    TIM1_BRK_TIM9_IRQHandler,         // TIM1 Break and TIM9                   
    TIM1_UP_TIM10_IRQHandler,         // TIM1 Update and TIM10                 
    TIM1_TRG_COM_TIM11_IRQHandler,    // TIM1 Trigger and Commutation and TIM11
    TIM1_CC_IRQHandler,               // TIM1 Capture Compare                                   
    TIM2_IRQHandler,                  // TIM2                                            
    TIM3_IRQHandler,                  // TIM3                                            
    TIM4_IRQHandler,                  // TIM4                                            
    I2C1_EV_IRQHandler,               // I2C1 Event                                             
    I2C1_ER_IRQHandler,               // I2C1 Error                                             
    I2C2_EV_IRQHandler,               // I2C2 Event                                             
    I2C2_ER_IRQHandler,               // I2C2 Error                                               
    SPI1_IRQHandler,                  // SPI1                                            
    SPI2_IRQHandler,                  // SPI2                                            
    USART1_IRQHandler,                // USART1                                          
    USART2_IRQHandler,                // USART2                                          
    USART3_IRQHandler,                // USART3                                          
    EXTI15_10_IRQHandler,             // External Line[15:10]s                                  
    RTC_Alarm_IRQHandler,             // RTC Alarm (A and B) through EXTI Line                  
    OTG_FS_WKUP_IRQHandler,           // USB OTG FS Wakeup through EXTI line                        
    TIM8_BRK_TIM12_IRQHandler,        // TIM8 Break and TIM12                  
    TIM8_UP_TIM13_IRQHandler,         // TIM8 Update and TIM13                 
    TIM8_TRG_COM_TIM14_IRQHandler,    // TIM8 Trigger and Commutation and TIM14
    TIM8_CC_IRQHandler,               // TIM8 Capture Compare                                   
    DMA1_Stream7_IRQHandler,          // DMA1 Stream7                                           
    FMC_IRQHandler,                   // FMC                                             
    SDMMC1_IRQHandler,                // SDMMC1                                            
    TIM5_IRQHandler,                  // TIM5                                            
    SPI3_IRQHandler,                  // SPI3                                            
    UART4_IRQHandler,                 // UART4                                           
    UART5_IRQHandler,                 // UART5                                           
    TIM6_DAC_IRQHandler,              // TIM6 and DAC1&2 underrun errors                   
    TIM7_IRQHandler,                  // TIM7                   
    DMA2_Stream0_IRQHandler,          // DMA2 Stream 0                                   
    DMA2_Stream1_IRQHandler,          // DMA2 Stream 1                                   
    DMA2_Stream2_IRQHandler,          // DMA2 Stream 2                                   
    DMA2_Stream3_IRQHandler,          // DMA2 Stream 3                                   
    DMA2_Stream4_IRQHandler,          // DMA2 Stream 4                                   
    ETH_IRQHandler,                   // Ethernet                                        
    ETH_WKUP_IRQHandler,              // Ethernet Wakeup through EXTI line                      
    CAN2_TX_IRQHandler,               // CAN2 TX                                                
    CAN2_RX0_IRQHandler,              // CAN2 RX0                                               
    CAN2_RX1_IRQHandler,              // CAN2 RX1                                               
    CAN2_SCE_IRQHandler,              // CAN2 SCE                                               
    OTG_FS_IRQHandler,                // USB OTG FS                                      
    DMA2_Stream5_IRQHandler,          // DMA2 Stream 5                                   
    DMA2_Stream6_IRQHandler,          // DMA2 Stream 6                                   
    DMA2_Stream7_IRQHandler,          // DMA2 Stream 7                                   
    USART6_IRQHandler,                // USART6                                           
    I2C3_EV_IRQHandler,               // I2C3 event                                             
    I2C3_ER_IRQHandler,               // I2C3 error                                             
    OTG_HS_EP1_OUT_IRQHandler,        // USB OTG HS End Point 1 Out                      
    OTG_HS_EP1_IN_IRQHandler,         // USB OTG HS End Point 1 In                       
    OTG_HS_WKUP_IRQHandler,           // USB OTG HS Wakeup through EXTI                         
    OTG_HS_IRQHandler,                // USB OTG HS                                      
    DCMI_IRQHandler,                  // DCMI                                            
    0,                                // Reserved                                     
    RNG_IRQHandler,                   // Rng
    FPU_IRQHandler,                   // FPU
    UART7_IRQHandler,                 // UART7
    UART8_IRQHandler,                 // UART8
    SPI4_IRQHandler,                  // SPI4
    SPI5_IRQHandler,                  // SPI5
    SPI6_IRQHandler,                  // SPI6
    SAI1_IRQHandler,                  // SAI1
    LTDC_IRQHandler,                  // LTDC
    LTDC_ER_IRQHandler,               // LTDC error
    DMA2D_IRQHandler,                 // DMA2D
    SAI2_IRQHandler,                  // SAI2
    QUADSPI_IRQHandler,               // QUADSPI
    LPTIM1_IRQHandler,                // LPTIM1
    CEC_IRQHandler,                   // HDMI_CEC
    I2C4_EV_IRQHandler,               // I2C4 Event                                             
    I2C4_ER_IRQHandler,               // I2C4 Error 
    SPDIF_RX_IRQHandler               // SPDIF_RX
    }
};
//------------------------------------------------------------------------------
__attribute__ ((noreturn))
static void default_handler() { for(;;) { } }
static void hf_handler()
{
    volatile int i = 0;         //  debug variable: set non-zero value to 
    while(!i) { }               //  return from handler - this figures out 
                                //  an address where HW fault raises
}
//------------------------------------------------------------------------------
//
//   Default exception handlers
//
#ifdef NDEBUG

#pragma weak NMI_Handler        = default_handler
#pragma weak HardFault_Handler  = default_handler
#pragma weak MemManage_Handler  = default_handler
#pragma weak BusFault_Handler   = default_handler
#pragma weak UsageFault_Handler = default_handler
#pragma weak SVC_Handler        = default_handler
#pragma weak DebugMon_Handler   = default_handler
#pragma weak PendSV_Handler     = default_handler
#pragma weak SysTick_Handler    = default_handler

#else // NDEBUG

WEAK void NMI_Handler        ()  { default_handler(); }
WEAK void HardFault_Handler  ()  { hf_handler();      }
WEAK void MemManage_Handler  ()  { default_handler(); }
WEAK void BusFault_Handler   ()  { default_handler(); }
WEAK void UsageFault_Handler ()  { default_handler(); }
WEAK void SVC_Handler        ()  { default_handler(); }
WEAK void DebugMon_Handler   ()  { default_handler(); }
WEAK void PendSV_Handler     ()  { default_handler(); }
WEAK void SysTick_Handler    ()  { default_handler(); }

#endif // NDEBUG

//------------------------------------------------------------------------------
//
//   Default interrupt handlers
//
#ifdef NDEBUG

#pragma weak WWDG_IRQHandler               = default_handler
#pragma weak PVD_IRQHandler                = default_handler
#pragma weak TAMP_STAMP_IRQHandler         = default_handler
#pragma weak RTC_WKUP_IRQHandler           = default_handler
#pragma weak FLASH_IRQHandler              = default_handler
#pragma weak RCC_IRQHandler                = default_handler
#pragma weak EXTI0_IRQHandler              = default_handler
#pragma weak EXTI1_IRQHandler              = default_handler
#pragma weak EXTI2_IRQHandler              = default_handler
#pragma weak EXTI3_IRQHandler              = default_handler
#pragma weak EXTI4_IRQHandler              = default_handler
#pragma weak DMA1_Stream0_IRQHandler       = default_handler
#pragma weak DMA1_Stream1_IRQHandler       = default_handler
#pragma weak DMA1_Stream2_IRQHandler       = default_handler
#pragma weak DMA1_Stream3_IRQHandler       = default_handler
#pragma weak DMA1_Stream4_IRQHandler       = default_handler
#pragma weak DMA1_Stream5_IRQHandler       = default_handler
#pragma weak DMA1_Stream6_IRQHandler       = default_handler
#pragma weak ADC_IRQHandler                = default_handler
#pragma weak CAN1_TX_IRQHandler            = default_handler
#pragma weak CAN1_RX0_IRQHandler           = default_handler
#pragma weak CAN1_RX1_IRQHandler           = default_handler
#pragma weak CAN1_SCE_IRQHandler           = default_handler
#pragma weak EXTI9_5_IRQHandler            = default_handler
#pragma weak TIM1_BRK_TIM9_IRQHandler      = default_handler
#pragma weak TIM1_UP_TIM10_IRQHandler      = default_handler
#pragma weak TIM1_TRG_COM_TIM11_IRQHandler = default_handler
#pragma weak TIM1_CC_IRQHandler            = default_handler
#pragma weak TIM2_IRQHandler               = default_handler
#pragma weak TIM3_IRQHandler               = default_handler
#pragma weak TIM4_IRQHandler               = default_handler
#pragma weak I2C1_EV_IRQHandler            = default_handler
#pragma weak I2C1_ER_IRQHandler            = default_handler
#pragma weak I2C2_EV_IRQHandler            = default_handler
#pragma weak I2C2_ER_IRQHandler            = default_handler
#pragma weak SPI1_IRQHandler               = default_handler
#pragma weak SPI2_IRQHandler               = default_handler
#pragma weak USART1_IRQHandler             = default_handler
#pragma weak USART2_IRQHandler             = default_handler
#pragma weak USART3_IRQHandler             = default_handler
#pragma weak EXTI15_10_IRQHandler          = default_handler
#pragma weak RTC_Alarm_IRQHandler          = default_handler
#pragma weak OTG_FS_WKUP_IRQHandler        = default_handler
#pragma weak TIM8_BRK_TIM12_IRQHandler     = default_handler
#pragma weak TIM8_UP_TIM13_IRQHandler      = default_handler
#pragma weak TIM8_TRG_COM_TIM14_IRQHandler = default_handler
#pragma weak TIM8_CC_IRQHandler            = default_handler
#pragma weak DMA1_Stream7_IRQHandler       = default_handler
#pragma weak FMC_IRQHandler                = default_handler
#pragma weak SDMMC1_IRQHandler             = default_handler
#pragma weak TIM5_IRQHandler               = default_handler
#pragma weak SPI3_IRQHandler               = default_handler
#pragma weak UART4_IRQHandler              = default_handler
#pragma weak UART5_IRQHandler              = default_handler
#pragma weak TIM6_DAC_IRQHandler           = default_handler
#pragma weak TIM7_IRQHandler               = default_handler
#pragma weak DMA2_Stream0_IRQHandler       = default_handler
#pragma weak DMA2_Stream1_IRQHandler       = default_handler
#pragma weak DMA2_Stream2_IRQHandler       = default_handler
#pragma weak DMA2_Stream3_IRQHandler       = default_handler
#pragma weak DMA2_Stream4_IRQHandler       = default_handler
#pragma weak ETH_IRQHandler                = default_handler
#pragma weak ETH_WKUP_IRQHandler           = default_handler
#pragma weak CAN2_TX_IRQHandler            = default_handler
#pragma weak CAN2_RX0_IRQHandler           = default_handler
#pragma weak CAN2_RX1_IRQHandler           = default_handler
#pragma weak CAN2_SCE_IRQHandler           = default_handler
#pragma weak OTG_FS_IRQHandler             = default_handler
#pragma weak DMA2_Stream5_IRQHandler       = default_handler
#pragma weak DMA2_Stream6_IRQHandler       = default_handler
#pragma weak DMA2_Stream7_IRQHandler       = default_handler
#pragma weak USART6_IRQHandler             = default_handler
#pragma weak I2C3_EV_IRQHandler            = default_handler
#pragma weak I2C3_ER_IRQHandler            = default_handler
#pragma weak OTG_HS_EP1_OUT_IRQHandler     = default_handler
#pragma weak OTG_HS_EP1_IN_IRQHandler      = default_handler
#pragma weak OTG_HS_WKUP_IRQHandler        = default_handler
#pragma weak OTG_HS_IRQHandler             = default_handler
#pragma weak DCMI_IRQHandler               = default_handler
#pragma weak RNG_IRQHandler                = default_handler
#pragma weak FPU_IRQHandler                = default_handler
#pragma weak UART7_IRQHandler              = default_handler
#pragma weak UART8_IRQHandler              = default_handler
#pragma weak SPI4_IRQHandler               = default_handler
#pragma weak SPI5_IRQHandler               = default_handler
#pragma weak SPI6_IRQHandler               = default_handler
#pragma weak SAI1_IRQHandler               = default_handler
#pragma weak LTDC_IRQHandler               = default_handler
#pragma weak LTDC_ER_IRQHandler            = default_handler
#pragma weak DMA2D_IRQHandler              = default_handler
#pragma weak SAI2_IRQHandler               = default_handler
#pragma weak QUADSPI_IRQHandler            = default_handler
#pragma weak LPTIM1_IRQHandler             = default_handler
#pragma weak CEC_IRQHandler                = default_handler
#pragma weak I2C4_EV_IRQHandler            = default_handler
#pragma weak I2C4_ER_IRQHandler            = default_handler
#pragma weak SPDIF_RX_IRQHandler           = default_handler

#else // NDEBUG

WEAK void WWDG_IRQHandler               ()  { default_handler(); }
WEAK void PVD_IRQHandler                ()  { default_handler(); }
WEAK void TAMP_STAMP_IRQHandler         ()  { default_handler(); }
WEAK void RTC_WKUP_IRQHandler           ()  { default_handler(); }
WEAK void FLASH_IRQHandler              ()  { default_handler(); }
WEAK void RCC_IRQHandler                ()  { default_handler(); }
WEAK void EXTI0_IRQHandler              ()  { default_handler(); }
WEAK void EXTI1_IRQHandler              ()  { default_handler(); }
WEAK void EXTI2_IRQHandler              ()  { default_handler(); }
WEAK void EXTI3_IRQHandler              ()  { default_handler(); }
WEAK void EXTI4_IRQHandler              ()  { default_handler(); }
WEAK void DMA1_Stream0_IRQHandler       ()  { default_handler(); }
WEAK void DMA1_Stream1_IRQHandler       ()  { default_handler(); }
WEAK void DMA1_Stream2_IRQHandler       ()  { default_handler(); }
WEAK void DMA1_Stream3_IRQHandler       ()  { default_handler(); }
WEAK void DMA1_Stream4_IRQHandler       ()  { default_handler(); }
WEAK void DMA1_Stream5_IRQHandler       ()  { default_handler(); }
WEAK void DMA1_Stream6_IRQHandler       ()  { default_handler(); }
WEAK void ADC_IRQHandler                ()  { default_handler(); }
WEAK void CAN1_TX_IRQHandler            ()  { default_handler(); }
WEAK void CAN1_RX0_IRQHandler           ()  { default_handler(); }
WEAK void CAN1_RX1_IRQHandler           ()  { default_handler(); }
WEAK void CAN1_SCE_IRQHandler           ()  { default_handler(); }
WEAK void EXTI9_5_IRQHandler            ()  { default_handler(); }
WEAK void TIM1_BRK_TIM9_IRQHandler      ()  { default_handler(); }
WEAK void TIM1_UP_TIM10_IRQHandler      ()  { default_handler(); }
WEAK void TIM1_TRG_COM_TIM11_IRQHandler ()  { default_handler(); }
WEAK void TIM1_CC_IRQHandler            ()  { default_handler(); }
WEAK void TIM2_IRQHandler               ()  { default_handler(); }
WEAK void TIM3_IRQHandler               ()  { default_handler(); }
WEAK void TIM4_IRQHandler               ()  { default_handler(); }
WEAK void I2C1_EV_IRQHandler            ()  { default_handler(); }
WEAK void I2C1_ER_IRQHandler            ()  { default_handler(); }
WEAK void I2C2_EV_IRQHandler            ()  { default_handler(); }
WEAK void I2C2_ER_IRQHandler            ()  { default_handler(); }
WEAK void SPI1_IRQHandler               ()  { default_handler(); }
WEAK void SPI2_IRQHandler               ()  { default_handler(); }
WEAK void USART1_IRQHandler             ()  { default_handler(); }
WEAK void USART2_IRQHandler             ()  { default_handler(); }
WEAK void USART3_IRQHandler             ()  { default_handler(); }
WEAK void EXTI15_10_IRQHandler          ()  { default_handler(); }
WEAK void RTC_Alarm_IRQHandler          ()  { default_handler(); }
WEAK void OTG_FS_WKUP_IRQHandler        ()  { default_handler(); }
WEAK void TIM8_BRK_TIM12_IRQHandler     ()  { default_handler(); }
WEAK void TIM8_UP_TIM13_IRQHandler      ()  { default_handler(); }
WEAK void TIM8_TRG_COM_TIM14_IRQHandler ()  { default_handler(); }
WEAK void TIM8_CC_IRQHandler            ()  { default_handler(); }
WEAK void DMA1_Stream7_IRQHandler       ()  { default_handler(); }
WEAK void FMC_IRQHandler                ()  { default_handler(); }
WEAK void SDMMC1_IRQHandler             ()  { default_handler(); }
WEAK void TIM5_IRQHandler               ()  { default_handler(); }
WEAK void SPI3_IRQHandler               ()  { default_handler(); }
WEAK void UART4_IRQHandler              ()  { default_handler(); }
WEAK void UART5_IRQHandler              ()  { default_handler(); }
WEAK void TIM6_DAC_IRQHandler           ()  { default_handler(); }
WEAK void TIM7_IRQHandler               ()  { default_handler(); }
WEAK void DMA2_Stream0_IRQHandler       ()  { default_handler(); }
WEAK void DMA2_Stream1_IRQHandler       ()  { default_handler(); }
WEAK void DMA2_Stream2_IRQHandler       ()  { default_handler(); }
WEAK void DMA2_Stream3_IRQHandler       ()  { default_handler(); }
WEAK void DMA2_Stream4_IRQHandler       ()  { default_handler(); }
WEAK void ETH_IRQHandler                ()  { default_handler(); }
WEAK void ETH_WKUP_IRQHandler           ()  { default_handler(); }
WEAK void CAN2_TX_IRQHandler            ()  { default_handler(); }
WEAK void CAN2_RX0_IRQHandler           ()  { default_handler(); }
WEAK void CAN2_RX1_IRQHandler           ()  { default_handler(); }
WEAK void CAN2_SCE_IRQHandler           ()  { default_handler(); }
WEAK void OTG_FS_IRQHandler             ()  { default_handler(); }
WEAK void DMA2_Stream5_IRQHandler       ()  { default_handler(); }
WEAK void DMA2_Stream6_IRQHandler       ()  { default_handler(); }
WEAK void DMA2_Stream7_IRQHandler       ()  { default_handler(); }
WEAK void USART6_IRQHandler             ()  { default_handler(); }
WEAK void I2C3_EV_IRQHandler            ()  { default_handler(); }
WEAK void I2C3_ER_IRQHandler            ()  { default_handler(); }
WEAK void OTG_HS_EP1_OUT_IRQHandler     ()  { default_handler(); }
WEAK void OTG_HS_EP1_IN_IRQHandler      ()  { default_handler(); }
WEAK void OTG_HS_WKUP_IRQHandler        ()  { default_handler(); }
WEAK void OTG_HS_IRQHandler             ()  { default_handler(); }
WEAK void DCMI_IRQHandler               ()  { default_handler(); }
WEAK void RNG_IRQHandler                ()  { default_handler(); }
WEAK void FPU_IRQHandler                ()  { default_handler(); }
WEAK void UART7_IRQHandler              ()  { default_handler(); }
WEAK void UART8_IRQHandler              ()  { default_handler(); }
WEAK void SPI4_IRQHandler               ()  { default_handler(); }
WEAK void SPI5_IRQHandler               ()  { default_handler(); }
WEAK void SPI6_IRQHandler               ()  { default_handler(); }
WEAK void SAI1_IRQHandler               ()  { default_handler(); }
WEAK void LTDC_IRQHandler               ()  { default_handler(); }
WEAK void LTDC_ER_IRQHandler            ()  { default_handler(); }
WEAK void DMA2D_IRQHandler              ()  { default_handler(); }
WEAK void SAI2_IRQHandler               ()  { default_handler(); }
WEAK void QUADSPI_IRQHandler            ()  { default_handler(); }
WEAK void LPTIM1_IRQHandler             ()  { default_handler(); }
WEAK void CEC_IRQHandler                ()  { default_handler(); }
WEAK void I2C4_EV_IRQHandler            ()  { default_handler(); }
WEAK void I2C4_ER_IRQHandler            ()  { default_handler(); }
WEAK void SPDIF_RX_IRQHandler           ()  { default_handler(); }

#endif // NDEBUG
//------------------------------------------------------------------------------
