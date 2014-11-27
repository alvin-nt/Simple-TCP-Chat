/*
 * ServerThread.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "ServerThread.h"

ServerThread::ServerThread(TCPStream* passedsocket) {
	socket = passedsocket;
	start();
}

ServerThread::~ServerThread() {
	// TODO Auto-generated destructor stub
}

void ServerThread::*run() {
	std::cout << "AAA" << std::endl;
	return NULL;
}
