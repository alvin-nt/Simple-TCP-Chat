/* 
 * File:   MessageRecvPackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 9:41 PM
 */

#include "MessageRecvPackage.h"
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

MessageRecvPackage::MessageRecvPackage(const string& sender, time_t messageTime, const string& message)
    : Package(Protocol::messageRecv), message(message)
{
	string cpy = sender.substr(0, Protocol::USERNAME_MAXLENGTH);
	copy(cpy.begin(), cpy.end(), this->sender);

	this->messageTime = messageTime;
}

MessageRecvPackage::MessageRecvPackage(const MessageRecvPackage& orig) 
    : Package(orig), messageTime(orig.messageTime), message(orig.message)
{   
	copy(orig.sender, orig.sender + sizeof(sender), sender);
}

MessageRecvPackage::MessageRecvPackage(const char* buff)
	: Package(buff)
{
	readData(buff);
}

MessageRecvPackage::~MessageRecvPackage() 
{
}

void MessageRecvPackage::operator=(const MessageRecvPackage& rhs) {
    if(this != &rhs) {
        message = rhs.message;
    }
}

void MessageRecvPackage::operator=(const char* buff) {
    readData(buff);
}

void MessageRecvPackage::setMessageSender(const string& sender) {
	setMessageSender(sender.substr(0, sizeof(sender)).c_str());
}

void MessageRecvPackage::setMessageSender(const char* sender) {
	copy(sender, sender + sizeof(this->sender), this->sender);
}

string MessageRecvPackage::getMessageSender() const {
	return string(sender, sizeof(sender));
}

const string& MessageRecvPackage::getMessage() const {
    return message;
}

void MessageRecvPackage::setMessage(const string& message) {
    this->message = message;
}

time_t MessageRecvPackage::getMessageTime() const {
	return messageTime;
}

void MessageRecvPackage::setMessageTime(time_t messageTime) {
	this->messageTime = messageTime;
}

ssize_t MessageRecvPackage::send(TCPStream& stream) const {
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

ssize_t MessageRecvPackage::receive(MessageRecvPackage& package, TCPStream& stream) {
    char buff[getPackageSize()];

    stream.receive(buff, sizeof(buff));

    ssize_t recvBytes = 0;

    // read params
    int packageType = *((int*)&buff[0]);
    time_t packageTime = *((time_t*)&buff[4]);
    const char *sender = &buff[dataOffset];

    int offsetMarkerPos = messageOffset - 1 - sizeof(messageTime);
    char offset = buff[offsetMarkerPos];

	package.readData(buff);
	while(offset == PACKAGE_NEXT) {
		stream.receive(buff, sizeof(buff));

		packageType = *((int*)&buff[0]);
		packageTime = *((time_t*)&buff[4]);
		offset = buff[offsetMarkerPos];

		assert(package.packageType == packageType);
		assert(package.packageTime == packageTime);

		assert(string(package.sender, sizeof(package.sender)) == string(sender, Protocol::USERNAME_MAXLENGTH));

		package.readData(buff);
	}

    return recvBytes;
}

void MessageRecvPackage::writeData(char* buff, bool end, int offset, int len) const {
    Package::writeData(buff);
    
    memcpy(&buff[dataOffset], sender, sizeof(sender));
    memcpy(&buff[dataOffset + sizeof(sender)], &messageTime, sizeof(messageTime));

    int offsetMarkerPos = messageOffset - 1 - sizeof(messageTime);
    buff[offsetMarkerPos] = end ? PACKAGE_END : PACKAGE_NEXT;

    memcpy(&buff[messageOffset], &message.c_str()[offset], len);
}

void MessageRecvPackage::readData(const char* buff) {
    Package::readData(buff);
    
    copy(&buff[dataOffset], &buff[dataOffset] + sizeof(sender), sender);

    time_t* msgTimePtr = (time_t*)&buff[dataOffset + sizeof(sender)];
    messageTime = *msgTimePtr;

    message += string(&buff[messageOffset], maxMessageSize);
}
