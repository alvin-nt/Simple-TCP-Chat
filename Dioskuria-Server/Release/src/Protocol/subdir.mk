################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Protocol/GroupCreatePackage.cpp \
../src/Protocol/GroupInfoPackage.cpp \
../src/Protocol/GroupJoinPackage.cpp \
../src/Protocol/MessageId.cpp \
../src/Protocol/MessageIdPackage.cpp \
../src/Protocol/MessageRecvPackage.cpp \
../src/Protocol/MessageSendPackage.cpp \
../src/Protocol/Package.cpp \
../src/Protocol/SimpleMessagePackage.cpp \
../src/Protocol/SocketException.cpp \
../src/Protocol/TCPAcceptor.cpp \
../src/Protocol/TCPConnector.cpp \
../src/Protocol/TCPStream.cpp \
../src/Protocol/UserIdPackage.cpp \
../src/Protocol/UserInitPackage.cpp 

OBJS += \
./src/Protocol/GroupCreatePackage.o \
./src/Protocol/GroupInfoPackage.o \
./src/Protocol/GroupJoinPackage.o \
./src/Protocol/MessageId.o \
./src/Protocol/MessageIdPackage.o \
./src/Protocol/MessageRecvPackage.o \
./src/Protocol/MessageSendPackage.o \
./src/Protocol/Package.o \
./src/Protocol/SimpleMessagePackage.o \
./src/Protocol/SocketException.o \
./src/Protocol/TCPAcceptor.o \
./src/Protocol/TCPConnector.o \
./src/Protocol/TCPStream.o \
./src/Protocol/UserIdPackage.o \
./src/Protocol/UserInitPackage.o 

CPP_DEPS += \
./src/Protocol/GroupCreatePackage.d \
./src/Protocol/GroupInfoPackage.d \
./src/Protocol/GroupJoinPackage.d \
./src/Protocol/MessageId.d \
./src/Protocol/MessageIdPackage.d \
./src/Protocol/MessageRecvPackage.d \
./src/Protocol/MessageSendPackage.d \
./src/Protocol/Package.d \
./src/Protocol/SimpleMessagePackage.d \
./src/Protocol/SocketException.d \
./src/Protocol/TCPAcceptor.d \
./src/Protocol/TCPConnector.d \
./src/Protocol/TCPStream.d \
./src/Protocol/UserIdPackage.d \
./src/Protocol/UserInitPackage.d 


# Each subdirectory must supply rules for building sources it contributes
src/Protocol/%.o: ../src/Protocol/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -D__cplusplus=201103L -O3 -Wall -c -fmessage-length=0 -m32 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


