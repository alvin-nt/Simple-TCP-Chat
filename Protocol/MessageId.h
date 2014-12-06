#ifndef _MessageId_H
#define _MessageId_H

#include <cstdio>
#include <ctime>

class MessageId {
public:
	static const char RECEIVER_USER = 'U';
	static const char RECEIVER_GROUP = 'G';
private:
	/**
	 * The userId of the sender
	 */
	int senderId;

	/**
	 * time of when the message is sent
	 */
	time_t messageTime;

	/**
	 * The userId of the receiver
	 */
	int receiverId;

	/**
	 * Type of the receiver
	 */
	char receiverType;

	/**
	 * not used, only for filler
	 */
	char empty[3];
public:
	/**
	 * Default constructor
	 */
	MessageId();
        
        /**
         * Parameterized constructor
         * @param senderId the userId of the sender
         * @param receiverId the userId/groupId of the receiver
         * @param receiverType the receiverType, as defined in RECIEVER_USER or RECIEVER_GROUP
         */
        MessageId(int senderId, int receiverId, char receiverType = RECEIVER_USER);

	MessageId(const MessageId& messageId);

        void operator=(const MessageId& rhs);
        
	int getSenderId() const;

	MessageId& setSenderId(int senderId);

	time_t getMessageTime() const;

	MessageId& setMessageTime(time_t messageTime);

	char getReceiverType() const;

	MessageId& setReceiverType(char receiverType);

	int getReceiverId() const;

	MessageId& setReceiverId(int receiverId);
};

#endif