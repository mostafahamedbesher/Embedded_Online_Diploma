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

#include "stm32f103x6.h"
#include "stm32_f103c6_gpio_drivers.h"
#include "lcd.h"
#include "keypad.h"


void clock_init(void)
{
	//enable clock for GPIOA
	RCC_GPIOA_CLK_EN();
	//enable clock for GPIOB
	RCC_GPIOB_CLK_EN();
}

void set_project_start(void)
{
	lcd_clear();
	lcd_write_string("PRESS A KEY");
	lcd_goto_xy(2,0);
}


int main(void)
{
	clock_init();
    lcd_init();
	keypad_init();
	lcd_goto_xy(1,0);
	lcd_write_string("PRESS A KEY");
	lcd_goto_xy(2,0);
	char press_key, press_counter = 0;
    while (1)
    {
		press_key = keypad_get_key();
		switch(press_key)
		{
			//when pressing clear button
			case '?':
			{
				set_project_start();
				press_counter = 0;
				break;
			}
			//in case of not pressing any key
			case 'N':
				break;
			//when pressing keys
			default:
			{
				press_counter++;
				//check if pressed keys exceeded max LCD columns(16 column)
				if(press_counter >= 16)
				{
					set_project_start();
					press_counter = 0;
				}
				lcd_write_char(press_key);
				break;
			}
		}
    }
}