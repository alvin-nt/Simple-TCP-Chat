/*
 * ServerThread.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef SERVERTHREAD_H_
#define SERVERTHREAD_H_

#include "Thread/thread.h"

class ServerThread: public Thread {
public:
	ServerThread();
	virtual ~ServerThread();

	//variables for single thread are here
};

#endif /* SERVERTHREAD_H_ */
