################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/run/src/request/request.cpp 

OBJS += \
./src/run/src/request/request.o 

CPP_DEPS += \
./src/run/src/request/request.d 


# Each subdirectory must supply rules for building sources it contributes
src/run/src/request/%.o: ../src/run/src/request/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


