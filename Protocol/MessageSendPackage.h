#ifndef _MessagePackage_H
#define _MessagePackage_H

#include <string>
#include "Package.h"
#include "Protocol.h"

using std::string;

class MessageSendPackage : public Package
{
protected:
	static char PACKAGE_NEXT = '1';
	static char PACKAGE_END = '0';
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
	static int maxMessageSize = dataSize - sizeof(PACKAGE_NEXT) - sizeof(senderId) - sizeof(recvId);
	static int messageOffset = dataOffset + sizeof(PACKAGE_NEXT) + sizeof(senderId) + sizeof(recvId);
public:
	/**
	 * Default constructor
	 * @param senderId the userId of the sender
	 * @param recvId the userId of the receiver
	 */
	MessageSendPackage(int senderId, int recvId);

	/**
	 * Initializes the object with a message
	 * @param senderId the userId of the sender
	 * @param recvId the userId of the receiver
	 * @param message the message
	 */
	MessageSendPackage(int senderId, int recvId, const string& message);

	/**
	 * Clones the package
	 * @param package the other {@link MessageSendPackage}
	 */
	MessageSendPackage(const MessageSendPackage& package);

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
	 * @param  stream the {@link TCPStream} object
	 * @return the new pointer to {@link MessageSendPackage} object
	 */
	static MessageSendPackage* receive(TCPStream& stream);
private:
	/**
	 * Receives a package from a stream
	 * @param stream the {@link TCPStream} object
	 * @param buff   pointer to data buffer, assumed that the size is equal to {@link Package::getDataSize()}
	 */
	void receivePackage(TCPStream& stream, char* buff);
};

#endif