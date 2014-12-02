/*
 * ServerThread.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "ServerThread.h"

using namespace std;

ServerThread::ServerThread() {
	start();
}

ServerThread::ServerThread(TCPStream* passedsocket) {
	socket = passedsocket;
	start();
}

ServerThread::~ServerThread() {
	// TODO Auto-generated destructor stub
}

void* ServerThread::run() {
	//TODO inisialisasi network i/o stream
	string username,password;
	while (true) {
		//TODO main loop thread, process query by package

		//if parse signup
			/* Signup */
			/* Receive packet contains username password */
				/*
				cin >> username >> password;
				if (currentUser.newUser(username, password) == USER_SIGNUP_SUCCESS) {
					//send signup success
					threadName = username;
				} else {
					//signup fail
				}
				*/
		//else if parse login
			/* Login */
			/* Receive packet contains username password */
				/*
				//cin >> username >> password;
				if(currentUser.login(username, password) == USER_LOGIN_SUCCESS) {
					//send success login
					threadName = username;
					currentUser.loadMessages();
					cout << USER_LOGIN_SUCCESS << endl;
				} else {
					//send login failed
					cout << USER_LOGIN_INVALID << endl;
				}
				*/
		//else if parse message
			/* User sends message */
			/* TODO use message processor */
		//else if create group
			/* User create group */
			/* TODO GROUP */
		//else if join group
			/* User join group */
		//else if parse leave group
			/* User leave group */
		//else if parse request message
			/* User asks for messages */
			/* TODO parse packet to string requestFor */
				/*
				string requestFor;
				vector<string> messages;
				messages = currentUser.getMessageFrom(requestFor);
				//do some sending back to client
				 */

		//else if parse logout
			/* Logout */
			//break;

		cout << endl << "LOOP" << endl;
	}

	return NULL;
}
