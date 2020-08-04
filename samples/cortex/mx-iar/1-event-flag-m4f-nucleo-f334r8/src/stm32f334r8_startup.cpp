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
    IRQ_DefaultHandler,                                     // MemManage    4
    IRQ_DefaultHandler,                                     // BusFault     5
    IRQ_DefaultHandler,                                     // UsageFault   6
    Reserved_DefaultHandler,                                // Reserved     7
    Reserved_DefaultHandler,                                // Reserved     8
    Reserved_DefaultHandler,                                // Reserved     9
    Reserved_DefaultHandler,                                // Reserved     10
    SVC_DefaultHandler,                                     // SVC          11
    Reserved_DefaultHandler,                                // Reserved     12
    Reserved_DefaultHandler,                                // Reserved     13
    PendSV_Handler,                                         // PendSV       14
    SysTick_Handler,                                        // SysTick      15
    // see RM0364 to fill vector table with your driver handlers
    // For example, instead of IRQ_DefaultHandler you can write^
    // RtcDriver::irqHandler. Where irqHandler is a static member of class RtcDriver
    // You may not user [extern "C"] in this case
    IRQ_DefaultHandler,                                     // IRQ0         16 (
    IRQ_DefaultHandler,                                     // IRQ1         17 (
    IRQ_DefaultHandler,                                     // IRQ2         18 (
    IRQ_DefaultHandler,                                     // IRQ3         19 (
    IRQ_DefaultHandler,                                     // IRQ4         20 (
    IRQ_DefaultHandler,                                     // IRQ5         21 (
    IRQ_DefaultHandler,                                     // IRQ6         22 (
    IRQ_DefaultHandler,                                     // IRQ7         23 (
    IRQ_DefaultHandler,                                     // IRQ8         24 (
    IRQ_DefaultHandler,                                     // IRQ9         25 (
    IRQ_DefaultHandler,                                     // IRQ10        26 (
    IRQ_DefaultHandler,                                     // IRQ11        27 (
    IRQ_DefaultHandler,                                     // IRQ12        28 (
    IRQ_DefaultHandler,                                     // IRQ13        29 (
    IRQ_DefaultHandler,                                     // IRQ14        30 (
    IRQ_DefaultHandler,                                     // IRQ15        31 (
    IRQ_DefaultHandler,                                     // IRQ16        32 (
    IRQ_DefaultHandler,                                     // IRQ17        33 (
    IRQ_DefaultHandler,                                     // IRQ18        34 (
    IRQ_DefaultHandler,                                     // IRQ19        35 (
    IRQ_DefaultHandler,                                     // IRQ20        36 (
    IRQ_DefaultHandler,                                     // IRQ21        37 (
    IRQ_DefaultHandler,                                     // IRQ22        38 (
    IRQ_DefaultHandler,                                     // IRQ23        39 (
    IRQ_DefaultHandler,                                     // IRQ24        40 (
    IRQ_DefaultHandler,                                     // IRQ24        41 (
    IRQ_DefaultHandler,                                     // IRQ24        42 (
    IRQ_DefaultHandler,                                     // IRQ25        43 (
    IRQ_DefaultHandler,                                     // IRQ26        44 (
    IRQ_DefaultHandler,                                     // IRQ27        45 (
    IRQ_DefaultHandler,                                     // IRQ28        46 (
    IRQ_DefaultHandler,                                     // IRQ29        47 (
};
