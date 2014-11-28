#include "MessageSendPackage.h"
#include <cstring>

MessageSendPackage::MessageSendPackage(int senderId, int recvId): 
 	Package(Protocol::messageSend)
{
	resetData();

	this->senderId = senderId;
	this->recvId = recvId;
}

MessageSendPackage::MessageSendPackage(const string& message):
	Package(Protocol::messageSend)
{
	resetData();

	this->senderId = senderId;
	this->recvId = recvId;
	this->message = message;
}

MessageSendPackage::MessageSendPackage(const MessageSendPackage& package)
{
	*this = package;
}

MessageSendPackage::~MessageSendPackage()
{

}

void MessageSendPackage::resetData() {
	if(data != NULL) {
		delete data;
		data = NULL;
	}

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

ssize_t MessageSendPackage::send(TCPStream& stream) {
	size_t offset = 0;
	size_t remainder = message.length();
	ssize_t sentBytes = 0;

	char buff[getPackageSize()];
	while(remainder > 0) {
		memset(buff, 0, sizeof(buff));

		bool end = (remainder < maxMessageSize);

		if(!end) {
			sprintf(buff, "%d%d%c%d%d", 
					packageType, (int)packageTime, '1', senderId, recvId);
		} else {
			sprintf(buff, "%d%d%c%d%d", 
					packageType, (int)packageTime, '0', senderId, recvId);
		}

		// copy the string
		size_t copiedChars = memcpy(&messagePackages[i][dataOffset], 
									&message.c_str()[offset], 
									end ? remainder + 1 : maxMessageSize);
		assert(copiedChars > 0);

		sentBytes += stream.send(buff, sizeof(buff));

		offset += copiedChars;
		remainder -= copiedChars;
	}

	return sentBytes;
}

MessageSendPackage* MessageSendPackage::receive(TCPStream& stream) {
	MessageSendPackage* newPackage;

	char buff[getPackageSize()];

	receivePackage(buff);

	// read params
	int packageType;
	time_t packageTime;
	char offset;
	int senderId;
	int recvId;

	sscanf(buff, "%d%d%c%d%d",
			&packageType, &packageTime, &offset, &senderId, &recvId);
	string message;

	if(packageType == Protocol::messageSend) {
		newPackage = new MessageSendPackage(senderId, recvId);
		newPackage->packageTime = packageTime;

		message += string(&buff[messageOffset], maxMessageSize);
		while(offset == PACKAGE_NEXT) {
			receivePackage(buff);

			sscanf(buff, "%d%d%c%d%d",
					&packageType, &packageTime, &offset, &senderId, &recvId);

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
