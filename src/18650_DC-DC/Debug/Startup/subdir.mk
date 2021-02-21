################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32g031g8ux.s 

OBJS += \
./Startup/startup_stm32g031g8ux.o 

S_DEPS += \
./Startup/startup_stm32g031g8ux.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_stm32g031g8ux.o: ../Startup/startup_stm32g031g8ux.s
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -c -x assembler-with-cpp -MMD -MP -MF"Startup/startup_stm32g031g8ux.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

