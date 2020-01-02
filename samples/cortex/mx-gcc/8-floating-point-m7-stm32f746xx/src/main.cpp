//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: STM32F746 (ARM Cortex-M7F)
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: v5.1.0
//*
//*
//*     Copyright (c) 2003-2016, scmRTOS Team
//*
//*     Permission is hereby granted, free of charge, to any person 
//*     obtaining  a copy of this software and associated documentation 
//*     files (the "Software"), to deal in the Software without restriction, 
//*     including without limitation the rights to use, copy, modify, merge, 
//*     publish, distribute, sublicense, and/or sell copies of the Software, 
//*     and to permit persons to whom the Software is furnished to do so, 
//*     subject to the following conditions:
//*
//*     The above copyright notice and this permission notice shall be included 
//*     in all copies or substantial portions of the Software.
//*
//*     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
//*     EXPRESS  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
//*     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
//*     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
//*     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
//*     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
//*     THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*
//*     =================================================================
//*     Project sources: https://github.com/scmrtos/scmrtos
//*     Documentation:   https://github.com/scmrtos/scmrtos/wiki/Documentation
//*     Wiki:            https://github.com/scmrtos/scmrtos/wiki
//*     Sample projects: https://github.com/scmrtos/scmrtos-sample-projects
//*     =================================================================
//*
//******************************************************************************
//*     GCC port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2020

#include <scmRTOS.h>
#include "hw.h"

/// Process types
using PiCalcProc = OS::process<OS::pr0, 300>;
using TestContextProc1 = OS::process<OS::pr1, 300>;
using TestContextProc2 = OS::process<OS::pr2, 300>;
using LedProc = OS::process<OS::pr3, 300>;

///      Process objects
PiCalcProc piCalcProc;
TestContextProc1 testContextProc1;
TestContextProc2 testContextProc2;
LedProc ledProc;

/**
 * Class for PI calculation
 */
template <uint32_t iterations>
class PiCalculator
{
public:
	void makeStep()
	{
		if (!done())
		{
			++step;
			ret += 4.0f/static_cast<float>(2 * step - 1);
		}
	}
	bool done() { return step > iterations; }
	double result() { return ret; }
private:
	uint32_t step { 0 };
	float ret { 0.f };
};

OS_PROCESS void test_context(uint32_t param);

int main()
{
    // configure pins
	Board::Pins::Init();

    // run
    OS::run();
}

namespace OS
{

template <>
OS_PROCESS void PiCalcProc::exec()
{
	sleep(2);
	for(;;)
	{
		PiCalculator<100000000> piCalc;
		while (!piCalc.done())
		{
			for(int i = 0; i < 100; i++)
				piCalc.makeStep();
			sleep(1);
		}
		sleep(piCalc.result());
	}
}

template <>
OS_PROCESS void TestContextProc1::exec()
{
	test_context(0x12345678);
}

template <>
OS_PROCESS void TestContextProc2::exec()
{
	test_context(0x87654321);
}

template <>
OS_PROCESS void LedProc::exec()
{
	for(;;)
	{
		GreenLED::On();
		sleep(50);
		GreenLED::Off();
		sleep(950);
	}
}

} // namespace OS

#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
	__WFI();
}
#endif
