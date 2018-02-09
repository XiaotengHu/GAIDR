################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/run/src/file/file.cpp 

OBJS += \
./src/run/src/file/file.o 

CPP_DEPS += \
./src/run/src/file/file.d 


# Each subdirectory must supply rules for building sources it contributes
src/run/src/file/%.o: ../src/run/src/file/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


