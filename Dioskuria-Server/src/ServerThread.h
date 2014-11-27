/*
 * ServerThread.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef SERVERTHREAD_H_
#define SERVERTHREAD_H_

#include "Thread/thread.h"
#include "Protocol/TCPStream.h"
#include "ServerClasses/User.h"
#include "ServerClasses/Group.h"
#include <string>
#include "ServerClasses/Utils.h"

using namespace std;

class ServerThread: public Thread {
public:
	ServerThread(TCPStream* passedsocket);
	virtual ~ServerThread();
	void *run();
	//variables for single thread are here
	string ThreadName;
private:
	TCPStream* socket;

};

#endif /* SERVERTHREAD_H_ */
