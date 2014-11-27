#include "MessageSendPackage.h"
#include <vector>
#include <cstring>

using std::vector;

MessageSendPackage::MessageSendPackage(): 
 	Package(Protocol::messageSend) 
{

}

MessageSendPackage::MessageSendPackage(const string& message):
	Package(Protocol::messageSend)
{

}

MessageSendPackage::MessageSendPackage(const MessageSendPackage& package):
	Package(package)
{
	*this = package;
}

MessageSendPackage::~MessageSendPackage()
{

}

MessageSendPackage& MessageSendPackage::operator=(const MessageSendPackage& rhs)	
{
	if(this != &rhs) {
		this->message = rhs.message;
	}
	return *this;
}

ssize_t MessageSendPackage::send(TCPStream* stream) {
	int packageNum = 1;
	if(message.length() > dataSize) {
		while(dataSize * packageNum < message.length()) {
			packageNum++;
		}
	}

	vector<char[getPackageSize()]> messagePackages(packageNum);

	int offset = 0;
	for(int i = 0; i < packageNum; i++) {
		memset(messagePackages[i], 0, getPackageSize());

		if(i == packageNum-1) {
			sprintf(messagePackage[i], "%d%d%c", packageType, (int)packageTime, '1');
		} else {
			sprintf(messagePackage[i], "%d%d%c", packageType, (int)packageTime, '0');
		}

		// copy the string
	}

	ssize_t sent = stream.send(buff, getPackageSize());

	return sent;
}