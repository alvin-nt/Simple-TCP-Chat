#include <arpa/inet.h>
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

ssize_t TCPStream::send(const Package& package) {
	return package.send(*this);
}

Package TCPStream::receive() {
	char buff[Package::getPackageSize()];

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
