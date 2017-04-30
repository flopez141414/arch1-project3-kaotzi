################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../newer.c 

OBJS += \
./newer.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 C Compiler'
	C:\axampp\msp430tools\msp430-toolchain-win-x86-3.0\bin\msp430-gcc -O0 -g -Wall -mmcu=msp430g2553 -std=gnu89 -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


