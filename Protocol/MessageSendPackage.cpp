#include "MessageSendPackage.h"
#include <cstring>
#include <cassert>
#include <cstdio>
#include <cstdlib>

char MessageSendPackage::PACKAGE_NEXT = '1';
char MessageSendPackage::PACKAGE_END = '0';

size_t MessageSendPackage::maxMessageSize = dataSize - sizeof(PACKAGE_NEXT) - sizeof(senderId) - sizeof(recvId);
size_t MessageSendPackage::messageOffset = dataOffset + sizeof(PACKAGE_NEXT) + sizeof(senderId) + sizeof(recvId);

MessageSendPackage::MessageSendPackage(int senderId, int recvId, const string& message): 
 	Package(Protocol::messageSend)
{
    this->senderId = senderId;
    this->recvId = recvId;
    this->message = message;
}

MessageSendPackage::MessageSendPackage(const MessageSendPackage& package)
	: Package(package)
{
    this->message = package.message;
}

MessageSendPackage::MessageSendPackage(const MessageSendPackage&& package)
    : Package(package.packageType)
{
    this->packageTime = package.packageTime;
    this->senderId = package.senderId;
    this->recvId = package.recvId;
    this->message = package.message;
}

MessageSendPackage::~MessageSendPackage()
{

}

void MessageSendPackage::resetData() {
	senderId = 0;
	recvId = 0;
	message.clear();
}

const string& MessageSendPackage::getMessage() const {
	return message;
}

void MessageSendPackage::setMessage(const string& message) {
	this->message = message;
}

const char* MessageSendPackage::getDataPtr() {
	// not used
	return NULL;
}

MessageSendPackage& MessageSendPackage::operator=(const MessageSendPackage& rhs)	
{
	// the compiler first invokes the operator= on {@link Package}, then this.
	if(this != &rhs) {
		this->senderId = rhs.senderId;
		this->recvId = rhs.recvId;
		this->message = rhs.message;
	}
	return *this;
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
    int senderId = *((int*)&buff[dataOffset]);
    int recvId = *((int*)&buff[dataOffset + 4]);
    char offset = buff[dataOffset + 8];

    if(packageType == Protocol::messageSend) {
        package.readData(buff);
        while(offset == PACKAGE_NEXT) {
            stream.receive(buff, sizeof(buff));
            
            packageType = *((int*)&buff[0]);
            packageTime = *((time_t*)&buff[4]);
            senderId = *((int*)&buff[dataOffset]);
            recvId = *((int*)&buff[dataOffset + 4]);
            offset = buff[dataOffset + 8];

            assert(package.packageType == packageType);
            assert(package.packageTime == packageTime);
            assert(package.senderId == senderId);
            assert(package.recvId == recvId);

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
    
    int* ptrSenderId = (int*)&buff[dataOffset];
    *ptrSenderId = senderId;
    
    int* ptrReceiverId = (int*)&buff[dataOffset + sizeof(senderId)];
    *ptrReceiverId = recvId;
    
    char* ptrReceiverType = &buff[dataOffset + sizeof(senderId) + sizeof(recvId)];
    *ptrReceiverType = end ? PACKAGE_END : PACKAGE_NEXT;
    
    memcpy(&buff[messageOffset], &message.c_str()[offset], len);
}

void MessageSendPackage::readData(char* buff) {
    Package::readData(buff);
    
    int* ptrSenderId = (int*)&buff[dataOffset];
    senderId = *ptrSenderId;
    
    int* ptrReceiverId = (int*)&buff[dataOffset + sizeof(senderId)];
    recvId = *ptrReceiverId;
    
    char* ptrMessage = &buff[messageOffset];
    message += string(ptrMessage, maxMessageSize);
}