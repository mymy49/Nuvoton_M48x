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
	gpioA.setAsAltFunc(0, Gpio::PA0_SPI0_I2S_DO);
	gpioA.setAsAltFunc(2, Gpio::PA2_SPI0_I2S_BCLK);
	gpioA.setAsAltFunc(3, Gpio::PA3_SPI0_I2S_LRCLK);
	gpioB.setAsAltFunc(0, Gpio::PB0_SPI0_I2S_MCLK);
	
	I2s::specification_t i2s0Spec = 
	{
		I2s::MODE_MAIN_TX,	//mode_t mode;
		I2s::BIT_16BIT,		//dataBit_t dataBit;
		I2s::STD_I2S_DATA,	//std_t std;
		176400				//uint32_t sampleRate;
	};

	i2s0.enableClock();
	i2s0.initialize(i2s0Spec);
	i2s0.enableInterrupt();
}
