/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
//prototypes
void clock_init(void);
void GPIO_init(void);

//GPIOA addresses
#define GPIOA_BASE    0x40010800
#define GPIOA_CRH     *(vuint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR     *(vuint32_t *)(GPIOA_BASE + 0x0C)
#define GPIOA_CRL     *(vuint32_t *)(GPIOA_BASE + 0x00)
//RCC addresses
#define RCC_BASE	  0x40021000
#define RCC_CFGR	  *(vuint32_t *)(RCC_BASE + 0x04)
#define RCC_CR		  *(vuint32_t *)(RCC_BASE + 0x00)
#define RCC_APB2ENR	  *(vuint32_t *)(RCC_BASE + 0x18)
//AFIO addresses
#define AFIO_BASE	  0x40010000
#define AFIO_EXTICR1  *(vuint32_t *)(AFIO_BASE + 0x08)
//EXTI addresses
#define EXTI_BASE	  0x40010400
#define EXTI_IMR  	  *(vuint32_t *)(EXTI_BASE + 0x00)
#define EXTI_RTSR  	  *(vuint32_t *)(EXTI_BASE + 0x08)
#define EXTI_PR  	  *(vuint32_t *)(EXTI_BASE + 0x14)
//NVIC addresses
#define NVIC_ISER0 	  *(vuint32_t *)(0xE000E100)

int main(void)
{
	clock_init();
	GPIO_init();
	//Enable clock for portA
	RCC_APB2ENR |= 1<<2;
	//Enable clock for AFIO
	RCC_APB2ENR |= 1<<0;
	//select PA0 from AFIO to EXT0 line
	AFIO_EXTICR1 = 0;
	//Enable interrupt line (EXTI0) in EXTI Module
	EXTI_IMR |= 1<<0;
	//Enable rising trigger
	EXTI_RTSR |= 1<<0;
	//Enable NVIC IRQ 6
	NVIC_ISER0 |= 1<<6;
	while(1);
}


void EXTI0_IRQHandler(void)
{
	//toggle portA pin 13
	GPIOA_ODR ^=  1<<13 ;
	//reset pending status
	EXTI_PR |= 1<<0;
}

void clock_init(void)
{
	//PLL multiplication factor by 8
	RCC_CFGR |= (0b0110<<18);
	//select PLL as a clock source
	RCC_CFGR |= (0b10<<0);
	//APB1 prescaler divided by 2
	RCC_CFGR |= (0b100<<8);
	//APB2 prescaler divided by 4
	RCC_CFGR |= (0b101<<11);
	//enable PLL
	RCC_CR |= 1<<24;
}

void GPIO_init(void)
{
	//Init GPIOA
	GPIOA_CRH   &= 0xFF0FFFFF;
	GPIOA_CRH   |= 0x00200000;
	//configure pin PA0 to be input
	GPIOA_CRL |= 1<<2;
}
