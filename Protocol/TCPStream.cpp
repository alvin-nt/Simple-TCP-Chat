#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <exception>
#include <cassert>
#include <cstring>

#include "TCPStream.h"
#include "Package.h"
#include "SocketException.h"

TCPStream::TCPStream(int sd, struct sockaddr_in* address) {
	char ip[50];
	inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr),
							ip, sizeof(ip)-1);
	
	m_sd = sd;
	m_peerIP = ip;
	m_peerPort = ntohs(address->sin_port);
}

TCPStream::TCPStream(const TCPStream& stream) {
	this->m_sd = stream.m_sd;
	this->m_peerIP = stream.m_peerIP;
	this->m_peerPort = stream.m_peerPort;
}

ssize_t TCPStream::send(const char* buff, size_t len, int flags) {
	return ::send(m_sd, buff, len, flags);
}

ssize_t TCPStream::send(const Package& package) {
	return package.send(*this);
}

ssize_t TCPStream::receive(char* buff, size_t len, int timeoutSec, int flags) {
	ssize_t recvBytes = -1;

	if(timeoutSec <= 0) { // no error checking
		recvBytes = ::recv(m_sd, buff, len, flags);
	} else {
		if(waitForReadEvent(timeoutSec)) {
			recvBytes = ::recv(m_sd, buff, len, flags);
		} else {
			// send a isConnected package. if no response, then throw SocketException
			if(sendPing(timeoutSec)) {
				recvBytes = 0;
			} else {
				throw SocketException("Disconnected from server.");
			}
		}
	}

	return recvBytes;
}

bool TCPStream::sendPing(int timeout) {
	bool ret;
	Package pingPackage(Protocol::pingSend);

	pingPackage.send(*this);

	// langsung receive
	if(waitForReadEvent(timeout)) {
		char buff[Package::getPackageSize()];
		memset(buff, 0, sizeof(buff));

		assert(recv(m_sd, buff, sizeof(buff), 0) == sizeof(buff));

		// TODO: some validation routine here
		ret = true;
	}

	return ret;
}

Package TCPStream::receive() {
	char buff[Package::getPackageSize()];
	memset(buff, 0, sizeof(buff));

	assert(receive(buff, sizeof(buff)) == sizeof(buff));
	Package package(buff);

	return package;
}

TCPStream::~TCPStream() {
	close(m_sd);
}

const string& TCPStream::getPeerIP() const {
	return m_peerIP;
}

int TCPStream::getPeerPort() const {
	return m_peerPort;
}

bool TCPStream::waitForReadEvent(int timeout)
{
	// fileDescriptor for socket, to check for READ event
    fd_set sdset;
    struct timeval tv;

    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    FD_ZERO(&sdset);
    FD_SET(m_sd, &sdset);

    int retval = select(m_sd+1, &sdset, NULL, NULL, &tv);
    bool status = (retval > 0);

   	return status;
}