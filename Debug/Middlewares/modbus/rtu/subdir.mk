################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/modbus/rtu/mbcrc.c \
../Middlewares/modbus/rtu/mbrtu.c 

OBJS += \
./Middlewares/modbus/rtu/mbcrc.o \
./Middlewares/modbus/rtu/mbrtu.o 

C_DEPS += \
./Middlewares/modbus/rtu/mbcrc.d \
./Middlewares/modbus/rtu/mbrtu.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/modbus/rtu/%.o: ../Middlewares/modbus/rtu/%.c Middlewares/modbus/rtu/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"E:/OneDrive - Hanoi University of Science and Technology/Document_TuBK/MODBUS/modbus_workspace/freeModbusRTU_Slave_F7/Middlewares" -I"E:/OneDrive - Hanoi University of Science and Technology/Document_TuBK/MODBUS/modbus_workspace/freeModbusRTU_Slave_F7/Middlewares/FreeRTOS/include" -I"E:/OneDrive - Hanoi University of Science and Technology/Document_TuBK/MODBUS/modbus_workspace/freeModbusRTU_Slave_F7/Middlewares/FreeRTOS/portable/GCC/ARM_CM4F" -I"E:/OneDrive - Hanoi University of Science and Technology/Document_TuBK/MODBUS/modbus_workspace/freeModbusRTU_Slave_F7/Middlewares/modbus" -I"E:/OneDrive - Hanoi University of Science and Technology/Document_TuBK/MODBUS/modbus_workspace/freeModbusRTU_Slave_F7/Middlewares/modbus/include" -I"E:/OneDrive - Hanoi University of Science and Technology/Document_TuBK/MODBUS/modbus_workspace/freeModbusRTU_Slave_F7/Middlewares/modbus/port" -I"E:/OneDrive - Hanoi University of Science and Technology/Document_TuBK/MODBUS/modbus_workspace/freeModbusRTU_Slave_F7/Middlewares/modbus/rtu" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

