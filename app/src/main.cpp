/*
	Copyright 2023. 홍윤기 all right reserved.

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <yss.h>
#include <bsp.h>
#include <util/runtime.h>
#include <yss/debug.h>
#include <std_ext/string.h>
#include <drv/Spi.h>

void thread_blinkLedR1(void);
void thread_blinkLedY1(void);
void thread_blinkLedG2(void);
void thread_testUart(void);

static const Spi::specification_t gConfig =
{
	Spi::MODE_MODE1,	//uint8_t mode;
	20000000,			//uint32_t maxFreq;
	Spi::BIT_BIT8		//uint8_t bit;
}; 

int main(void)
{
	uint32_t count;
	uint8_t *data;
	error_t result;

	uint8_t sa[32], da[32];

	for(uint32_t i = 0; i < 32; i++)
	{
		sa[i] = i;
		da[i] = 0;
	}

	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();
	
	// DMA memory to memory Test
	memcpyd(da, sa, 32);

	memsetd(da, 0xAA, 32);

	memsethwd(da, 0xBBCC, 16);

	memsetwd(da, 0x12345678, 8);

	thread::add(thread_blinkLedR1, 512);
	thread::add(thread_blinkLedG2, 512);
	thread::add(thread_blinkLedY1, 512);
	thread::add(thread_testUart, 512);
	
	spi2.setSpecification(gConfig);
	spi2.enable(true);
	
	while(1)
	{
		count = uart0.getRxCount();

		if(count)
		{
			data = (uint8_t*)uart0.getRxBuffer();
			for(uint32_t i = 0; i < count; i++)
				debug_printf("%c = 0x%02X\r\n", data[i], data[i]);
			
			uart0.releaseRxBuffer(count);
		}

		debug_printf("%d\r", (uint32_t)runtime::getMsec());

		result =  spi2.send(sa, 32);
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

void thread_testUart(void)
{
	while(1)
	{
		uart0.send("Hello World!!\n\r", sizeof("Hello World!!\n\r"));
	}
}

