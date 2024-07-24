/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#ifndef DEV_LED__H_
#define DEV_LED__H_

namespace led
{
	void initialize(void) __attribute__((optimize("-O1")));

	void setLedR1(bool on) __attribute__((optimize("-O1")));

	void setLedY1(bool on) __attribute__((optimize("-O1")));

	void setLedG2(bool on) __attribute__((optimize("-O1")));
}

#endif

