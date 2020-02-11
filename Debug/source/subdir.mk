################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/Control.cpp \
../source/Interrupts.cpp \
../source/K64F-Controle.cpp \
../source/cpp_config.cpp 

C_SRCS += \
../source/semihost_hardfault.c 

OBJS += \
./source/Control.o \
./source/Interrupts.o \
./source/K64F-Controle.o \
./source/cpp_config.o \
./source/semihost_hardfault.o 

CPP_DEPS += \
./source/Control.d \
./source/Interrupts.d \
./source/K64F-Controle.d \
./source/cpp_config.d 

C_DEPS += \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/board" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/inc" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/source" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/drivers" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/device" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/CMSIS" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/component/uart" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/utilities" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/component/serial_manager" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/component/lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/board" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/source" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/drivers" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/device" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/CMSIS" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/component/uart" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/utilities" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/component/serial_manager" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/component/lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

