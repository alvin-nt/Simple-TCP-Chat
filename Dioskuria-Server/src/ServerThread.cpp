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
	string username,password;
	while (true) {
		cout << "Client connected" << endl;
		//TODO main loop thread, process query by package
		try {
			Package currentPackage(socket->receive());
			if(currentPackage.getPackageType() == Protocol::userSignup) {
				/* Signup */
				/* Receive packet contains username password */
				cin >> username >> password;
				if(Group::isGroupExists(username)) {
					//TODO signup fail, add signup fail message?
					Package reply(Protocol::userSignupFail);
					reply.send(*socket);
					cout << "IT IS GROUP NAME" << endl;
				} else {
					if (currentUser.newUser(username, password) == USER_SIGNUP_SUCCESS) {
						threadName = username;
						Package reply(Protocol::userSignupSuccess);
						reply.send(*socket);
					} else {
						//TODO signup fail, add signup fail message?
						Package reply(Protocol::userSignupFail);
						reply.send(*socket);
					}
				}
			} else if (currentPackage.getPackageType() == Protocol::userLogin) {
				/* Login */
				/* Receive packet contains username password */
				username = "dafuq";
				password = "string";
				if(currentUser.login(username, password) == USER_LOGIN_SUCCESS) {
					Package reply(Protocol::userLoginSuccess);
					reply.send(*socket);
					threadName = username;
					currentUser.loadMessages();
					checkNotification();
					cout << USER_LOGIN_SUCCESS << endl;
				} else {
					//send login failed
					Package reply(Protocol::userLoginFail);
					reply.send(*socket);
					cout << USER_LOGIN_INVALID << endl;
				}
			} else if (currentPackage.getPackageType() == Protocol::messageRecv) {
				/* User sends message */
				/* if user is present (threadlist) then send to its queue,
				 * else call the currentUser.dumpMessageTo(targetUser)
				 */
				string name;
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
									ms.sender = currentUser.getUserName();
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
			} else if (currentPackage.getPackageType() == Protocol::groupCreate) {
				/* User create group */
				//Proto
				/*
				 Group::createGroup(currentUser, "name");
				 */
			} else if (currentPackage.getPackageType() == Protocol::groupJoin) {
				/* User join group */
				//Proto
				/*
				 Group::isGroupExists(name);
				 getgroupnum;
				 group.joinGroup(currentUser);
				 */
			} else if (currentPackage.getPackageType() == Protocol::groupLeave) {
				/* User leave group */
				//Proto
				/*
				grouplookup;
				if(group.checkMembership(currentUser)) {
					group.leaveGroup(currentUser);
				}
				 */
			}
		//else if parse request message
			/* User asks for messages */
			/* TODO parse packet to string requestFor */
				/*
				string requestFor;
				vector<string> messages;
				messages = currentUser.getMessageFrom(requestFor);
				//do some sending back to client
				 */
			else if (currentPackage.getPackageType() == Protocol::userLogout) {
				/* Logout */
				Utils::writeServerLog(username + " logged out");
				break;
			}
		} catch (SocketException& e) {
			break;
		}
	}

	//cleanup codes
	threadPoolMutex.lock();
	for(unsigned int i = 0; i < threadPool.size();i++) {
		if (threadPool.at(i) == this) {
			threadPool.erase(threadPool.begin()+i);
			break;
		}
	}
	threadPoolMutex.unlock();

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
