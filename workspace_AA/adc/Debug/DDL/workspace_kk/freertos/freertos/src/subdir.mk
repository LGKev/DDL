################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DDL/workspace_kk/freertos/freertos/src/croutine.c \
../DDL/workspace_kk/freertos/freertos/src/list.c \
../DDL/workspace_kk/freertos/freertos/src/queue.c \
../DDL/workspace_kk/freertos/freertos/src/tasks.c 

OBJS += \
./DDL/workspace_kk/freertos/freertos/src/croutine.o \
./DDL/workspace_kk/freertos/freertos/src/list.o \
./DDL/workspace_kk/freertos/freertos/src/queue.o \
./DDL/workspace_kk/freertos/freertos/src/tasks.o 

C_DEPS += \
./DDL/workspace_kk/freertos/freertos/src/croutine.d \
./DDL/workspace_kk/freertos/freertos/src/list.d \
./DDL/workspace_kk/freertos/freertos/src/queue.d \
./DDL/workspace_kk/freertos/freertos/src/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
DDL/workspace_kk/freertos/freertos/src/%.o: ../DDL/workspace_kk/freertos/freertos/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -D__USE_CMSIS -DDEBUG -D__CODE_RED -I../cmsis -I../config -I../driver -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


