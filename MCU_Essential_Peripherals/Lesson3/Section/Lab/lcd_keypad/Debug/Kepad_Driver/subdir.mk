################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Kepad_Driver/keypad.c 

OBJS += \
./Kepad_Driver/keypad.o 

C_DEPS += \
./Kepad_Driver/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
Kepad_Driver/keypad.o: ../Kepad_Driver/keypad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"D:/Embedded_Diploma/assignments/5_Unit7_MCU_Essential Peripherals/Lesson3/section/lcd_keypad/LCD_Driver/inc" -I"D:/Embedded_Diploma/assignments/5_Unit7_MCU_Essential Peripherals/Lesson3/section/lcd_keypad/stm32_f103c6_Drivers/inc" -I"D:/Embedded_Diploma/assignments/5_Unit7_MCU_Essential Peripherals/Lesson3/section/lcd_keypad/Kepad_Driver/inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Kepad_Driver/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

