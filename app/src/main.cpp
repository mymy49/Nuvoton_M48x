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

void thread_test(void)
{
	while(1)
	{
		thread::yield();
	}
}

int main(void)
{
	uint64_t lastT, thisT;

	// 운영체체 초기화
	initializeYss();

	// 보드 초기화
	initializeBoard();

	thread::add(thread_test, 512);
	
	thisT = lastT = runtime::getMsec();

	while(1)
	{
		debug_printf("%d\r", (uint32_t)runtime::getMsec());
	}
}
