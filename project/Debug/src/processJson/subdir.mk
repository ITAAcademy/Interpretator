################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/processJson/addNewtask.cpp \
../src/processJson/addTestsToTask.cpp \
../src/processJson/getJson.cpp \
../src/processJson/mergeUtestsAndTask.cpp \
../src/processJson/start.cpp 

OBJS += \
./src/processJson/addNewtask.o \
./src/processJson/addTestsToTask.o \
./src/processJson/getJson.o \
./src/processJson/mergeUtestsAndTask.o \
./src/processJson/start.o 

CPP_DEPS += \
./src/processJson/addNewtask.d \
./src/processJson/addTestsToTask.d \
./src/processJson/getJson.d \
./src/processJson/mergeUtestsAndTask.d \
./src/processJson/start.d 


# Each subdirectory must supply rules for building sources it contributes
src/processJson/%.o: ../src/processJson/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../__GXX_EXPERIMENTAL_CXX0X__ -I/usr/include/mysql -I/usr/include/mysql++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


