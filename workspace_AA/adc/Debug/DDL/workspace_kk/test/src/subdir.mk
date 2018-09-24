################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DDL/workspace_kk/test/src/cr_startup_lpc11xx.c \
../DDL/workspace_kk/test/src/crp.c \
../DDL/workspace_kk/test/src/test.c 

OBJS += \
./DDL/workspace_kk/test/src/cr_startup_lpc11xx.o \
./DDL/workspace_kk/test/src/crp.o \
./DDL/workspace_kk/test/src/test.o 

C_DEPS += \
./DDL/workspace_kk/test/src/cr_startup_lpc11xx.d \
./DDL/workspace_kk/test/src/crp.d \
./DDL/workspace_kk/test/src/test.d 


# Each subdirectory must supply rules for building sources it contributes
DDL/workspace_kk/test/src/%.o: ../DDL/workspace_kk/test/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -D__USE_CMSIS -DDEBUG -D__CODE_RED -I../cmsis -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lib_small_printf_m0\inc" -I../config -I../driver -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


