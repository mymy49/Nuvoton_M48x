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
#include <drv/Spi.h>
#include <math.h>

void thread_blinkLedR1(void);

void thread_blinkLedY1(void);

void thread_blinkLedG2(void);

int16_t gAudioBuffer[1024];

int main(void)
{
	uint32_t count;
	int16_t pcm = 0;
	int16_t *audioBuf;
	float radian = 0;

	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();
	
	memsethwd(gAudioBuffer, 0, 1024);

	thread::add(thread_blinkLedR1, 512);
	thread::add(thread_blinkLedG2, 512);
	thread::add(thread_blinkLedY1, 512);

	i2s0.transfer(gAudioBuffer, 1024);
	
	while(1)
	{
		count = i2s0.getTxCount();
		if(count)
		{
			audioBuf =  (int16_t*)i2s0.getCurrrentBuffer();

			for(uint32_t i = 0; i < count; i += 2)
			{
				pcm = sin(radian) * 32767;
				audioBuf[i] = pcm;
				audioBuf[i+1] = pcm;
				radian += 0.00001f;
			}
			
			i2s0.releaseBuffer(count);
		}
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

