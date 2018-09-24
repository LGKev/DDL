################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DDL/workspace_kk/timedwakeup/cmsis/core_cm0.c \
../DDL/workspace_kk/timedwakeup/cmsis/system_LPC11xx.c 

OBJS += \
./DDL/workspace_kk/timedwakeup/cmsis/core_cm0.o \
./DDL/workspace_kk/timedwakeup/cmsis/system_LPC11xx.o 

C_DEPS += \
./DDL/workspace_kk/timedwakeup/cmsis/core_cm0.d \
./DDL/workspace_kk/timedwakeup/cmsis/system_LPC11xx.d 


# Each subdirectory must supply rules for building sources it contributes
DDL/workspace_kk/timedwakeup/cmsis/%.o: ../DDL/workspace_kk/timedwakeup/cmsis/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -D__USE_CMSIS -DDEBUG -D__CODE_RED -I../cmsis -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lib_small_printf_m0\inc" -I../config -I../driver -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


