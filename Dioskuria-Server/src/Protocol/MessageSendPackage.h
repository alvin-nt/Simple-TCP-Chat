#ifndef _MessagePackage_H
#define _MessagePackage_H

#include <string>
#include "Package.h"
#include "Protocol.h"

using std::string;

class MessageSendPackage : public Package
{
protected:
	/**
	 * the message
	 */
	string message;

public:
	/**
	 * Default constructor
	 */
	MessageSendPackage();

	/**
	 * Initializes the object with a message
	 * @param message the message
	 */
	MessageSendPackage(const string& message);

	/**
	 * Clones the package
	 * @param package the other {@link MessageSendPackage}
	 */
	MessageSendPackage(const MessageSendPackage& package);

	/**
	 * Destructor
	 */
	~MessageSendPackage();
	
	MessageSendPackage& operator=(const MessageSendPackage& rhs);

	/**
	 * Get the message as a {@link string} object
	 * @return constant reference to message
	 */
	const string& getMessage() const;

	/**
	 * Sets the message
	 * @param message the message object
	 */
	void setMessage(const string& message);

	/**
	 * Sends the package through a TCPStream object
	 * @param  stream the TCPStream object
	 * @return        number of bytes sent
	 */
	//virtual ssize_t MessageSendPackage::send(TCPStream& stream);
};

#endif
