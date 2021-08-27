# Warning!
Use bit WDG_SW in option byte to enable the watchdog by hardware. It doesn't start by any routines in code!
You can do it easyly using STM32 ST-LINK Utility via ST-LINK. They say STM32 Flash Loader Demonstartor also can modify
option byte. You don't need ST-LINK. Instead of it you write the option byte via serial port.