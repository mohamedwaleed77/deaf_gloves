################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART/subdir.mk
-include MCAL/TIMERS/subdir.mk
-include MCAL/I2C/subdir.mk
-include MCAL/GI/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/LCDI2C/subdir.mk
-include HAL/FLEX_SENSOR/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
deaf_gloves.lss \

FLASH_IMAGE += \
deaf_gloves.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: deaf_gloves.elf secondary-outputs

# Tool invocations
deaf_gloves.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,deaf_gloves.map -mmcu=atmega32 -o "deaf_gloves.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

deaf_gloves.lss: deaf_gloves.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S deaf_gloves.elf  >"deaf_gloves.lss"
	@echo 'Finished building: $@'
	@echo ' '

deaf_gloves.hex: deaf_gloves.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex deaf_gloves.elf  "deaf_gloves.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: deaf_gloves.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 deaf_gloves.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) deaf_gloves.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
