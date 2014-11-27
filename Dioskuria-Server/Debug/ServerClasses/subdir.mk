################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ServerClasses/Group.cpp \
../ServerClasses/IO.cpp \
../ServerClasses/User.cpp 

OBJS += \
./ServerClasses/Group.o \
./ServerClasses/IO.o \
./ServerClasses/User.o 

CPP_DEPS += \
./ServerClasses/Group.d \
./ServerClasses/IO.d \
./ServerClasses/User.d 


# Each subdirectory must supply rules for building sources it contributes
ServerClasses/%.o: ../ServerClasses/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -m32 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


