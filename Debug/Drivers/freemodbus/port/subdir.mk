################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/freemodbus/port/mbcrc.c \
../Drivers/freemodbus/port/portevent.c \
../Drivers/freemodbus/port/portserial.c \
../Drivers/freemodbus/port/porttimer.c 

OBJS += \
./Drivers/freemodbus/port/mbcrc.o \
./Drivers/freemodbus/port/portevent.o \
./Drivers/freemodbus/port/portserial.o \
./Drivers/freemodbus/port/porttimer.o 

C_DEPS += \
./Drivers/freemodbus/port/mbcrc.d \
./Drivers/freemodbus/port/portevent.d \
./Drivers/freemodbus/port/portserial.d \
./Drivers/freemodbus/port/porttimer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/freemodbus/port/%.o: ../Drivers/freemodbus/port/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/STM32Toolchain/BH1750FVI/Inc" -I"C:/STM32Toolchain/BH1750FVI/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32Toolchain/BH1750FVI/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/STM32Toolchain/BH1750FVI/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32Toolchain/BH1750FVI/Drivers/CMSIS/Include" -I"C:/STM32Toolchain/BH1750FVI/Drivers/freemodbus/port" -I"C:/STM32Toolchain/BH1750FVI/Drivers/freemodbus/modbus/include" -I"C:/STM32Toolchain/BH1750FVI/Drivers/freemodbus/modbus/rtu"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


