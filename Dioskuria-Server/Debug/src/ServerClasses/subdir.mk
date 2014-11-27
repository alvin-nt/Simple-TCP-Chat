################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ServerClasses/Group.cpp \
../src/ServerClasses/IO.cpp \
../src/ServerClasses/User.cpp 

OBJS += \
./src/ServerClasses/Group.o \
./src/ServerClasses/IO.o \
./src/ServerClasses/User.o 

CPP_DEPS += \
./src/ServerClasses/Group.d \
./src/ServerClasses/IO.d \
./src/ServerClasses/User.d 


# Each subdirectory must supply rules for building sources it contributes
src/ServerClasses/%.o: ../src/ServerClasses/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -m32 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


