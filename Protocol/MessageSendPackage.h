#ifndef _MessagePackage_H
#define _MessagePackage_H

#include <string>
#include "Package.h"
#include "Protocol.h"

using std::string;

class MessageSendPackage : public Package
{
protected:
	static char PACKAGE_NEXT;
	static char PACKAGE_END;
	/**
	 * userId of the sender
	 */
	int senderId;

	/**
	 * userId of the receiver
	 */
	int recvId;

	/**
	 * the message
	 */
	string message;

	/**
	 * maximum message size supported by ONE MessageSendPackage object
	 */
	static size_t maxMessageSize;
	static size_t messageOffset;
public:
	/**
	 * Initializes the object with a message
	 * @param senderId the userId of the sender
	 * @param recvId the userId of the receiver
	 * @param message the message
	 */
	MessageSendPackage(int senderId = -1, int recvId = -1, const string& message = "");

	/**
	 * Clones the package
	 * @param package the other {@link MessageSendPackage}
	 */
	MessageSendPackage(const MessageSendPackage& package);
        
        /**
         * Moves the package
         * @param rhs
         */
        MessageSendPackage(const MessageSendPackage&& package);

	/**
	 * Destructor
	 */
	~MessageSendPackage();
	
	/**
	 * Copies the content of the {@link MessageSendPackage} object to this
	 * @param rhs the {@link MessageSendPackage} object
	 */
	MessageSendPackage& operator=(const MessageSendPackage& rhs);
        
	/**
	 * Resets the data of this package
	 * Actions done:
	 * 	- nullify pointer to data, as it is not used
	 * 	- setting senderId to 0
	 * 	- setting recvId to 0
	 * 	- calling message.clear()
	 */
	void resetData();

	/**
	 * Get the message as a {@link string} object
	 * @return constant reference to message
	 */
	const string& getMessage() const;

	/**
	 * NOTE: unused
	 * @return NULL
	 */
	const char* getDataPtr();

	/**
	 * Sets the message
	 * @param message the message object
	 */
	void setMessage(const string& message);

	/**
	 * Sends the package through a {@link TCPStream} object
	 * @param  stream the {@link TCPStream} object
	 * @return number of bytes sent
	 */
	virtual ssize_t send(TCPStream& stream) const;

	/**
	 * Receives a MessageSendPackage through a {@link TCPStream} object
         * @param  package reference to package object
	 * @param  stream the {@link TCPStream} object
	 */
	static void receive(MessageSendPackage& package, TCPStream& stream);
private:
	/**
	 * Receives a package from a stream
	 * @param stream the {@link TCPStream} object
	 * @param buff   pointer to data buffer, assumed that the size is equal to {@link Package::getDataSize()}
	 */
	void receivePackage(TCPStream& stream, char* buff);
        
        /**
         * Writes the package data to the buffer
         * @param buff the data buffer
         * @param end indicates whether the package is reaching the end
         * @param offset character offset from the string
         * @param len the length of characters to be sent, defaults to maxMessageSize
         */
        void writeData(char* buff, bool end, int offset, int len = maxMessageSize) const;
        
        /**
         * Reads the package data from the buffer
         * @param buff the data buffer
         */
        void readData(char* buff);
};

#endif