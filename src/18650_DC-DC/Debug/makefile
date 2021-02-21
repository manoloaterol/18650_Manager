################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/ssd1306/subdir.mk
-include Src/bq27441/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32G0xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

BUILD_ARTIFACT_NAME := 18650_DC-DC
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
18650_DC-DC.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
18650_DC-DC.list \

OBJCOPY_BIN += \
18650_DC-DC.bin \


# All Target
all: main-build

# Main-build Target
main-build: 18650_DC-DC.elf secondary-outputs

# Tool invocations
18650_DC-DC.elf: $(OBJS) $(USER_OBJS) /Users/mat/Library/Mobile\ Documents/com~apple~CloudDocs/IoT/STM32/Proyectos_CubeIDE/18650_DC-DC/STM32G031G8UX_FLASH.ld
	arm-none-eabi-gcc -o "18650_DC-DC.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"/Users/mat/Library/Mobile Documents/com~apple~CloudDocs/IoT/STM32/Proyectos_CubeIDE/18650_DC-DC/STM32G031G8UX_FLASH.ld" --specs=nosys.specs -Wl,-Map="18650_DC-DC.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

18650_DC-DC.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "18650_DC-DC.list"
	@echo 'Finished building: $@'
	@echo ' '

18650_DC-DC.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "18650_DC-DC.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
