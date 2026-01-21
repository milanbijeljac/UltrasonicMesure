################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/GPIO/UART/Src/uart_driver.cpp 

OBJS += \
./Drivers/GPIO/UART/Src/uart_driver.o 

CPP_DEPS += \
./Drivers/GPIO/UART/Src/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/GPIO/UART/Src/%.o Drivers/GPIO/UART/Src/%.su Drivers/GPIO/UART/Src/%.cyclo: ../Drivers/GPIO/UART/Src/%.cpp Drivers/GPIO/UART/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++20 -g3 -DDEBUG -DSTM32 -DSTM32F0 -DSTM32F072RBTx -c -I../Inc -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/Drivers/GPIO/Inc" -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/CMSIS/Inc" -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/DataStructure/RingBuffer/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-GPIO-2f-UART-2f-Src

clean-Drivers-2f-GPIO-2f-UART-2f-Src:
	-$(RM) ./Drivers/GPIO/UART/Src/uart_driver.cyclo ./Drivers/GPIO/UART/Src/uart_driver.d ./Drivers/GPIO/UART/Src/uart_driver.o ./Drivers/GPIO/UART/Src/uart_driver.su

.PHONY: clean-Drivers-2f-GPIO-2f-UART-2f-Src

