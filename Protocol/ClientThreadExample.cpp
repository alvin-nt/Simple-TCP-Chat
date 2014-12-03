#include <cstring>
#include <iostream>
#include <functional>

#include "SocketException.h"
#include "ClientThreadExample.h"
#include "Package.h"

ClientThreadExample::ClientThreadExample(TCPStream* stream)
{
	this->stream = stream;
	m_alive = false;
}

ClientThreadExample::ClientThreadExample(ClientThreadExample&& other) 
	: m_thread(std::move(other.m_thread)),
	  stream(other.stream),
	  m_alive(other.m_alive)
{

}

void ClientThreadExample::threadRoutine() {
	char buff[Package::getPackageSize()];

	while(m_alive) {
		memset(buff, 0, sizeof(buff));

		try {
			cout << "Listening for package" << endl;
			stream->receive(buff, sizeof(buff), 0);

			Package tempPackage = buff;
			cout << "Package type: " << tempPackage.getPackageType() << endl;
			cout << "Package time: " << tempPackage.getPackageTime() << endl;

			// filter based on packageType
			switch(tempPackage.getPackageType()) {
				case Protocol::pingSend:
					tempPackage.setPackageType(Protocol::pingReceive);
					tempPackage.resetTime();

					stream->send(tempPackage);
				break;
			}
		} catch (SocketException& e) {
			cerr << "Caught SocketException on thread " 
				 << m_thread.get_id() << ": "
				 << e.what() << endl;
		}
	}		
}

void ClientThreadExample::start() {
	m_alive = true;
	m_thread = std::thread(&ClientThreadExample::threadRoutine, this);
}

ClientThreadExample::~ClientThreadExample()
{
	if(stream != NULL)
		delete stream;
	m_thread.join();
}

bool ClientThreadExample::isRunning() const {
	return m_alive;
}

ssize_t ClientThreadExample::send(const Package& package) {
	return stream->send(package);
}

ssize_t ClientThreadExample::send(const char* buff, int len) {
	return stream->send(buff, len);
}

int ClientThreadExample::getPort() const
{
	return stream->getPeerPort();
}