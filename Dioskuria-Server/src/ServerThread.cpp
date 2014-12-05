/*
 * ServerThread.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "ServerThread.h"

using namespace std;

ServerThread::ServerThread() {
	socket = NULL;
	start();
}

ServerThread::ServerThread(TCPStream* passedsocket) {
	socket = passedsocket;
	start();
}

ServerThread::~ServerThread() {
}

void* ServerThread::run() {
	//TODO inisialisasi network i/o stream
	string username,password;
	while (true) {
		cout << "Client connected" << endl;
		//TODO main loop thread, process query by package
		//if parse signup
			/* Signup */
			/* Receive packet contains username password */
				/*
				cin >> username >> password;
				if(Group::isGroupExists(username)) {
					//signup fail
					cout << "IT IS GROUP NAME" << endl;
				} else {
					if (currentUser.newUser(username, password) == USER_SIGNUP_SUCCESS) {
						//send signup success
						threadName = username;
					} else {
						//signup fail
					}
				}
				*/
		//else if parse login
			/* Login */
			/* Receive packet contains username password */
		/*
				username = "dafuq";
				password = "string";
				//cin >> username >> password;
				if(currentUser.login(username, password) == USER_LOGIN_SUCCESS) {
					//send success login
					threadName = username;
					currentUser.loadMessages();
					checkNotification();
					cout << USER_LOGIN_SUCCESS << endl;

					break;
				} else {
					//send login failed
					cout << USER_LOGIN_INVALID << endl;
				}
*/
		//else if parse message
			/* User sends message */
			/* TODO use message processor */
				/* if user is present (threadlist) then send to its queue, TODO create method in serverthread
				 * to handle message passing to user messagequeue
				 * else call the currentUser.dumpMessageTo(targetUser)
				 */
				/*string name;
				string msg;
				//msg = currentUser.getUserName() + " : " + message;
				bool isGroupName = Group::isGroupExists(name);
				if (isGroupName) {
					Group* temp;
					temp = Group::getGroup("red-dot");
					if(temp != NULL) {
						temp->broadcast(currentUser,msg);
					}
				} else { //to user
					if(User::isUserExists(name)) {
						Utils::writeServerLog(currentUser.getUserName()+" messages "+name);
						if(isUserOnline(name)) {
							threadPoolMutex.lock();
							for(unsigned int i = 0; i < threadPool.size(); i++) {
								if (threadPool.at(i)->threadName == name) {
									struct Message ms;
									ms.sender = currentUser.getUserName;
									ms.message = msg;
									threadPool.at(i)->acceptMessage(ms);
									break;
								}
							}
							threadPoolMutex.unlock();
						} else {
							currentUser.dumpMessageTo(name, msg);
						}
					} else {
						//send it does not exist
					}
				}
				*/
		//else if create group
			/* User create group */
			/* TODO GROUP */
				//Proto
				/*
				 Group::createGroup(currentUser, "name");
				 */

		//else if join group
			/* User join group */
				//Proto
				/*
				 Group::isGroupExists(name);
				 getgroupnum;
				 group.joinGroup(currentUser);
				 */

		//else if parse leave group
			/* User leave group */
				//Proto
				/*
				grouplookup;
				if(group.checkMembership(currentUser)) {
					group.leaveGroup(currentUser);
				}
				 */

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
			//Utils::writeServerLog(username + " logged out");
			//break;
		break;
		cout << endl << "LOOP" << endl;
	}

	return NULL;
}

void ServerThread::checkNotification(){
	if(!currentUser.unseenMessage.empty()) {
		//notify user on new messages from who who who, TODO send via network
		vector<string> userlist = currentUser.getUniqueSenderList();
		cout << NEW_NOTIFICATION;
		for (unsigned int i = 0; i < userlist.size();i++) {
			cout << userlist.at(i) << " ";
		}
		cout << endl;
	}
}

void ServerThread::acceptMessage(struct Message what) {
	currentUser.unseenMessage.push_back(what);
}
