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

#include "stm32_f103c6_EXTI_drivers.h"
#include "stm32f103x6.h"
#include "stm32_f103c6_gpio_drivers.h"
#include "lcd.h"


uint32_t IRQ_Flag = 0;

void delay(uint32_t time)
{
	uint32_t i,j;
	for(i=0; i<time; i++)
		for(j=0; j<255; j++);
}


void EXTI9_CALLBACK(void)
{
	lcd_write_string("IRQ EXTI9 IS HAPPEN _|- ");
	delay(2000);
	IRQ_Flag = 1;
}

void clock_init(void)
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();
}


int main(void)
{
	clock_init();
	lcd_init();
	lcd_clear();
	EXTI_PINCONFIG_t pin_config;
	pin_config.EXTI_PIN = EXTI9PB9;
	pin_config.Trigger_Case = EXTI_TRIGGER_RISING;
	pin_config.P_IRQ_callback = EXTI9_CALLBACK;
	pin_config.IRQ_EN = EXTI_IRQ_ENABLE;
	MCAL_EXTI_GPIO_Init(&pin_config);
	IRQ_Flag = 1;
	while(1)
	{
		if(IRQ_Flag)
		{
			lcd_clear();
			IRQ_Flag = 0;
		}
	}
}