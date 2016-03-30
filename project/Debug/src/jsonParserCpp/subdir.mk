################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/jsonParserCpp/isValidFields.cpp \
../src/jsonParserCpp/parseAddUtest.cpp \
../src/jsonParserCpp/parseChekableArgIndexes.cpp 

OBJS += \
./src/jsonParserCpp/isValidFields.o \
./src/jsonParserCpp/parseAddUtest.o \
./src/jsonParserCpp/parseChekableArgIndexes.o 

CPP_DEPS += \
./src/jsonParserCpp/isValidFields.d \
./src/jsonParserCpp/parseAddUtest.d \
./src/jsonParserCpp/parseChekableArgIndexes.d 


# Each subdirectory must supply rules for building sources it contributes
src/jsonParserCpp/%.o: ../src/jsonParserCpp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I../__GXX_EXPERIMENTAL_CXX0X__ -I/usr/include/mysql -I/usr/include/mysql++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


