#ifndef _SocketException_H
#define _SocketException_H

#include <exception>
#include <stdexcept>
#include <string>

using namespace std;

class SocketException : public runtime_error {

public:
	explicit SocketException(const string& message);
	explicit SocketException(const char* message);
};

#endif