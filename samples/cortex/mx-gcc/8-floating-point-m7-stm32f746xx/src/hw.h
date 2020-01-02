/**
*  @file hw.h
*
*  Project-wide hardware definitions
*
*  Copyright © 2020 Anton B. Gusev
**/

#pragma once

#include <scmRTOS.h>
#include "pin.h"

/**
 * STM32746G-Discovery board hardware definitions
 */
struct Stm32F746DiscoveryHardware
{
	/// IO Pins
	struct Pins
	{
		using GreenLED = Pin<'I', 1>;

		static void Init()
		{
			GreenLED::Off();
			GreenLED::Mode(OUTPUT);
		}
	};
};

using Board = Stm32F746DiscoveryHardware;

using GreenLED = Board::Pins::GreenLED;
