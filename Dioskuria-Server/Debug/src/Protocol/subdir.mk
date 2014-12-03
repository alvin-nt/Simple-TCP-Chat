################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Protocol/MessageSendPackage.cpp \
../src/Protocol/Package.cpp \
../src/Protocol/TCPAcceptor.cpp \
../src/Protocol/TCPConnector.cpp \
../src/Protocol/TCPStream.cpp 

OBJS += \
./src/Protocol/MessageSendPackage.o \
./src/Protocol/Package.o \
./src/Protocol/TCPAcceptor.o \
./src/Protocol/TCPConnector.o \
./src/Protocol/TCPStream.o 

CPP_DEPS += \
./src/Protocol/MessageSendPackage.d \
./src/Protocol/Package.d \
./src/Protocol/TCPAcceptor.d \
./src/Protocol/TCPConnector.d \
./src/Protocol/TCPStream.d 


# Each subdirectory must supply rules for building sources it contributes
src/Protocol/%.o: ../src/Protocol/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -m32 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


