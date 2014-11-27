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
	TCPAcceptor ss = new TCPAcceptor(PORT);
	//TODO display date time log
	if(ss.start() != 0) {
		Utils::writeServerLog("CANNOT BIND PORT, EXITING");
		exit(1);
	} else {
		Utils::writeServerLog("SERVER STARTS");
		while (true) {
			ServerThread st = new ServerThread(ss.accept());
			ThreadPool.push_back(st);
		}
	}
}

DioskuriaServer::~DioskuriaServer() {
	// TODO Auto-generated destructor stub
}

