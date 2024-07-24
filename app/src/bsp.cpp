/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

#include <bsp.h>
#include <yss/instance.h>

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
	gpioA.setAsAltFunc(8, Gpio::PA8_SPI2_MOSI);
	gpioA.setAsAltFunc(9, Gpio::PA9_SPI2_MISO);
	gpioA.setAsAltFunc(10, Gpio::PA10_SPI2_CLK);
	gpioA.setAsOutput(11);

	spi2.enableClock();
	spi2.initializeAsMain();
	spi2.enableInterrupt();
}
