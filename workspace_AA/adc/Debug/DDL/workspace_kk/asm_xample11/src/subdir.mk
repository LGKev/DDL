################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../DDL/workspace_kk/asm_xample11/src/asm_sum_cm0.s 

C_SRCS += \
../DDL/workspace_kk/asm_xample11/src/cr_startup_lpc11.c \
../DDL/workspace_kk/asm_xample11/src/main.c 

OBJS += \
./DDL/workspace_kk/asm_xample11/src/asm_sum_cm0.o \
./DDL/workspace_kk/asm_xample11/src/cr_startup_lpc11.o \
./DDL/workspace_kk/asm_xample11/src/main.o 

C_DEPS += \
./DDL/workspace_kk/asm_xample11/src/cr_startup_lpc11.d \
./DDL/workspace_kk/asm_xample11/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
DDL/workspace_kk/asm_xample11/src/%.o: ../DDL/workspace_kk/asm_xample11/src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -DDEBUG -D__CODE_RED -g3 -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

DDL/workspace_kk/asm_xample11/src/%.o: ../DDL/workspace_kk/asm_xample11/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -D__USE_CMSIS -DDEBUG -D__CODE_RED -I../cmsis -I../config -I../driver -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


