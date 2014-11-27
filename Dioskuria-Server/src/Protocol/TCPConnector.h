// class source: http://vichargrave.com/network-programming-design-patterns-in-c/

#ifndef _TCPConnector_H
#define _TCPConnector_H

#include <netinet/in.h>
#include "TCPStream.h"

/**
 * TCPConnector class is used to connect to a listening port on a server.
 *
 * Usually used by the client
 */
class TCPConnector
{
public:
	TCPStream* connect(int port, const char* server);

private:
	int resolveHostName(const char* hostname, struct in_addr* addr);
};

#endif