################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../UART.c \
../gpio.c \
../lcd.c \
../main.c \
../seven_segment.c 

OBJS += \
./ADC.o \
./UART.o \
./gpio.o \
./lcd.o \
./main.o \
./seven_segment.o 

C_DEPS += \
./ADC.d \
./UART.d \
./gpio.d \
./lcd.d \
./main.d \
./seven_segment.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


