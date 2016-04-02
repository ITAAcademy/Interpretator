################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/functions/replaceSlashTabsParagBreakets.cpp 

OBJS += \
./src/functions/replaceSlashTabsParagBreakets.o 

CPP_DEPS += \
./src/functions/replaceSlashTabsParagBreakets.d 


# Each subdirectory must supply rules for building sources it contributes
src/functions/%.o: ../src/functions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../__GXX_EXPERIMENTAL_CXX0X__ -I/usr/include/mysql -I/usr/include/mysql++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


