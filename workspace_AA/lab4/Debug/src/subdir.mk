################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc11xx.c \
../src/crp.c \
../src/lab4.c 

OBJS += \
./src/cr_startup_lpc11xx.o \
./src/crp.o \
./src/lab4.o 

C_DEPS += \
./src/cr_startup_lpc11xx.d \
./src/crp.d \
./src/lab4.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSIS_CORE_LPC11xx -D__LPC11XX__ -D__REDLIB__ -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lab4\inc" -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lab4\driver" -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lab4\config" -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\CMSIS_CORE_LPC11xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


