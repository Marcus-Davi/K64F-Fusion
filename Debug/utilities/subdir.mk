################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c \
../utilities/fsl_str.c 

OBJS += \
./utilities/fsl_debug_console.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_debug_console.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DPRINTF_FLOAT_ENABLE -DPRINTF_ADVANCED_ENABLE -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/projeto/Workspace/MCU/Workspace/K64F-Fusion2/board" -I"/home/projeto/Workspace/MCU/Workspace/K64F-Fusion2/source" -I"/home/projeto/Workspace/MCU/Workspace/K64F-Fusion2" -I"/home/projeto/Workspace/MCU/Workspace/K64F-Fusion2/drivers" -I"/home/projeto/Workspace/MCU/Workspace/K64F-Fusion2/device" -I"/home/projeto/Workspace/MCU/Workspace/K64F-Fusion2/CMSIS" -I"/home/projeto/Workspace/MCU/Workspace/K64F-Fusion2/component/uart" -I"/home/projeto/Workspace/MCU/Workspace/K64F-Fusion2/utilities" -I"/home/projeto/Workspace/MCU/Workspace/K64F-Fusion2/component/serial_manager" -I"/home/projeto/Workspace/MCU/Workspace/K64F-Fusion2/component/lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


