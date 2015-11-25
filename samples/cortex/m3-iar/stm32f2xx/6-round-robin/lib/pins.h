/**
*  GPIO pin manipulation class template for STM32F4xx.
*
*  Copyright (c) 2012 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
*
*  Inspired by AVR macros from Askold Volkov
*
*
* USAGE:
*
*   I. Declare pin typedef:
* typedef Pin<'A', 5, 'H', PIN_SPEED_50MHZ> PA5;    // PA5, active level = high, pin speed = 50MHZ
* typedef Pin<'A', 6> PA6;                          // PA6, default active level ('H'), default pin speed (PIN_SPEED_2MHZ)
* typedef Pin<'B', 12, 'L'> PB12;                   // PB12, active level = low, default pin speed (PIN_SPEED_2MHZ)
*
*   II. Set pin mode:
* PA5::Mode(OUTPUT);       // configure PA5 as output (push-pull, 50MHz)
* PA5::Direct(OUTPUT);     // the same.
* PA6::Mode(INPUT);        // configure PA6 as input floating (use object and "." notation)
* PB12::Mode(OUTPUT);      // configure PB12 as output
* TX::Mode(ALT_OUTPUT);    // configure TX as alternate output push-pull
*                          // (see PinConfig enum for list of all pin modes)
*
*   III. Manipulate pin:
* PA5::On();               // switch PA5 to active state (H)
* PB12::On();              // switch PB12 to active state (L)
* PA5::Off();              // switch PA5 to inactive state (L)
* PB12::Cpl();             // invert PB12 output
*
*   IV. Check pin state:
* if (PA5::Signalled())     // returns non-zero if pin input = active state (H for PA5)
* if (PB12::Latched())      // returns non-zero if pin output = active state (L for PB12)
*
*   V. Use pin registers uniformly:
* locked = PA5::GPIOx->LCKR & PA5::mask; // read PA5 lock state.
*
*   It is also possible to declare object of defined type:
* PA5 PinA5;
* In this case, one can use "dot" notation to call object functions, i.e.
* PinA5.On();
* PB12.Mode(INPUT);
* Note : using objects instead of types can (in some cases) increase memory consumption.
*
*
*  Public domain, AS IS.
*
*/

#ifndef PIN_STM32F4XX_H_
#define PIN_STM32F4XX_H_

#include <stddef.h>

#ifndef INLINE
#define INLINE _Pragma("inline=forced") inline
#endif

namespace {

typedef struct
{
  volatile uint32_t MODER;    ///!< GPIO port mode register
  volatile uint32_t OTYPER;   ///!< GPIO port output type register
  volatile uint32_t OSPEEDR;  ///!< GPIO port output speed register
  volatile uint32_t PUPDR;    ///!< GPIO port pull-up/pull-down register
  volatile uint32_t IDR;      ///!< GPIO port input data register
  volatile uint32_t ODR;      ///!< GPIO port output data register
  volatile uint32_t BSRR;     ///!< GPIO port bit set/reset low register
  volatile uint32_t LCKR;     ///!< GPIO port configuration lock register
  volatile uint32_t AFR[2];   ///!< GPIO alternate function registers
} GPIOxTypeDef;

}

/**
 * PinConfig enumeration. Defines all possible pin configuration variants.
 */
enum PinConfig
{
    INPUT,                   ///!< input floating
    INPUT_PULLUP,            ///!< input pull-up
    INPUT_PULLDOWN,          ///!< input pull-down
    ALT_INPUT,               ///!< alternate function input
    ALT_INPUT_PULLUP,        ///!< alternate function input with pull-up
    ALT_INPUT_PULLDOWN,      ///!< alternate function input with pull-down
    ANALOG,                  ///!< analog

    OUTPUT,                  ///!< output push-pull
    OUTPUT_OD,               ///!< output open-drain
    OUTPUT_OD_PULLUP,        ///!< output open-drain pull-up
    OUTPUT_OD_PULLDOWN,      ///!< output open-drain pull-down
    ALT_OUTPUT,              ///!< alternate function output push-pull
    ALT_OUTPUT_OD,           ///!< alternate function output open-drain
    ALT_OUTPUT_OD_PULLUP,    ///!< alternate function output open-drain pull-up
    ALT_OUTPUT_OD_PULLDOWN   ///!< alternate function output open-drain pull-down
};


/**
 * PinMode enumeration. Defines all possible values for MODER register.
 */
enum PinMode
{
    MODER_INPUT  = 0,
    MODER_OUTPUT  = 1,
    MODER_ALTERNATE  = 2,
    MODER_ANALOG  = 3
};

/**
 * PullUpMode enumeration. Defines all possible values for PUPDR register.
 */
enum PullUpMode
{
    PUPDR_NONE  = 0,
    PUPDR_PULLUP = 1,
    PUPDR_PULLDOWN = 2
};

/**
 * PinSpeed enumeration. Defines all possible values for OSPEEDR register.
 */
enum PinSpeed
{
    PIN_SPEED_2MHZ = 0,
    PIN_SPEED_25MHZ = 1,
    PIN_SPEED_50MHZ = 2,
    PIN_SPEED_100MHZ = 3,
    PIN_SPEED_MASK = 3
};

/**
 * PinOutputType enumeration. Defines all possible values for OTYPER register.
 */
enum PinOutputType
{
    PUSH_PULL = 0,
    OPEN_DRAIN = 1
};



template<char port> struct port_gpio_t;

template<> struct port_gpio_t<'A'>
{
    enum { GPIOx_BASE = 0x40020000UL };    // GPIOA_BASE
};

template<> struct port_gpio_t<'B'>
{
    enum { GPIOx_BASE = 0x40020400UL };    // GPIOB_BASE
};

template<> struct port_gpio_t<'C'>
{
    enum { GPIOx_BASE = 0x40020800UL };    // GPIOC_BASE
};

template<> struct port_gpio_t<'D'>
{
    enum { GPIOx_BASE = 0x40020C00UL };    // GPIOD_BASE
};

template<> struct port_gpio_t<'E'>
{
    enum { GPIOx_BASE = 0x40021000UL };    // GPIOE_BASE
};

template<> struct port_gpio_t<'F'>
{
    enum { GPIOx_BASE = 0x40021400UL };    // GPIOF_BASE
};

template<> struct port_gpio_t<'G'>
{
    enum { GPIOx_BASE = 0x40021800UL };    // GPIOG_BASE
};

template<> struct port_gpio_t<'H'>
{
    enum { GPIOx_BASE = 0x40021C00UL };    // GPIOH_BASE
};

template<> struct port_gpio_t<'I'>
{
    enum { GPIOx_BASE = 0x40022000UL };    // GPIOI_BASE
};

template <uint32_t addr, uint32_t pin> struct BitBand
{
    #define PERIPH_BB_BASE        ((uint32_t)0x42000000)
    #define PERIPH_BASE           ((uint32_t)0x40000000) 
    enum
    {
        ADDR = addr,
        BB_ADDR  = PERIPH_BB_BASE + (addr - PERIPH_BASE) * 32 + pin * 4
    };
};

template<
    char port,
    int pin_no,
    char activestate = 'H',
    PinSpeed speed = PIN_SPEED_2MHZ
    > struct Pin;

template<char port, int pin_no, char activestate, PinSpeed speed>
struct Pin
{
    static const int pin = pin_no;
    static const int port_no = port-'A';
    static const uint32_t mask = 1UL << pin;
    static const uint32_t clearmask = 1UL << (pin + 16);
    static const uint32_t shift_x2 = pin * 2;
    static const uint32_t mask_x2 = 3UL << shift_x2;
    static const uint32_t shift_x4 = (pin % 8) << 2;
    static const uint32_t mask_x4 = 0xFUL << shift_x4;

    enum
    {
        GPIOx_BASE       = port_gpio_t<port>::GPIOx_BASE,
        IDR_BB_ADDR      = PERIPH_BB_BASE + (GPIOx_BASE + offsetof(GPIOxTypeDef, IDR) - PERIPH_BASE) * 32 + pin * 4,
        ODR_BB_ADDR      = PERIPH_BB_BASE + (GPIOx_BASE + offsetof(GPIOxTypeDef, ODR) - PERIPH_BASE) * 32 + pin * 4,

        MODER_BB_ADDR    = PERIPH_BB_BASE + (GPIOx_BASE + offsetof(GPIOxTypeDef, MODER) - PERIPH_BASE) * 32 + shift_x2 * 4,
        OTYPER_BB_ADDR   = PERIPH_BB_BASE + (GPIOx_BASE + offsetof(GPIOxTypeDef, OTYPER) - PERIPH_BASE) * 32 + pin * 4,
        OSPEEDR_BB_ADDR  = PERIPH_BB_BASE + (GPIOx_BASE + offsetof(GPIOxTypeDef, OSPEEDR) - PERIPH_BASE) * 32 + shift_x2 * 4,
        PUPDR_BB_ADDR    = PERIPH_BB_BASE + (GPIOx_BASE + offsetof(GPIOxTypeDef, PUPDR) - PERIPH_BASE) * 32 + shift_x2 * 4,

        GPIO_BB_ADDR     = PERIPH_BB_BASE + (GPIOx_BASE + offsetof(GPIOxTypeDef, MODER) - PERIPH_BASE) * 32 + shift_x2 * 4
    };

    typedef struct
    {
      volatile uint32_t MODER_BIT0;
      volatile uint32_t MODER_BIT1;
      uint32_t reserved1[(OTYPER_BB_ADDR - MODER_BB_ADDR)/4 - 2];
      volatile uint32_t OTYPER_BIT0;
      uint32_t reserved2[(OSPEEDR_BB_ADDR - OTYPER_BB_ADDR)/4 - 1];
      volatile uint32_t OSPEEDR_BIT0;
      volatile uint32_t OSPEEDR_BIT1;
      uint32_t reserved3[30];
      volatile uint32_t PUPDR_BIT0;
      volatile uint32_t PUPDR_BIT1;
      uint32_t reserved4[(IDR_BB_ADDR - PUPDR_BB_ADDR)/4 - 2];
      volatile uint32_t IDR_BIT0;
      uint32_t reserved5[31];
      volatile uint32_t ODR_BIT0;
      uint32_t reserved6[31];
      volatile uint32_t BSRR_SET;
      uint32_t reserved7[15];
      volatile uint32_t BSRR_CLR;
    } GPIOxBbBits;


    static struct
    {
        GPIOxTypeDef* operator-> () { return (GPIOxTypeDef*)GPIOx_BASE; }
    }GPIOx;

    static struct
    {
        GPIOxBbBits* operator-> () { return (GPIOxBbBits*)GPIO_BB_ADDR; }
    }BBBits;

    INLINE static void On(bool set_on=true)
    {
        (activestate == 'H') == set_on ? GPIOx->BSRR = mask : GPIOx->BSRR = clearmask;
    }
    INLINE static void OnBB(bool set_on=true)
    {
        (activestate == 'H') == set_on ? BBBits->BSRR_SET = 1 : BBBits->BSRR_CLR = 1;
    }
    INLINE static void Off() { On(false); }
    INLINE static void CplA()
    {
        *(volatile uint32_t *)ODR_BB_ADDR = ~*(volatile uint32_t *)ODR_BB_ADDR;
    }
    INLINE static void Cpl()
    {
        BBBits->ODR_BIT0 = ~BBBits->ODR_BIT0;
    }

    INLINE static void Mode(PinConfig cfg)
    {
        switch(cfg)
        {
        case  INPUT:
            SetMode(MODER_INPUT);
            PullNone();
            break;

        case  INPUT_PULLUP:
            SetMode(MODER_INPUT);
            PullUp();
            break;

        case INPUT_PULLDOWN:
            SetMode(MODER_INPUT);
            PullDown();
            break;

        case ALT_INPUT:
            SetMode(MODER_ALTERNATE);
            PullNone();
            break;

        case ALT_INPUT_PULLUP:
            SetMode(MODER_ALTERNATE);
            PullUp();
            break;

        case ALT_INPUT_PULLDOWN:
            SetMode(MODER_ALTERNATE);
            PullDown();
            break;            
            
        case ANALOG:
            SetMode(MODER_ANALOG);
            PullNone();
            break;

        case OUTPUT:
            SetSpeed(speed);
            SetMode(MODER_OUTPUT);
            SetPushPull();
            //SetOutputTypeA(PUSH_PULL);
            PullNone();
            //SetPullUpA(PUPDR_NONE);
            break;

        case OUTPUT_OD:
            SetSpeed(speed);
            SetMode(MODER_OUTPUT);
            SetOpenDrain();
            PullNone();
            break;

        case OUTPUT_OD_PULLUP:
            SetSpeed(speed);
            SetMode(MODER_OUTPUT);
            SetOpenDrain();
            PullUp();
            break;

        case OUTPUT_OD_PULLDOWN:
            SetSpeed(speed);
            SetMode(MODER_OUTPUT);
            SetOpenDrain();
            PullDown();
            break;

        case ALT_OUTPUT:
            SetSpeed(speed);
            SetMode(MODER_ALTERNATE);
            SetPushPull();
            PullNone();
            break;

        case ALT_OUTPUT_OD:
            SetSpeed(speed);
            SetMode(MODER_ALTERNATE);
            SetOpenDrain();
            PullNone();
            break;

        case ALT_OUTPUT_OD_PULLUP:
            SetSpeed(speed);
            SetMode(MODER_ALTERNATE);
            SetOpenDrain();
            PullUp();
            break;

        case ALT_OUTPUT_OD_PULLDOWN:
            SetSpeed(speed);
            SetMode(MODER_ALTERNATE);
            SetOpenDrain();
            PullDown();
            break;
        }
    }
    INLINE static void Direct(PinConfig cfg) { Mode(cfg); }

    /**
     * Set Pull-UP/Pull-Down mode.
     */
    INLINE static void SetPullUpA(PullUpMode mode) { GPIOx->PUPDR = (GPIOx->PUPDR & ~mask_x2) | (mode << shift_x2); }
    INLINE static void SetPullUp(PullUpMode mode)
    {
        BBBits->PUPDR_BIT0 = mode & 1;
        BBBits->PUPDR_BIT1 = bool(mode & 2);
    }
    INLINE static void PullUp()   { SetPullUp(PUPDR_PULLUP); }
    INLINE static void PullDown() { SetPullUp(PUPDR_PULLDOWN); }
    INLINE static void PullNone() { SetPullUp(PUPDR_NONE); }

    INLINE static void SetSpeedA(PinSpeed s) { GPIOx->OSPEEDR = (GPIOx->OSPEEDR & ~mask_x2) | (s << shift_x2); }
    INLINE static void SetSpeed(PinSpeed s)
    {
        BBBits->OSPEEDR_BIT0 = s & 1;
        BBBits->OSPEEDR_BIT1 = bool(s & 2);
    }

    INLINE static void SetModeA(PinMode mode) { GPIOx->MODER = (GPIOx->MODER & ~mask_x2) | (mode << shift_x2); }
    INLINE static void SetMode(PinMode mode)
    {
        BBBits->MODER_BIT0 = mode & 1;
        BBBits->MODER_BIT1 = bool(mode & 2);
    }

    INLINE static void SetOutputTypeA(PinOutputType val) { val ? GPIOx->OTYPER |= mask : GPIOx->OTYPER &= ~mask; }
    INLINE static void SetOutputType(PinOutputType val) { BBBits->OTYPER_BIT0 = val; }
    INLINE static void SetPushPull() { SetOutputType(PUSH_PULL); }
    INLINE static void SetOpenDrain() { SetOutputType(OPEN_DRAIN);}

    INLINE static void Alternate(int val)
    {
        GPIOx->AFR[pin / 8] = (GPIOx->AFR[pin / 8] & ~mask_x4) | (val << shift_x4);
    }

    INLINE static int Latched()
    {
        int ret = BBBits->ODR_BIT0;
        return activestate == 'L' ? !ret : ret;
    }

    INLINE static int Signalled()
    {
        int ret = BBBits->IDR_BIT0;
        return activestate == 'L' ? !ret : ret;
    }

};


#endif /* PIN_STM32F4XX_H_ */
