//******************************************************************************
//*
//*      Project:   Any
//*
//*      File:      Default exception/interrupt handlers
//*
//*      Version 1.0
//*
//*      Copyright (c) 2012-2016, Harry E. Zhurov
//*
//*
//------------------------------------------------------------------------------

                  
#include "exception.h"

extern "C" 
{

//------------------------------------------------------------------------------
static void default_handler() 
{
    // In case we received a hard fault because
    // of a breakpoint instruction, we return.
    // This may happen with the IAR workbench when semihosting is used
    //

#define NVIC_HFSR (*((volatile unsigned long *)(0xE000ED2C)))
     
//  if( NVIC_HFSR & 1uL << 31 )
//  {
//      NVIC_HFSR |= (1uL << 31);
//      return;
//  }
    
    for(;;) 
    { 
    }
}

//------------------------------------------------------------------------------
//
//   Default exception handlers
//
WEAK void NMI_Handler       ()  { default_handler(); }
WEAK void HardFault_Handler ()  { default_handler(); }
WEAK void MemManage_Handler ()  { default_handler(); }
WEAK void BusFault_Handler  ()  { default_handler(); }
WEAK void UsageFault_Handler()  { default_handler(); }
WEAK void SVC_Handler       ()  { default_handler(); }
WEAK void DebugMon_Handler  ()  { default_handler(); }
WEAK void PendSV_Handler    ()  { default_handler(); }
WEAK void SysTick_Handler   ()  { default_handler(); }

//------------------------------------------------------------------------------
//
//   Default interrupt handlers
//
WEAK void WWDG_IRQHandler          ()  { default_handler(); }
WEAK void PVD_IRQHandler           ()  { default_handler(); }
WEAK void TAMPER_IRQHandler        ()  { default_handler(); }
WEAK void RTC_IRQHandler           ()  { default_handler(); }
WEAK void FLASH_IRQHandler         ()  { default_handler(); }
WEAK void RCC_IRQHandler           ()  { default_handler(); }
WEAK void EXTI0_IRQHandler         ()  { default_handler(); }
WEAK void EXTI1_IRQHandler         ()  { default_handler(); }
WEAK void EXTI2_IRQHandler         ()  { default_handler(); }
WEAK void EXTI3_IRQHandler         ()  { default_handler(); }
WEAK void EXTI4_IRQHandler         ()  { default_handler(); }
WEAK void DMA1_Channel1_IRQHandler ()  { default_handler(); }
WEAK void DMA1_Channel2_IRQHandler ()  { default_handler(); }
WEAK void DMA1_Channel3_IRQHandler ()  { default_handler(); }
WEAK void DMA1_Channel4_IRQHandler ()  { default_handler(); }
WEAK void DMA1_Channel5_IRQHandler ()  { default_handler(); }
WEAK void DMA1_Channel6_IRQHandler ()  { default_handler(); }
WEAK void DMA1_Channel7_IRQHandler ()  { default_handler(); }
WEAK void ADC1_2_IRQHandler        ()  { default_handler(); }
WEAK void CAN1_TX_IRQHandler       ()  { default_handler(); }
WEAK void CAN1_RX0_IRQHandler      ()  { default_handler(); }
WEAK void CAN1_RX1_IRQHandler      ()  { default_handler(); }
WEAK void CAN1_SCE_IRQHandler      ()  { default_handler(); }
WEAK void EXTI9_5_IRQHandler       ()  { default_handler(); }
WEAK void TIM1_BRK_IRQHandler      ()  { default_handler(); }
WEAK void TIM1_UP_IRQHandler       ()  { default_handler(); }
WEAK void TIM1_TRG_COM_IRQHandler  ()  { default_handler(); }
WEAK void TIM1_CC_IRQHandler       ()  { default_handler(); }
WEAK void TIM2_IRQHandler          ()  { default_handler(); }
WEAK void TIM3_IRQHandler          ()  { default_handler(); }
WEAK void TIM4_IRQHandler          ()  { default_handler(); }
WEAK void I2C1_EV_IRQHandler       ()  { default_handler(); }
WEAK void I2C1_ER_IRQHandler       ()  { default_handler(); }
WEAK void I2C2_EV_IRQHandler       ()  { default_handler(); }
WEAK void I2C2_ER_IRQHandler       ()  { default_handler(); }
WEAK void SPI1_IRQHandler          ()  { default_handler(); }
WEAK void SPI2_IRQHandler          ()  { default_handler(); }
WEAK void USART1_IRQHandler        ()  { default_handler(); }
WEAK void USART2_IRQHandler        ()  { default_handler(); }
WEAK void USART3_IRQHandler        ()  { default_handler(); }
WEAK void EXTI15_10_IRQHandler     ()  { default_handler(); }
WEAK void RTCAlarm_IRQHandler      ()  { default_handler(); }
WEAK void OTG_FS_WKUP_IRQHandler   ()  { default_handler(); }
WEAK void TIM8_BRK_IRQ_Handler     ()  { default_handler(); }
WEAK void TIM8_UP_IRQ_Handler      ()  { default_handler(); }
WEAK void TIM8_TRG_IRQ_Handler     ()  { default_handler(); }
WEAK void TIM8_CC_IRQ_Handler      ()  { default_handler(); }
WEAK void DMA1_Channel8_IRQHandler ()  { default_handler(); }
WEAK void FSMC_IRQHandler          ()  { default_handler(); }
WEAK void SDIO_IRQHandler          ()  { default_handler(); }
WEAK void TIM5_IRQHandler          ()  { default_handler(); }
WEAK void SPI3_IRQHandler          ()  { default_handler(); }
WEAK void USART4_IRQHandler        ()  { default_handler(); }
WEAK void USART5_IRQHandler        ()  { default_handler(); }
WEAK void TIM6_IRQHandler          ()  { default_handler(); }
WEAK void TIM7_IRQHandler          ()  { default_handler(); }
WEAK void DMA2_Channel1_IRQHandler ()  { default_handler(); }
WEAK void DMA2_Channel2_IRQHandler ()  { default_handler(); }
WEAK void DMA2_Channel3_IRQHandler ()  { default_handler(); }
WEAK void DMA2_Channel4_IRQHandler ()  { default_handler(); }
WEAK void DMA2_Channel5_IRQHandler ()  { default_handler(); }
WEAK void ETH_IRQHandler           ()  { default_handler(); }
WEAK void ETH_WKUP_IRQHandler      ()  { default_handler(); }
WEAK void CAN2_TX_IRQHandler       ()  { default_handler(); }
WEAK void CAN2_RX0_IRQHandler      ()  { default_handler(); }
WEAK void CAN2_RX1_IRQHandler      ()  { default_handler(); }
WEAK void CAN2_SCE_IRQHandler      ()  { default_handler(); }
WEAK void OTG_FS_IRQHandler        ()  { default_handler(); }
WEAK void DMA2_Channel6_IRQHandler ()  { default_handler(); }
WEAK void DMA2_Channel7_IRQHandler ()  { default_handler(); }
WEAK void DMA2_Channel8_IRQHandler ()  { default_handler(); }
WEAK void USART6_IRQHandler        ()  { default_handler(); }
WEAK void I2C3_EV_IRQHandler       ()  { default_handler(); }
WEAK void I2C3_ER_IRQHandler       ()  { default_handler(); }
WEAK void OTG_HS_EP1_OUT_IRQHandler()  { default_handler(); }
WEAK void OTG_HS_EP1_IN_IRQHandler ()  { default_handler(); }
WEAK void OTG_HS_WKUP_IRQHandler   ()  { default_handler(); }
WEAK void OTG_HS_IRQHandler        ()  { default_handler(); }
WEAK void DCMI_IRQHandler          ()  { default_handler(); }
WEAK void CRYP_IRQHandler          ()  { default_handler(); }
WEAK void HASH_RNG_IRQHandler      ()  { default_handler(); }
WEAK void IrqHandlerNotUsed        ()  { default_handler(); }

}

//------------------------------------------------------------------------------

                                           



