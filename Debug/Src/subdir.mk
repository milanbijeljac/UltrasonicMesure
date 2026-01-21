################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/main.cpp 

C_SRCS += \
../Src/syscalls.c \
../Src/sysmem.c 

C_DEPS += \
./Src/syscalls.d \
./Src/sysmem.d 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

CPP_DEPS += \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.cpp Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++20 -g3 -DDEBUG -DSTM32 -DSTM32F0 -DSTM32F072RBTx -c -I../Inc -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/Drivers/GPIO/Inc" -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/CMSIS/Inc" -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/DataStructure/RingBuffer/Inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F0 -DSTM32F072RBTx -c -I../Inc -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/Drivers/GPIO/Inc" -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/CMSIS/Inc" -I"/home/milan/STM32CubeIDE/workspace_1.19.0/UltrasonicMesure/DataStructure/RingBuffer/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

