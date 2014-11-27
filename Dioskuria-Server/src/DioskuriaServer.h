/*
 * DioskuriaServer.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef SRC_DIOSKURIASERVER_H_
#define SRC_DIOSKURIASERVER_H_

#include "ServerThread.h"
#include "TCPAcceptor.h"
#include <vector>

class DioskuriaServer {
public:
	DioskuriaServer(int PORT);
	virtual ~DioskuriaServer();

	//static server wide variables here
	static std::vector<ServerThread> ThreadPool;
};

#endif /* SRC_DIOSKURIASERVER_H_ */
