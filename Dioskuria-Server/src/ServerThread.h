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
#include "Protocol/Package.h"
#include "Protocol/Protocol.h"
#include "Protocol/SocketException.h"
#include "ServerClasses/User.h"
#include "ServerClasses/Group.h"
#include "ServerClasses/Utils.h"
#include "ServerClasses/MessageProcessor.h"
#include "ServerClasses/Mutexes.h"
#include "Constants.h"
#include "globals.h"
#include <string>
#include <iostream>
#include <mutex>

using namespace std;

class ServerThread: public Thread {
public:
	ServerThread();
	ServerThread(TCPStream* passedsocket);
	virtual ~ServerThread();
	void *run();
	void checkNotification();

	void acceptMessage(struct Message what);

	//variables for single thread are here
	string threadName;
private:
	TCPStream* socket;
	User currentUser;
};

#endif /* SERVERTHREAD_H_ */
