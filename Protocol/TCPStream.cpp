#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <cassert>
#include <cstring>
#include "TCPStream.h"
#include "Package.h"

TCPStream::TCPStream(int sd, struct sockaddr_in* address) {
	char ip[50];
	inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr),
							ip, sizeof(ip)-1);
	
	m_peerIP = ip;
	m_peerPort = ntohs(address->sin_port);
}

TCPStream::TCPStream(const TCPStream& stream) {
	this->m_sd = stream.m_sd;
	this->m_peerIP = stream.m_peerIP;
	this->m_peerPort = stream.m_peerPort;
}

ssize_t TCPStream::send(const char* buff, size_t len) {
	return write(m_sd, buff, len);
}

ssize_t TCPStream::send(const Package& package) {
	return package.send(*this);
}

ssize_t TCPStream::receive(char* buff, size_t len, int timeout) {
	if(timeout <= 0) {
		return read(m_sd, buff, len);
	} else {
		if(waitForReadEvent(timeout)) {
			return read(m_sd, buff, len);
		}
	}
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
    fd_set sdset;
    struct timeval tv;

    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    FD_ZERO(&sdset);
    FD_SET(m_sd, &sdset);

    if (select(m_sd+1, &sdset, NULL, NULL, &tv) > 0)
    {
        return true;
    }

    return false;
}