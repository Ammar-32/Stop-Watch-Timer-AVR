################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
StopWatchAVR.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: StopWatchAVR.elf secondary-outputs

# Tool invocations
StopWatchAVR.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,StopWatchAVR.map -mmcu=atmega16 -o "StopWatchAVR.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

StopWatchAVR.lss: StopWatchAVR.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S StopWatchAVR.elf  >"StopWatchAVR.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: StopWatchAVR.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 StopWatchAVR.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) StopWatchAVR.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
