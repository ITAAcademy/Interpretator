################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FCGI_Stream.cpp \
../src/SQLconector.cpp \
../src/cLang.cpp \
../src/codeclear.cpp \
../src/errorresponder.cpp \
../src/logfile.cpp \
../src/main.cpp 

OBJS += \
./src/FCGI_Stream.o \
./src/SQLconector.o \
./src/cLang.o \
./src/codeclear.o \
./src/errorresponder.o \
./src/logfile.o \
./src/main.o 

CPP_DEPS += \
./src/FCGI_Stream.d \
./src/SQLconector.d \
./src/cLang.d \
./src/codeclear.d \
./src/errorresponder.d \
./src/logfile.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I../__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


