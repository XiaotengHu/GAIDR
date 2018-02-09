################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/run/src/redis/redis.cpp 

OBJS += \
./src/run/src/redis/redis.o 

CPP_DEPS += \
./src/run/src/redis/redis.d 


# Each subdirectory must supply rules for building sources it contributes
src/run/src/redis/%.o: ../src/run/src/redis/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


