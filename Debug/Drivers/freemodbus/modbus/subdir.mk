################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/freemodbus/modbus/mb.c 

OBJS += \
./Drivers/freemodbus/modbus/mb.o 

C_DEPS += \
./Drivers/freemodbus/modbus/mb.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/freemodbus/modbus/%.o: ../Drivers/freemodbus/modbus/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/STM32Toolchain/BH1750FVI/Inc" -I"C:/STM32Toolchain/BH1750FVI/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/STM32Toolchain/BH1750FVI/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/STM32Toolchain/BH1750FVI/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/STM32Toolchain/BH1750FVI/Drivers/CMSIS/Include" -I"C:/STM32Toolchain/BH1750FVI/Drivers/freemodbus/port" -I"C:/STM32Toolchain/BH1750FVI/Drivers/freemodbus/modbus/include" -I"C:/STM32Toolchain/BH1750FVI/Drivers/freemodbus/modbus/rtu"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


