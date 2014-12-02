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

		//if bla bla
			/* Signup */
			/* Receive packet contains username password */
				/*
				cin >> username >> password;
				if (currentUser.newUser(username, password) == USER_SIGNUP_SUCCESS) {
					//send signup success
					threadName = username;
				} else {
					//signup fail
				}*/
		//else if
			/* Login */
			/* Receive packet contains username password */
				cin >> username >> password;
				if(currentUser.login(username, password) == USER_LOGIN_SUCCESS) {
					//send success login
					threadName = username;
					cout << USER_LOGIN_SUCCESS << endl;
				} else {
					//send login failed
					cout << USER_LOGIN_INVALID << endl;
				}
		cout << endl << "LOOP" << endl;
	}

	return NULL;
}
