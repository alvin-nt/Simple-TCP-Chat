// class source: http://vichargrave.com/network-programming-design-patterns-in-c/
#ifndef _TCPStream_H
#define _TCPStream_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

using namespace std;

// forward declaration
class Package;
class TCPStream
{
private:
	/**
	 * Socket number descriptor
	 */
	int			m_sd;

	/**
	 * IP of the peer
	 */
	string		m_peerIP;

	/**
	 * Port of the peer
	 */
	int			m_peerPort;
public:
	// let the elements be accessed from outside by other classes
	friend class TCPAcceptor;
	friend class TCPConnector;
	
	~TCPStream();
	
	// package functions
	ssize_t send(const Package& package);
	Package receive();

	// wrapper for native functions
	ssize_t send(const char* buffer, size_t len, int flags = 0);
	ssize_t receive(char* buffer, size_t len, int timeoutSec = 5, int flags = 0);

	/**
	 * Gets the IP of the peer as a std::string
	 * @return peerIP
	 */
	const string& getPeerIP() const;

	/**
	 * Gets the port of the peer
	 * @return peerPort
	 */
	int getPeerPort() const;
private:
	TCPStream(int sd, struct sockaddr_in* address);
	TCPStream();
	TCPStream(const TCPStream& stream); // TODO: cctor definition

	/**
	 * Used to wait for read to execute
	 *
	 * using select()
	 * @param  timeout length of waiting
	 * @return         true if the event is called within the timeout
	 */
	bool waitForReadEvent(int timeout);

	/**
	 * Sends a ping to the destination, and wait for response
	 * @param	timeout the time required for the ping to timeout
	 * @return true if the target responds, 
	 *         false if no response is caught within the timeout frame
	 */
	bool sendPing(int timeout);
};

#endif