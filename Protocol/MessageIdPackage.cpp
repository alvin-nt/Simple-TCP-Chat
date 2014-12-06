/* 
 * File:   MessageIdPackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 6:47 AM
 */

#include "MessageIdPackage.h"
#include <cstring>

MessageIdPackage::MessageIdPackage(const MessageId& messageId, int packageType) 
    : Package(packageType), messageId(messageId)
{
}

MessageIdPackage::MessageIdPackage(const MessageIdPackage& orig) 
    : Package(orig), messageId(orig.messageId)
{
}

MessageIdPackage::~MessageIdPackage() {
}

MessageId& MessageIdPackage::getMessageId() {
    return messageId;
}

const MessageId& MessageIdPackage::getConstMessageId() const {
    return messageId;
}

void MessageIdPackage::setMessageId(const MessageId& messageId) {
    this->messageId = messageId;
}

void MessageIdPackage::operator=(const MessageIdPackage& rhs) {
    if(this != &rhs) {
        this->messageId = rhs.messageId;
    }
}

void MessageIdPackage::operator=(const char* buff) {
    readData(buff);
}

void MessageIdPackage::writeData(char* buff) const {
    Package::writeData(buff);
    
    std::memcpy(&buff[dataOffset], &messageId, sizeof(messageId));
}

void MessageIdPackage::readData(const char* buff) {
    Package::readData(buff);
    
    std::memcpy(&messageId, &buff[dataOffset], sizeof(messageId));
}