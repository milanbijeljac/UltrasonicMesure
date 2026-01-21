################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drivers/GPIO/Src/gpio_driver.cpp 

OBJS += \
./Drivers/GPIO/Src/gpio_driver.o 

CPP_DEPS += \
./Drivers/GPIO/Src/gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/GPIO/Src/%.o Drivers/GPIO/Src/%.su Drivers/GPIO/Src/%.cyclo: ../Drivers/GPIO/Src/%.cpp Drivers/GPIO/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++20 -g3 -DDEBUG -DSTM32 -DSTM32F0 -DSTM32F072RBTx -c -I../Inc -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/Drivers/GPIO/Inc" -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/CMSIS/Inc" -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/DataStructure/RingBuffer/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-GPIO-2f-Src

clean-Drivers-2f-GPIO-2f-Src:
	-$(RM) ./Drivers/GPIO/Src/gpio_driver.cyclo ./Drivers/GPIO/Src/gpio_driver.d ./Drivers/GPIO/Src/gpio_driver.o ./Drivers/GPIO/Src/gpio_driver.su

.PHONY: clean-Drivers-2f-GPIO-2f-Src

