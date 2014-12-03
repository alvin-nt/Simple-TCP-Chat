/*
 * DioskuriaServer.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "DioskuriaServer.h"
#include "ServerClasses/Utils.h"


using namespace std;

DioskuriaServer::DioskuriaServer(int PORT) {
	/*
	TCPAcceptor* ss = new TCPAcceptor(PORT);
	//TODO display date time log
	if(ss->start() != 0) {
		Utils::writeServerLog("CANNOT BIND PORT, EXITING");
		exit(1);
	} else {
		Utils::writeServerLog("SERVER STARTS");
		while (true) {
			TCPStream* stream = ss->accept();
			if (stream != NULL) {
				ServerThread* st = new ServerThread(stream);
				threadPool.push_back(st);
			}
			usleep(50);
		}
	} */
	ServerThread* st = new ServerThread();
	while (true) {
		usleep(50);
	}
}

DioskuriaServer::~DioskuriaServer() {
	// TODO Auto-generated destructor stub
}

