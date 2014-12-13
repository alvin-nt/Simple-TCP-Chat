#include "MessageSendPackage.h"

#include <cstring>
#include <cassert>
#include <cstdio>
#include <cstdlib>

char MessageSendPackage::PACKAGE_NEXT = '1';
char MessageSendPackage::PACKAGE_END = '0';

size_t MessageSendPackage::maxMessageSize = dataSize - sizeof(PACKAGE_NEXT) - sizeof(recvName);
size_t MessageSendPackage::messageOffset = dataOffset + sizeof(PACKAGE_NEXT) + sizeof(recvName);

MessageSendPackage::MessageSendPackage(const string& receiver, const string& message):
 	Package(Protocol::messageSend)
{
	setReceiver(receiver);
    this->message = message;
}

MessageSendPackage::MessageSendPackage(const MessageSendPackage& package)
	: Package(package)
{
	memcpy(recvName, package.recvName, sizeof(recvName));
    this->message = package.message;
}

MessageSendPackage::MessageSendPackage(const MessageSendPackage&& package)
    : Package(package.packageType)
{
    this->packageTime = package.packageTime;
    memmove(recvName, package.recvName, sizeof(recvName));
    this->message = package.message;
}

MessageSendPackage::MessageSendPackage(const char* buff)
	: Package(buff)
{
	*this = buff;
}

MessageSendPackage::~MessageSendPackage()
{

}

void MessageSendPackage::resetData() {
	memset(recvName, 0, sizeof(recvName));
	message.clear();
}

const string& MessageSendPackage::getMessage() const {
	return message;
}

void MessageSendPackage::setMessage(const string& message) {
	this->message = message;
}

MessageSendPackage& MessageSendPackage::operator=(const MessageSendPackage& rhs)	
{
	// the compiler first invokes the operator= on {@link Package}, then this.
	if(this != &rhs) {
		memcpy(recvName, rhs.recvName, sizeof(recvName));
		this->message = rhs.message;
	}
	return *this;
}

void MessageSendPackage::operator=(const char* buff) {
	readData(buff);
}

void MessageSendPackage::setReceiver(const string& receiver) {
	string cpy = receiver.substr(0, Protocol::USERNAME_MAXLENGTH);

	memcpy(recvName, cpy.c_str(), cpy.length());
}

string MessageSendPackage::getReceiver() const {
	return string(recvName);
}

ssize_t MessageSendPackage::send(TCPStream& stream) const {
    size_t offset = 0;
    size_t remainder = message.length();
    ssize_t sentBytes = 0;

    char buff[getPackageSize()];
    while(remainder > 0) {
        memset(buff, 0, sizeof(buff));

        bool end = (remainder < maxMessageSize);
        size_t copySize = end ? maxMessageSize : remainder;

        // copy the string
        writeData(buff, end, offset, copySize);

        sentBytes += stream.send(buff, sizeof(buff));

        offset += copySize;
        remainder -= copySize;
    }

    return sentBytes;
}

void MessageSendPackage::receive(MessageSendPackage& package, TCPStream& stream) {
    char buff[getPackageSize()];

    stream.receive(buff, sizeof(buff));

    // read params
    int packageType = *((int*)&buff[0]);
    time_t packageTime = *((time_t*)&buff[4]);
    const char *recvName = &buff[dataOffset];
    char offset = buff[dataOffset + 1];

    if(packageType == Protocol::messageSend) {
        package.readData(buff);
        while(offset == PACKAGE_NEXT) {
            stream.receive(buff, sizeof(buff));
            
            packageType = *((int*)&buff[0]);
            packageTime = *((time_t*)&buff[4]);
            offset = buff[dataOffset + 1];

            assert(package.packageType == packageType);
            assert(package.packageTime == packageTime);

            assert(string(package.recvName) == string(recvName, Protocol::USERNAME_MAXLENGTH));

            package.readData(buff);
        }
    } else {
        //
    }
}

void MessageSendPackage::receivePackage(TCPStream& stream, char* buff)
{
    memset(buff, 0, getPackageSize());

    ssize_t readBytes = stream.receive(buff, getPackageSize());
    assert(readBytes > 0);
}

void MessageSendPackage::writeData(char* buff, bool end, int offset, int len) const {
    Package::writeData(buff);
    
    buff[dataOffset + sizeof(recvName)] = end ? PACKAGE_END : PACKAGE_NEXT;
    
    memcpy(&buff[dataOffset], recvName, sizeof(recvName));

    copy(message.begin() + offset, message.begin() + offset + len, &buff[messageOffset]);
}

void MessageSendPackage::readData(const char* buff) {
    Package::readData(buff);
    
    memcpy(recvName, &buff[dataOffset], sizeof(recvName));
    
    message += string(&buff[messageOffset], maxMessageSize);
}
