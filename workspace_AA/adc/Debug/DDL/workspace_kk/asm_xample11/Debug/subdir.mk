################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../DDL/workspace_kk/asm_xample11/Debug/cr_startup_lpc11.asm \
../DDL/workspace_kk/asm_xample11/Debug/main.asm 

OBJS += \
./DDL/workspace_kk/asm_xample11/Debug/cr_startup_lpc11.o \
./DDL/workspace_kk/asm_xample11/Debug/main.o 


# Each subdirectory must supply rules for building sources it contributes
DDL/workspace_kk/asm_xample11/Debug/%.o: ../DDL/workspace_kk/asm_xample11/Debug/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -DDEBUG -D__CODE_RED -g3 -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


