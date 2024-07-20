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

#include <bsp.h>
#include <yss/instance.h>

Touch_LCD_Shield_for_Arduino_2_8_inch lcd;

Bmp565Buffer brush(10000);

void initializeBoard(void)
{
	// LED 초기화
	led::initialize();

	// UART0 초기화
	gpioB.setAsAltFunc(12, Gpio::PB12_UART0_RXD);
	gpioB.setAsAltFunc(13, Gpio::PB13_UART0_TXD);

	uart0.enableClock();
	uart0.initialize(115200, 64);
	uart0.enableInterrupt();

	// SPI2 초기화
	gpioA.setAsAltFunc(0, Gpio::PA0_SPI0_MOSI);
	gpioA.setAsAltFunc(1, Gpio::PA1_SPI0_MISO);
	gpioA.setAsAltFunc(2, Gpio::PA2_SPI0_CLK);
	gpioA.setAsOutput(3); // CS
	gpioA.setAsOutput(4); // BL
	gpioE.setAsOutput(5); // DC

	gpioA.setOutput(4, false);
	gpioA.setOutput(4, true);

	spi0.enableClock();
	spi0.initializeAsMain();
	spi0.enableInterrupt();
	
	const Touch_LCD_Shield_for_Arduino_2_8_inch::config_t config =
	{
		spi0,			//Spi &peri;
		{&gpioA, 3},	//pin_t chipSelect;
		{&gpioE, 5},	//pin_t dataCommand;
		{0, 0}			//pin_t reset;
	};

	lcd.setConfig(config);
	lcd.initialize();
	lcd.setBmp565Buffer(brush);
	lcd.setBackgroundColor(0xFF, 0xFF, 0xFF);
	lcd.clear();
}
