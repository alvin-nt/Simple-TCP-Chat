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
#include "ServerClasses/Group.h"
#include <vector>

using namespace std;

class DioskuriaServer {
public:
	DioskuriaServer(int PORT, string host);
	virtual ~DioskuriaServer();
};

static vector<ServerThread*> ThreadPool;
static vector<Group> GroupList;


#endif /* SRC_DIOSKURIASERVER_H_ */
