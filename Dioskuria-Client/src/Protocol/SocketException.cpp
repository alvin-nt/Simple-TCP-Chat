#include "SocketException.h"

SocketException::SocketException(const string& message)
	: runtime_error(message) 
{
	
}

SocketException::SocketException(const char* message)
	: runtime_error(message)
{
	
}