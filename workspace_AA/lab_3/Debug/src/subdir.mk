################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/GetFib.s 

C_SRCS += \
../src/cr_startup_lpc11xx.c \
../src/crp.c \
../src/main.c 

OBJS += \
./src/GetFib.o \
./src/cr_startup_lpc11xx.o \
./src/crp.o \
./src/main.o 

C_DEPS += \
./src/cr_startup_lpc11xx.d \
./src/crp.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSIS_CORE_LPC11xx -D__LPC11XX__ -D__REDLIB__ -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lab_3\inc" -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\CMSIS_CORE_LPC11xx\inc" -g3 -mcpu=cortex-m0 -mthumb -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSIS_CORE_LPC11xx -D__LPC11XX__ -D__REDLIB__ -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lab_3\inc" -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lab_3\driver" -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\lab_3\config" -I"C:\Users\dell\Documents\GitHub\DDL\workspace_AA\CMSIS_CORE_LPC11xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


