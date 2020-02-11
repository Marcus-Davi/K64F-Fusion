################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/peripherals.c \
../board/pin_mux.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/peripherals.o \
./board/pin_mux.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/peripherals.d \
./board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/board" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/source" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/drivers" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/device" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/CMSIS" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/component/uart" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/utilities" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/component/serial_manager" -I"/home/marcus/Workspace/MCU/NXP/Workspace/K64F-Controle/component/lists" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


