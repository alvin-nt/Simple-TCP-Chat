################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DioskuriaServer.cpp \
../src/ServerThread.cpp \
../src/main.cpp 

OBJS += \
./src/DioskuriaServer.o \
./src/ServerThread.o \
./src/main.o 

CPP_DEPS += \
./src/DioskuriaServer.d \
./src/ServerThread.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -D__cplusplus=201103L -O0 -g3 -Wall -c -fmessage-length=0 -m32 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


