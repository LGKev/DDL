################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DDL/workspace_kk/swuart/driver/adc.c \
../DDL/workspace_kk/swuart/driver/can.c \
../DDL/workspace_kk/swuart/driver/clkconfig.c \
../DDL/workspace_kk/swuart/driver/crp.c \
../DDL/workspace_kk/swuart/driver/debug_printf.c \
../DDL/workspace_kk/swuart/driver/gpio.c \
../DDL/workspace_kk/swuart/driver/i2c.c \
../DDL/workspace_kk/swuart/driver/i2cslave.c \
../DDL/workspace_kk/swuart/driver/lpc_swu.c \
../DDL/workspace_kk/swuart/driver/rs485.c \
../DDL/workspace_kk/swuart/driver/small_gpio.c \
../DDL/workspace_kk/swuart/driver/ssp.c \
../DDL/workspace_kk/swuart/driver/timer16.c \
../DDL/workspace_kk/swuart/driver/timer32.c \
../DDL/workspace_kk/swuart/driver/uart.c \
../DDL/workspace_kk/swuart/driver/wdt.c 

OBJS += \
./DDL/workspace_kk/swuart/driver/adc.o \
./DDL/workspace_kk/swuart/driver/can.o \
./DDL/workspace_kk/swuart/driver/clkconfig.o \
./DDL/workspace_kk/swuart/driver/crp.o \
./DDL/workspace_kk/swuart/driver/debug_printf.o \
./DDL/workspace_kk/swuart/driver/gpio.o \
./DDL/workspace_kk/swuart/driver/i2c.o \
./DDL/workspace_kk/swuart/driver/i2cslave.o \
./DDL/workspace_kk/swuart/driver/lpc_swu.o \
./DDL/workspace_kk/swuart/driver/rs485.o \
./DDL/workspace_kk/swuart/driver/small_gpio.o \
./DDL/workspace_kk/swuart/driver/ssp.o \
./DDL/workspace_kk/swuart/driver/timer16.o \
./DDL/workspace_kk/swuart/driver/timer32.o \
./DDL/workspace_kk/swuart/driver/uart.o \
./DDL/workspace_kk/swuart/driver/wdt.o 

C_DEPS += \
./DDL/workspace_kk/swuart/driver/adc.d \
./DDL/workspace_kk/swuart/driver/can.d \
./DDL/workspace_kk/swuart/driver/clkconfig.d \
./DDL/workspace_kk/swuart/driver/crp.d \
./DDL/workspace_kk/swuart/driver/debug_printf.d \
./DDL/workspace_kk/swuart/driver/gpio.d \
./DDL/workspace_kk/swuart/driver/i2c.d \
./DDL/workspace_kk/swuart/driver/i2cslave.d \
./DDL/workspace_kk/swuart/driver/lpc_swu.d \
./DDL/workspace_kk/swuart/driver/rs485.d \
./DDL/workspace_kk/swuart/driver/small_gpio.d \
./DDL/workspace_kk/swuart/driver/ssp.d \
./DDL/workspace_kk/swuart/driver/timer16.d \
./DDL/workspace_kk/swuart/driver/timer32.d \
./DDL/workspace_kk/swuart/driver/uart.d \
./DDL/workspace_kk/swuart/driver/wdt.d 


# Each subdirectory must supply rules for building sources it contributes
DDL/workspace_kk/swuart/driver/%.o: ../DDL/workspace_kk/swuart/driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -D__USE_CMSIS -DDEBUG -D__CODE_RED -I../cmsis -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lib_small_printf_m0\inc" -I../config -I../driver -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


