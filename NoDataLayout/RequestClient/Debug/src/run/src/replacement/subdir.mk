################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/run/src/replacement/replacement.cpp 

OBJS += \
./src/run/src/replacement/replacement.o 

CPP_DEPS += \
./src/run/src/replacement/replacement.d 


# Each subdirectory must supply rules for building sources it contributes
src/run/src/replacement/%.o: ../src/run/src/replacement/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


