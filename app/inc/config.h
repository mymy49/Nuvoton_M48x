/*
 * Copyright (c) 2024 Yoon-Ki Hong
 *
 * This file is subject to the terms and conditions of the MIT License.
 * See the file "LICENSE" in the main directory of this archive for more details.
 */

// Nuvoton M483 시리즈에서 유효한 설정이 담긴 참고용 파일입니다.
// 해당 파일을 사용자 프로젝트의 include 경로(app/inc)에 복사하고 config.h로 변경해서 사용하는 것을 추천합니다.

#ifndef YSS_CONFIG__H_
#define YSS_CONFIG__H_

// ####################### 외부 크리스탈 클럭 주파수 설정 #######################
// 아래 HSE_CLOCK_FREQ가 정의 되어 있으면 HSE 클럭을 소스로 PLL 설정이 이뤄집니다.
// 정의되어 있지 않으면 HSI 클럭을 소스로 PLL 설정이 이뤄집니다.
//#define HSE_CLOCK_FREQ 12000000

// ####################### 스케줄러 설정 #######################
// runtime 함수를 지원할 PWM 장치 설정 (RUNTIME_TIM3, 14, 15, 16, 17)
#define YSS_TIMER			RUNTIME_TIMER0

// 쓰레드당 할당 받는 Systick Clock의 수
#define THREAD_GIVEN_CLOCK	20000

// 최대 등록 가능한 쓰레드의 수
#define MAX_THREAD			6

// 쓰레드의 스택을 0xAA 패턴으로 채우기 (true, false)
#define FILL_THREAD_STACK	false

// ####################### DMA 복사 설정 #######################
// DMA를 사용하는 copy() 함수가 사용할 DMA를 지정한다. (dmaChannel1 ~ dmaChannel5)
#define COPY_DMA			dmaChannel1

// ####################### GUI 설정 #######################
// GUI library Enable (true, false)
#define USE_GUI				true

// ####################### KEY 설정 #######################
// 최대 KEY 생성 가능 갯수 설정 (0 ~ ), 0일 경우 기능 꺼짐
#define NUM_OF_YSS_KEY		0

// ###################### 주변 장치 활성화 ######################
// 활성화 시킬 장치에 대해 false -> true로 변경하여 활성화 한다.
//
// 주의 
// 1. TIMER, PWM, CAPTURE는 실제 동일한 장치지만 OS 구조상 별도의 장치로 표현한다. 그러므로 동일한 번호의 TIMER, PWM, CAPTURE는 동시에 활성화 되지 못한다.

// SPI 활성화
#define SPI0_ENABLE			true
#define SPI1_ENABLE			false
#define SPI2_ENABLE			false
#define SPI3_ENABLE			false

// UART 활성화
#define UART0_ENABLE		true
#define UART1_ENABLE		false
#define UART2_ENABLE		false
#define UART3_ENABLE		false
#define UART4_ENABLE		false
#define UART5_ENABLE		false
#define UART6_ENABLE		false
#define UART7_ENABLE		false

#endif

