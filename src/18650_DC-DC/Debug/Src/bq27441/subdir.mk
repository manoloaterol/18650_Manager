################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/bq27441/bq27441-g1.c 

OBJS += \
./Src/bq27441/bq27441-g1.o 

C_DEPS += \
./Src/bq27441/bq27441-g1.d 


# Each subdirectory must supply rules for building sources it contributes
Src/bq27441/bq27441-g1.o: ../Src/bq27441/bq27441-g1.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32G031xx -c -I../Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/bq27441/bq27441-g1.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

