################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/BV1750FVI.c \
../Src/SoilMoisture.c \
../Src/adc.c \
../Src/am2302.c \
../Src/delays.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
../Src/mbtask.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_it.c \
../Src/system_stm32f1xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/BV1750FVI.o \
./Src/SoilMoisture.o \
./Src/adc.o \
./Src/am2302.o \
./Src/delays.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/mbtask.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_it.o \
./Src/system_stm32f1xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/BV1750FVI.d \
./Src/SoilMoisture.d \
./Src/adc.d \
./Src/am2302.d \
./Src/delays.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
./Src/mbtask.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_it.d \
./Src/system_stm32f1xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/STM32Toolchain/BH1750FVI/Inc" -I"C:/STM32Toolchain/BH1750FVI/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32Toolchain/BH1750FVI/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/STM32Toolchain/BH1750FVI/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32Toolchain/BH1750FVI/Drivers/CMSIS/Include" -I"C:/STM32Toolchain/BH1750FVI/Drivers/freemodbus/port" -I"C:/STM32Toolchain/BH1750FVI/Drivers/freemodbus/modbus/include" -I"C:/STM32Toolchain/BH1750FVI/Drivers/freemodbus/modbus/rtu"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


