################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../startup/startup_mk64f12.cpp 

OBJS += \
./startup/startup_mk64f12.o 

CPP_DEPS += \
./startup/startup_mk64f12.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2/board" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2/inc" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2/source" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2/drivers" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2/device" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2/CMSIS" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2/component/uart" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2/utilities" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2/component/serial_manager" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Fusion2/component/lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


