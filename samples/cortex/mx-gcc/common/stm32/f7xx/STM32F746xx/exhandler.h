//******************************************************************************
//*
//*      STM32F746XX exception/intrrupt handlers stuff header file
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

#ifndef EXHANDLER_H
#define EXHANDLER_H

//------------------------------------------------------------------------------
//
//   Weak attribute allows to replace default handler with the user's one
//
#define WEAK __attribute__ ((weak))
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
extern unsigned long __top_of_stack[];

//------------------------------------------------------------------------------
//
//   Vector table item. Can be pointer to function or plain address value
//
typedef void (*intfun_t)();
typedef struct
{
    unsigned long *tos;
    intfun_t      vectors[113];
}
__vector_table_t;

//------------------------------------------------------------------------------
//
//   Startup handler
//
void Reset_Handler();

//------------------------------------------------------------------------------
//
//   Cortex-M internal exceptions
//
WEAK void NMI_Handler();
WEAK void HardFault_Handler();
WEAK void MemManage_Handler();
WEAK void BusFault_Handler();
WEAK void UsageFault_Handler();
WEAK void SVC_Handler();
WEAK void DebugMon_Handler();
WEAK void PendSV_Handler();
WEAK void SysTick_Handler();

//------------------------------------------------------------------------------
//
//   Controller specific peripheral interrupts
//
WEAK void WWDG_IRQHandler();
WEAK void PVD_IRQHandler();
WEAK void TAMP_STAMP_IRQHandler();
WEAK void RTC_WKUP_IRQHandler();
WEAK void FLASH_IRQHandler();
WEAK void RCC_IRQHandler();
WEAK void EXTI0_IRQHandler();
WEAK void EXTI1_IRQHandler();
WEAK void EXTI2_IRQHandler();
WEAK void EXTI3_IRQHandler();
WEAK void EXTI4_IRQHandler();
WEAK void DMA1_Stream0_IRQHandler();
WEAK void DMA1_Stream1_IRQHandler();
WEAK void DMA1_Stream2_IRQHandler();
WEAK void DMA1_Stream3_IRQHandler();
WEAK void DMA1_Stream4_IRQHandler();
WEAK void DMA1_Stream5_IRQHandler();
WEAK void DMA1_Stream6_IRQHandler();
WEAK void ADC_IRQHandler();
WEAK void CAN1_TX_IRQHandler();
WEAK void CAN1_RX0_IRQHandler();
WEAK void CAN1_RX1_IRQHandler();
WEAK void CAN1_SCE_IRQHandler();
WEAK void EXTI9_5_IRQHandler();
WEAK void TIM1_BRK_TIM9_IRQHandler();
WEAK void TIM1_UP_TIM10_IRQHandler();
WEAK void TIM1_TRG_COM_TIM11_IRQHandler();
WEAK void TIM1_CC_IRQHandler();
WEAK void TIM2_IRQHandler();
WEAK void TIM3_IRQHandler();
WEAK void TIM4_IRQHandler();
WEAK void I2C1_EV_IRQHandler();
WEAK void I2C1_ER_IRQHandler();
WEAK void I2C2_EV_IRQHandler();
WEAK void I2C2_ER_IRQHandler();
WEAK void SPI1_IRQHandler();
WEAK void SPI2_IRQHandler();
WEAK void USART1_IRQHandler();
WEAK void USART2_IRQHandler();
WEAK void USART3_IRQHandler();
WEAK void EXTI15_10_IRQHandler();
WEAK void RTC_Alarm_IRQHandler();
WEAK void OTG_FS_WKUP_IRQHandler();
WEAK void TIM8_BRK_TIM12_IRQHandler();
WEAK void TIM8_UP_TIM13_IRQHandler();
WEAK void TIM8_TRG_COM_TIM14_IRQHandler();
WEAK void TIM8_CC_IRQHandler();
WEAK void DMA1_Stream7_IRQHandler();
WEAK void FMC_IRQHandler();
WEAK void SDMMC1_IRQHandler();
WEAK void TIM5_IRQHandler();
WEAK void SPI3_IRQHandler();
WEAK void UART4_IRQHandler();
WEAK void UART5_IRQHandler();
WEAK void TIM6_DAC_IRQHandler();
WEAK void TIM7_IRQHandler();
WEAK void DMA2_Stream0_IRQHandler();
WEAK void DMA2_Stream1_IRQHandler();
WEAK void DMA2_Stream2_IRQHandler();
WEAK void DMA2_Stream3_IRQHandler();
WEAK void DMA2_Stream4_IRQHandler();
WEAK void ETH_IRQHandler();
WEAK void ETH_WKUP_IRQHandler();
WEAK void CAN2_TX_IRQHandler();
WEAK void CAN2_RX0_IRQHandler();
WEAK void CAN2_RX1_IRQHandler();
WEAK void CAN2_SCE_IRQHandler();
WEAK void OTG_FS_IRQHandler();
WEAK void DMA2_Stream5_IRQHandler();
WEAK void DMA2_Stream6_IRQHandler();
WEAK void DMA2_Stream7_IRQHandler();
WEAK void USART6_IRQHandler();
WEAK void I2C3_EV_IRQHandler();
WEAK void I2C3_ER_IRQHandler();
WEAK void OTG_HS_EP1_OUT_IRQHandler();
WEAK void OTG_HS_EP1_IN_IRQHandler();
WEAK void OTG_HS_WKUP_IRQHandler();
WEAK void OTG_HS_IRQHandler();
WEAK void DCMI_IRQHandler();
WEAK void RNG_IRQHandler();
WEAK void FPU_IRQHandler();
WEAK void UART7_IRQHandler();
WEAK void UART8_IRQHandler();
WEAK void SPI4_IRQHandler();
WEAK void SPI5_IRQHandler();
WEAK void SPI6_IRQHandler();
WEAK void SAI1_IRQHandler();
WEAK void LTDC_IRQHandler();
WEAK void LTDC_ER_IRQHandler();
WEAK void DMA2D_IRQHandler();
WEAK void SAI2_IRQHandler();
WEAK void QUADSPI_IRQHandler();
WEAK void LPTIM1_IRQHandler();
WEAK void CEC_IRQHandler();
WEAK void I2C4_EV_IRQHandler();
WEAK void I2C4_ER_IRQHandler();
WEAK void SPDIF_RX_IRQHandler();
//------------------------------------------------------------------------------

#endif // EXHANDLER_H

//------------------------------------------------------------------------------
