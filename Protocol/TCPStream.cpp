#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <exception>
#include <cassert>
#include <cstring>
#include <iostream>

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
	int sent = ::send(m_sd, buff, len, flags);
	
	cout << "Sent " << sent << " bytes" << endl;

	return sent;
}

ssize_t TCPStream::send(const Package& package) {
	return package.send(*this);
}

ssize_t TCPStream::receive(char* buff, size_t len, int flags) {
	ssize_t recvBytes = recv(m_sd, buff, len, flags);

	if(recvBytes == 0)
		throw SocketException("Stream closed.");
	else if(recvBytes == -1)
		throw SocketException("Stream error.");

	return recvBytes;
}

Package TCPStream::receive() {
	char buff[Package::getPackageSize()];
	memset(buff, 0, sizeof(buff));

	assert((unsigned)receive(buff, sizeof(buff)) == sizeof(buff));
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
