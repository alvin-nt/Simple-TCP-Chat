/* 
 * File:   MessageRecvPackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 9:41 PM
 */

#include "MessageRecvPackage.h"
#include <cstring>

using namespace std;

MessageRecvPackage::MessageRecvPackage(const MessageId& messageId, const string& message) 
    : MessageIdPackage(messageId, Protocol::messageRecv), message(message)
{
}

MessageRecvPackage::MessageRecvPackage(const MessageRecvPackage& orig) 
    : MessageIdPackage(orig.messageId, orig.packageType), message(orig.message)
{   
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

const string& MessageRecvPackage::getMessage() const {
    return message;
}

void MessageRecvPackage::setMessage(const string& message) {
    this->message = message;
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

void MessageRecvPackage::writeData(char* buff, bool end, int offset, int len) const {
    MessageIdPackage::writeData(buff);
    
    buff[dataOffset + sizeof(messageId)] = end ? PACKAGE_END : PACKAGE_NEXT;
    memcpy(&buff[messageOffset], &message.c_str()[offset], len);
}

void MessageRecvPackage::readData(const char* buff) {
    MessageIdPackage::readData(buff);
    
    message += string(&buff[messageOffset], maxMessageSize);
}