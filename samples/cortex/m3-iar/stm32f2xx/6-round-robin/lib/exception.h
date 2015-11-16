//******************************************************************************
//*
//*      Project:   Any
//*
//*      File:      Exceptions and Intrrupt handler stuff header file
//*
//*      Version 1.0
//*
//*      Copyright (c) 2012, Harry E. Zhurov
//*
//*
//------------------------------------------------------------------------------


#ifndef EXCEPTION_H
#define EXCEPTION_H

//------------------------------------------------------------------------------
//
//   Weak attribute allows to replace default handler with the user's one
//
#if defined   ( __CC_ARM   )
  #define WEAK __attribute__ ((weak))
#elif defined ( __ICCARM__ )
  #define WEAK __weak
#elif defined (  __GNUC__  )
  #define WEAK __attribute__ ((weak))
#endif

//------------------------------------------------------------------------------

extern "C" 
{

void __iar_program_start();

//------------------------------------------------------------------------------

/****** Undefined (not implemented) interrupts **********************/

extern WEAK void IrqHandlerNotUsed();

/****** CM3 internal exceptions *************************************/

extern WEAK void NMI_Handler();
extern WEAK void HardFault_Handler();
extern WEAK void MemManage_Handler();
extern WEAK void BusFault_Handler();
extern WEAK void UsageFault_Handler();
extern WEAK void SVC_Handler();
extern WEAK void DebugMon_Handler();
extern WEAK void PendSV_Handler();
extern WEAK void SysTick_Handler();

/****** Controller specific peripheral interrupts *******************/

extern WEAK void WWDG_IRQHandler();
extern WEAK void PVD_IRQHandler();
extern WEAK void TAMPER_IRQHandler();
extern WEAK void RTC_IRQHandler();
extern WEAK void FLASH_IRQHandler();
extern WEAK void RCC_IRQHandler();
extern WEAK void EXTI0_IRQHandler();
extern WEAK void EXTI1_IRQHandler();
extern WEAK void EXTI2_IRQHandler();
extern WEAK void EXTI3_IRQHandler();
extern WEAK void EXTI4_IRQHandler();
extern WEAK void DMA1_Channel1_IRQHandler();
extern WEAK void DMA1_Channel2_IRQHandler();
extern WEAK void DMA1_Channel3_IRQHandler();
extern WEAK void DMA1_Channel4_IRQHandler();
extern WEAK void DMA1_Channel5_IRQHandler();
extern WEAK void DMA1_Channel6_IRQHandler();
extern WEAK void DMA1_Channel7_IRQHandler();
extern WEAK void ADC1_2_IRQHandler();
extern WEAK void CAN1_TX_IRQHandler();
extern WEAK void CAN1_RX0_IRQHandler();
extern WEAK void CAN1_RX1_IRQHandler();
extern WEAK void CAN1_SCE_IRQHandler();
extern WEAK void EXTI9_5_IRQHandler();
extern WEAK void TIM1_BRK_IRQHandler();
extern WEAK void TIM1_UP_IRQHandler();
extern WEAK void TIM1_TRG_COM_IRQHandler();
extern WEAK void TIM1_CC_IRQHandler();
extern WEAK void TIM2_IRQHandler();
extern WEAK void TIM3_IRQHandler();
extern WEAK void TIM4_IRQHandler();
extern WEAK void I2C1_EV_IRQHandler();
extern WEAK void I2C1_ER_IRQHandler();
extern WEAK void I2C2_EV_IRQHandler();
extern WEAK void I2C2_ER_IRQHandler();
extern WEAK void SPI1_IRQHandler();
extern WEAK void SPI2_IRQHandler();
extern WEAK void USART1_IRQHandler();
extern WEAK void USART2_IRQHandler();
extern WEAK void USART3_IRQHandler();
extern WEAK void EXTI15_10_IRQHandler();
extern WEAK void RTCAlarm_IRQHandler();
extern WEAK void OTG_FS_WKUP_IRQHandler();
extern WEAK void TIM8_BRK_IRQ_Handler();
extern WEAK void TIM8_UP_IRQ_Handler();
extern WEAK void TIM8_TRG_IRQ_Handler();
extern WEAK void TIM8_CC_IRQ_Handler();
extern WEAK void DMA1_Channel8_IRQHandler();
extern WEAK void FSMC_IRQHandler();
extern WEAK void SDIO_IRQHandler();
extern WEAK void TIM5_IRQHandler();
extern WEAK void SPI3_IRQHandler();
extern WEAK void USART4_IRQHandler();
extern WEAK void USART5_IRQHandler();
extern WEAK void TIM6_IRQHandler();
extern WEAK void TIM7_IRQHandler();
extern WEAK void DMA2_Channel1_IRQHandler();
extern WEAK void DMA2_Channel2_IRQHandler();
extern WEAK void DMA2_Channel3_IRQHandler();
extern WEAK void DMA2_Channel4_IRQHandler();
extern WEAK void DMA2_Channel5_IRQHandler();
extern WEAK void ETH_IRQHandler();
extern WEAK void ETH_WKUP_IRQHandler();
extern WEAK void CAN2_TX_IRQHandler();
extern WEAK void CAN2_RX0_IRQHandler();
extern WEAK void CAN2_RX1_IRQHandler();
extern WEAK void CAN2_SCE_IRQHandler();
extern WEAK void OTG_FS_IRQHandler();
extern WEAK void DMA2_Channel6_IRQHandler();
extern WEAK void DMA2_Channel7_IRQHandler();
extern WEAK void DMA2_Channel8_IRQHandler();
extern WEAK void USART6_IRQHandler();
extern WEAK void I2C3_EV_IRQHandler();
extern WEAK void I2C3_ER_IRQHandler();
extern WEAK void OTG_HS_EP1_OUT_IRQHandler();
extern WEAK void OTG_HS_EP1_IN_IRQHandler();
extern WEAK void OTG_HS_WKUP_IRQHandler();
extern WEAK void OTG_HS_IRQHandler();
extern WEAK void DCMI_IRQHandler();
extern WEAK void CRYP_IRQHandler();
extern WEAK void HASH_RNG_IRQHandler();

}

//------------------------------------------------------------------------------

#endif // EXCEPTION_H 

//------------------------------------------------------------------------------
