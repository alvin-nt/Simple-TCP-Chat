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
	loadGroupList();

	groupListMutex.lock();
	for (unsigned int i = 0; i < groupList.size(); i++) {
		cout << "GROUP NAME: " << i << " " << groupList.at(i)->getGroupName() <<endl;
	}
	groupListMutex.unlock();
	/*
	TCPAcceptor* ss = new TCPAcceptor(PORT);
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
	st->join();
}

DioskuriaServer::~DioskuriaServer() {
}

void DioskuriaServer::loadGroupList() {
	groupListMutex.lock();
	groupFileMutex.lock();
	string groupFileName = "GroupList.txt";
	ifstream groupFile;
	groupFile.open(groupFileName.c_str(), ifstream::in);
	string process;
	while (getline(groupFile, process)) {
		Group *tem = new Group(process);
		groupList.push_back(tem);
	}
	groupListMutex.unlock();
	groupFileMutex.unlock();
}


