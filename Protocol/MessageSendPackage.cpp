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
	resetData();

	this->senderId = senderId;
	this->recvId = recvId;
	this->message = message;
}

MessageSendPackage::MessageSendPackage(const MessageSendPackage& package)
	: Package(package)
{
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
		this->resetData();

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

		size_t copySize;

		if(!end) {
			sprintf(buff, "%d%d%c%d%d", 
					packageType, (int)packageTime, '1', senderId, recvId);
			copySize = maxMessageSize;
		} else {
			sprintf(buff, "%d%d%c%d%d", 
					packageType, (int)packageTime, '0', senderId, recvId);
			copySize = remainder + 1;
		}

		// copy the string
		memcpy(&buff[dataOffset], &message.c_str()[offset], copySize);

		sentBytes += stream.send(buff, sizeof(buff));

		offset += copySize;
		remainder -= copySize;
	}

	return sentBytes;
}

MessageSendPackage* MessageSendPackage::receive(TCPStream& stream) {
	MessageSendPackage* newPackage;

	char buff[getPackageSize()];

	stream.receive(buff, sizeof(buff));

	// read params
	int packageType;
	time_t packageTime;
	char offset;
	int senderId;
	int recvId;

	sscanf(buff, "%d%d%c%d%d",
			&packageType, (int*)&packageTime, &offset, &senderId, &recvId);
	string message;

	if(packageType == Protocol::messageSend) {
		newPackage = new MessageSendPackage(senderId, recvId);
		newPackage->packageTime = packageTime;

		message += string(&buff[messageOffset], maxMessageSize);
		while(offset == PACKAGE_NEXT) {
			stream.receive(buff, sizeof(buff));

			sscanf(buff, "%d%d%c%d%d",
					&packageType, (int*)&packageTime, &offset, &senderId, &recvId);

			assert(newPackage->packageType == packageType);
			assert(newPackage->packageTime == packageTime);
			assert(newPackage->senderId == senderId);
			assert(newPackage->recvId == recvId);

			message += string(&buff[messageOffset], maxMessageSize);
		}

		newPackage->message = message;
	} else {
		newPackage = NULL;
	}

	return newPackage;
}

void MessageSendPackage::receivePackage(TCPStream& stream, char* buff)
{
	memset(buff, 0, getPackageSize());

	ssize_t readBytes = stream.receive(buff, getPackageSize());
	assert(readBytes > 0);
}
