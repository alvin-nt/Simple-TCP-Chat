// class source: http://vichargrave.com/network-programming-design-patterns-in-c/
#ifndef _TCPAcceptor_H
#define _TCPAcceptor_H

#include <string>
#include <netinet/in.h>
#include "TCPStream.h"

using namespace std;

/**
 * TCPAcceptor is used to listen on connection.
 *
 * Used by servers that need to actively listen to a port
 */
class TCPAcceptor {
private:
	/**
	 * Local socket descriptor number
	 */
	int			m_lsd;
	/**
	 * target address
	 */
	string		m_address;
	/**
	 * target port
	 */
	int			m_port;
	/**
	 * is listening?
	 */
	bool		m_listening;
public:
	TCPAcceptor(int port, const char* address="");
	~TCPAcceptor();
	
	/**
	 * Starts a connection
	 * @return number indicating the connection stat. 0 is ok, else means something wrong's happening
	 */
	int			start();
	/**
	 * 
	 * @return pointer to a new TCPStream
	 */
	TCPStream*	accept();
	
private:
	TCPAcceptor() {};
};

#endif