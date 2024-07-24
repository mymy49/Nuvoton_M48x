/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <dev/led.h>
#include <yss/instance.h>

namespace led
{
	void initialize(void)
	{
		gpioH.setAsOutput(4);
		gpioH.setAsOutput(5);
		gpioH.setAsOutput(6);

		setLedR1(false);
		setLedY1(false);
		setLedG2(false);
	}

	void setLedR1(bool on)
	{
		gpioH.setOutput(4, !on);
	}

	void setLedY1(bool on)
	{
		gpioH.setOutput(5, !on);
	}

	void setLedG2(bool on)
	{
		gpioH.setOutput(6, !on);
	}
}

