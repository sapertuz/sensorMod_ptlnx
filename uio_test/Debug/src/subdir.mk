################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SensorMod.c \
../src/xil_uio.c \
../src/xil_uio_test.c 

OBJS += \
./src/SensorMod.o \
./src/xil_uio.o \
./src/xil_uio_test.o 

C_DEPS += \
./src/SensorMod.d \
./src/xil_uio.d \
./src/xil_uio_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 Linux gcc compiler'
	arm-linux-gnueabihf-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


