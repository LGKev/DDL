################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/old_Pid/subdir.mk
-include src/subdir.mk
-include driver/subdir.mk
-include cmsis/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: DDL_FINAL_invert_pendulum.axf

# Tool invocations
DDL_FINAL_invert_pendulum.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map=DDL_FINAL_invert_pendulum.map -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "../linker/lpc1114_flash_crp.ld" -o "DDL_FINAL_invert_pendulum.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) DDL_FINAL_invert_pendulum.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size DDL_FINAL_invert_pendulum.axf; arm-none-eabi-objcopy -O binary DDL_FINAL_invert_pendulum.axf DDL_FINAL_invert_pendulum.bin ; checksum -p LPC1114_302 -d DDL_FINAL_invert_pendulum.bin;
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
