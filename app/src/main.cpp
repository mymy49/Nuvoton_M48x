/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <yss.h>
#include <bsp.h>
#include <util/runtime.h>
#include <yss/debug.h>
#include <std_ext/string.h>
#include <targets/nuvoton/bitfield_m48x.h>

void thread_blinkLedR1(void);

void thread_blinkLedY1(void);

void thread_blinkLedG2(void);

int main(void)
{
	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	thread::add(thread_blinkLedR1, 512);
	thread::add(thread_blinkLedG2, 512);
	thread::add(thread_blinkLedY1, 512);

	flash.erasePage(3);
	flash.program(3, (uint32_t)0x00000000, 1024);

	while(1)
	{
		thread::yield();
	}
}

void thread_blinkLedR1(void)
{
	while(1)
	{
		led::setLedR1(true);
		thread::delay(250);

		led::setLedR1(false);
		thread::delay(250);
	}
}

void thread_blinkLedG2(void)
{
	while(1)
	{
		led::setLedG2(true);
		thread::delay(500);

		led::setLedG2(false);
		thread::delay(500);
	}
}

void thread_blinkLedY1(void)
{
	while(1)
	{
		led::setLedY1(true);
		thread::delay(1000);

		led::setLedY1(false);
		thread::delay(1000);
	}
}

