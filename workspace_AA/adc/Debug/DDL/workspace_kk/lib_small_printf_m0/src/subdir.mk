################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DDL/workspace_kk/lib_small_printf_m0/src/small_printf_float.c \
../DDL/workspace_kk/lib_small_printf_m0/src/small_printf_nofloat.c \
../DDL/workspace_kk/lib_small_printf_m0/src/small_printf_support.c \
../DDL/workspace_kk/lib_small_printf_m0/src/small_utils.c 

OBJS += \
./DDL/workspace_kk/lib_small_printf_m0/src/small_printf_float.o \
./DDL/workspace_kk/lib_small_printf_m0/src/small_printf_nofloat.o \
./DDL/workspace_kk/lib_small_printf_m0/src/small_printf_support.o \
./DDL/workspace_kk/lib_small_printf_m0/src/small_utils.o 

C_DEPS += \
./DDL/workspace_kk/lib_small_printf_m0/src/small_printf_float.d \
./DDL/workspace_kk/lib_small_printf_m0/src/small_printf_nofloat.d \
./DDL/workspace_kk/lib_small_printf_m0/src/small_printf_support.d \
./DDL/workspace_kk/lib_small_printf_m0/src/small_utils.d 


# Each subdirectory must supply rules for building sources it contributes
DDL/workspace_kk/lib_small_printf_m0/src/%.o: ../DDL/workspace_kk/lib_small_printf_m0/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -D__USE_CMSIS -DDEBUG -D__CODE_RED -I../cmsis -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lib_small_printf_m0\inc" -I../config -I../driver -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


