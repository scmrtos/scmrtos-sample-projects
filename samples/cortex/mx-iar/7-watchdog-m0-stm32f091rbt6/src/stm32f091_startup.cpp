typedef union VectorEntry_t {
    void ( *pHandler )();
    void * pStack;
}VectorEntry_t;

// IAR default entry
extern "C" void __iar_program_start();
// scmRTOS irq handlers
extern "C" void PendSV_Handler();
extern "C" void SysTick_Handler();

static __noreturn void reset() {
    __iar_program_start();
    while (1);
}
// These handlers do not use in the example
static void NMI_DefaultHandler() {
    while (1);
}
static void Reserved_DefaultHandler() {
    while (1);
}
static void IRQ_DefaultHandler() {
    while (1);
}
static void SVC_DefaultHandler() {
    while (1);
}

extern unsigned char CSTACK$$Limit;
#pragma location = ".intvec"
extern "C" const __root VectorEntry_t __vector_table[] = {
    {.pStack = &CSTACK$$Limit },                            // stack        0
    {.pHandler = reset        },                            // reset        1
    NMI_DefaultHandler,                                     // NMI          2
    IRQ_DefaultHandler,                                     // HardFault    3
    Reserved_DefaultHandler,                                // Reserved     4
    Reserved_DefaultHandler,                                // Reserved     5
    Reserved_DefaultHandler,                                // Reserved     6
    Reserved_DefaultHandler,                                // Reserved     7
    Reserved_DefaultHandler,                                // Reserved     8
    Reserved_DefaultHandler,                                // Reserved     9
    Reserved_DefaultHandler,                                // Reserved     10
    SVC_DefaultHandler,                                     // SVC          11
    Reserved_DefaultHandler,                                // Reserved     12
    Reserved_DefaultHandler,                                // Reserved     13
    PendSV_Handler,                                         // PendSV       14
    SysTick_Handler,                                        // SysTick      15
    // see RM9001 to fill vector table with your driver handlers
    // For example, instead of IRQ_DefaultHandler you can write^
    // RtcDriver::irqHandler. Where irqHandler is a static member of class RtcDriver
    // You may not user [extern "C"] in this case
    IRQ_DefaultHandler,                                     // IRQ0         16 (WWDG)
    IRQ_DefaultHandler,                                     // IRQ1         17 (PVD)
    IRQ_DefaultHandler,                                     // IRQ2         18 (RTC)
    IRQ_DefaultHandler,                                     // IRQ3         19 (FLASH)
    IRQ_DefaultHandler,                                     // IRQ4         20 (RCC)
    IRQ_DefaultHandler,                                     // IRQ5         21 (EXTI0_1_IRQHandler)
    IRQ_DefaultHandler,                                     // IRQ6         22 (EXTI2_3_IRQHandler)
    IRQ_DefaultHandler,                                     // IRQ7         23 (EXTI4_15_IRQHandler)
    IRQ_DefaultHandler,                                     // IRQ8         24 (TS_IRQHandler)
    IRQ_DefaultHandler,                                     // IRQ9         25 (DMA_CH1)
    IRQ_DefaultHandler,                                     // IRQ10        26 (DMA_CH2_3, DMA2_CH1_2)
    IRQ_DefaultHandler,                                     // IRQ11        27 (DMA_CH4_7, DMA2_CH3_5)
    IRQ_DefaultHandler,                                     // IRQ12        28 (ADC1_COMP_IRQHandler)
    IRQ_DefaultHandler,                                     // IRQ13        29 (TIM1_BRK_UP_TRG_COM)
    IRQ_DefaultHandler,                                     // IRQ14        30 (TIM1_CC)
    IRQ_DefaultHandler,                                     // IRQ15        31 (TIM2)
    IRQ_DefaultHandler,                                     // IRQ16        32 (TIM3)
    IRQ_DefaultHandler,                                     // IRQ17        33 (TIM6_DAC_IRQHandler)
    IRQ_DefaultHandler,                                     // IRQ18        34 (TIM7)
    IRQ_DefaultHandler,                                     // IRQ19        35 (TIM14)
    IRQ_DefaultHandler,                                     // IRQ20        36 (TIM15)
    IRQ_DefaultHandler,                                     // IRQ21        37 (TIM16)
    IRQ_DefaultHandler,                                     // IRQ22        38 (TIM17)
    IRQ_DefaultHandler,                                     // IRQ23        39 (I2C1)
    IRQ_DefaultHandler,                                     // IRQ24        40 (I2C2)
    IRQ_DefaultHandler,                                     // IRQ24        41 (SPI1)
    IRQ_DefaultHandler,                                     // IRQ24        42 (SPI2)
    IRQ_DefaultHandler,                                     // IRQ25        43 (USART1)
    IRQ_DefaultHandler,                                     // IRQ26        44 (USART2)
    IRQ_DefaultHandler,                                     // IRQ27        45 (USART3_8)
    IRQ_DefaultHandler,                                     // IRQ28        46 (CEC_CAN)IRQHandler)
    IRQ_DefaultHandler,                                     // IRQ29        47 (USB)
};
