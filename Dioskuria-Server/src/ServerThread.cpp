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

void* ServerThread::run() {
	//TODO inisialisasi network i/o stream

	while (true) {
		//TODO main loop thread, process query by package
	}

	return NULL;
}
