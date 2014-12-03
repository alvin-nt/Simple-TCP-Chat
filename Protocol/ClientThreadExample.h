#ifndef _ClientThreadExample_H
#define _ClientThreadExample_H

#include <future>
#include <thread>

#include "TCPStream.h"

using namespace std;

class ClientThreadExample {
private:
	TCPStream* stream;

	bool m_alive;
public:
	ClientThreadExample(TCPStream* stream);
	// move constructor
	ClientThreadExample(ClientThreadExample&&);
	~ClientThreadExample();

	bool isRunning() const;

	void start();

	ssize_t send(const Package&);

	ssize_t send(const char*, int);

	int getPort() const;
private:
	void threadRoutine();

	thread m_thread;
};

#endif