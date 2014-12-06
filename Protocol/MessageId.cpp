#include "MessageId.h"

MessageId::MessageId() {
    senderId = 0;
    messageTime = std::time(NULL);
    receiverId = 0;
    receiverType = RECEIVER_USER;

    for(int i = 0; i < sizeof(empty); i++) {
            empty[i] = '\0';
    }
};

MessageId::MessageId(int senderId, int receiverId, char receiverType) {
    this->senderId = senderId;
    messageTime = std::time(NULL);
    this->receiverId = receiverId;
    this->receiverType = receiverType;
    
    for(int i = 0; i < sizeof(empty); i++) {
        empty[i] = '\0';
    }
}

MessageId::MessageId(const MessageId& messageId) {
    *this = messageId;
};

void MessageId::operator=(const MessageId& rhs) {
    if(this != &rhs) {
        senderId = rhs.senderId;
        messageTime = rhs.messageTime;
        receiverId = rhs.receiverId;
        receiverType = rhs.receiverType;
    }
}

int MessageId::getSenderId() const {
	return senderId;
}

MessageId& MessageId::setSenderId(int senderId) {
	this->senderId = senderId;
	return *this;
};

time_t MessageId::getMessageTime() const {
	return messageTime;
}

MessageId& MessageId::setMessageTime(time_t messageTime) {
	this->messageTime = messageTime;
	return *this;
};

MessageId& MessageId::setReceiverType(char receiverType) {
	this->receiverType = receiverType;
	return *this;
};

MessageId& MessageId::setReceiverId(int receiverId) {
	this->receiverId = receiverId;
	return *this;
};