/*
 * DioskuriaServer.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef SRC_DIOSKURIASERVER_H_
#define SRC_DIOSKURIASERVER_H_

#include "ServerThread.h"
#include "Protocol/TCPAcceptor.h"
#include "globals.h"
#include <vector>

using namespace std;

class DioskuriaServer {
public:
	DioskuriaServer(int PORT);
	virtual ~DioskuriaServer();
	void loadGroupList();
};


#endif /* SRC_DIOSKURIASERVER_H_ */
