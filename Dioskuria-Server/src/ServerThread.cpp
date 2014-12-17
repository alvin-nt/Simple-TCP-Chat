/*
 * ServerThread.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "ServerThread.h"

#include "Protocol/SimpleMessagePackage.h"
#include "Protocol/GroupCreatePackage.h"
#include "Protocol/GroupJoinPackage.h"
#include "Protocol/UserInitPackage.h"
#include "Protocol/UserIdPackage.h"
#include "Protocol/MessageSendPackage.h"
#include "Protocol/MessageRecvPackage.h"

#include <cstring>

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
	while (true) {
		//TODO main loop thread, process query by package
		try {
			char buff[512];
			memset(buff, 0, sizeof(buff));

			socket->receive(buff, sizeof(buff), MSG_PEEK);

			Package currentPackage = buff;

			/*char timeBuff[100];
			memset(timeBuff, 0, sizeof(timeBuff));
			time_t packageTime = currentPackage.getPackageTime();

			strftime(timeBuff, sizeof(timeBuff), "%T", gmtime(&packageTime));

			cout << "--- Received package stats --- " << endl
				 << "packageNum: " << currentPackage.getPackageType() << endl
				 << "packageTime: " << timeBuff << endl
				 << "--- End of package stats --- " << endl;*/
			if(currentPackage.getPackageType() == Protocol::userSignup) {
				/* Signup */
				/* Receive packet contains username password */
				// flush first
				memset(buff, 0, sizeof(buff));
				socket->receive(buff, sizeof(buff));

				UserInitPackage package = buff;

				string username = package.getUserName();
				string password = package.getUserPassword();

				if(Group::isGroupExists(username)) {
					//TODO signup fail, add signup fail message?
					SimpleMessagePackage reply(Protocol::userSignupFail);

					reply.setMessage("IT IS GROUP NAME");
					reply.send(*socket);
				} else {
					if (currentUser.newUser(username, password) == USER_SIGNUP_SUCCESS) {
						threadName = username;
						Package reply(Protocol::userSignupSuccess);

						// TODO: generate user id here
						reply.send(*socket);
					} else {
						//TODO signup fail, add signup fail message?
						SimpleMessagePackage reply(Protocol::userSignupFail);

						reply.send(*socket);
					}
				}
			} else if (currentPackage.getPackageType() == Protocol::userLogin) {
				cout << "logging in..." << endl;
				/* Login */
				/* Receive packet contains username password */
				memset(buff, 0, sizeof(buff));
				socket->receive(buff, sizeof(buff));

				UserInitPackage package = buff;

				string username = package.getUserName();
				string password = package.getUserPassword();

				if(currentUser.login(username, password) == USER_LOGIN_SUCCESS) {
					Package reply(Protocol::userLoginSuccess);
					reply.send(*socket);

					threadName = username;
					currentUser.loadMessages();
					checkNotification();
					Utils::writeServerLog(username + " has logged in");
				} else {
					//send login failed
					SimpleMessagePackage reply(Protocol::userLoginFail);

					reply.setMessage("Login failed");
					reply.send(*socket);

					cout << USER_LOGIN_INVALID << endl;
				}
			} else if (currentPackage.getPackageType() == Protocol::messageSend) {
				/* User sends message */
				/* if user is present (threadlist) then send to its queue,
				 * else call the currentUser.dumpMessageTo(targetUser)
				 */
				memset(buff, 0, sizeof(buff));
				socket->receive(buff, sizeof(buff));

				MessageSendPackage package = buff;

				string name = package.getReceiver();
				time_t msgTime = package.getPackageTime();
				string message = package.getMessage();
				string msg = currentUser.getUserName() + " : " + message;
				cout << msg << endl;
				bool isGroupName = Group::isGroupExists(name);
				if (isGroupName) {
					Group* temp = Group::getGroup(name);
					if(temp != NULL) {
						temp->broadcast(currentUser,msg);
						SimpleMessagePackage reply(Protocol::messageSendSuccess);
						reply.send(*socket);
					}
				} else { //to user
					if(User::isUserExists(name)) {
						Utils::writeServerLog(currentUser.getUserName() + " messages " + name);

						if(isUserOnline(name)) {
							threadPoolMutex.lock();
							for(unsigned int i = 0; i < threadPool.size(); i++) {
								if (threadPool.at(i)->threadName == name) {
									struct Message ms;
									ms.sender = currentUser.getUserName();
									ms.time = msgTime;
									ms.message = msg;
									threadPool[i]->acceptMessage(ms);
									SimpleMessagePackage reply(Protocol::messageSendSuccess);
									reply.send(*socket);
									break;
								}
							}
							threadPoolMutex.unlock();
						} else {
							currentUser.dumpMessageTo(name, msgTime, msg);
							SimpleMessagePackage reply(Protocol::messageSendSuccess);
							reply.send(*socket);
						}
					} else {
						//send it does not exist
						SimpleMessagePackage reply(Protocol::messageSendFailed);
						reply.setMessage("User " + name + " does not exist!");

						reply.send(*socket);
					}
				}
			} else if (currentPackage.getPackageType() == Protocol::groupCreate) {
				/* User create group */
				// flush
				socket->receive(buff, sizeof(buff));

				GroupCreatePackage package = buff;
				if(Group::createGroup(currentUser, package.getGroupName())) {
					UserIdPackage reply(Protocol::groupCreateSuccess, 0);
					// TODO: generate the group id here
					reply.send(*socket);
				} else {
					UserIdPackage reply(Protocol::groupCreateFail, 0);

					reply.send(*socket);
				}
			} else if (currentPackage.getPackageType() == Protocol::groupJoin) {
				/* User join group */
				// flush
				cout << "Masuk?" << endl;
				socket->receive(buff, sizeof(buff));
				//socket->receive(buff, sizeof(buff));

				GroupJoinPackage package = buff;

				string groupName = package.getGroupName();
				if(Group::isGroupExists(groupName)) {
					cout << "Group " << groupName << " exists!" << endl;

					Group* group = Group::getGroup(groupName);
					if(group->checkMembership(currentUser)) {
						cout << "already in group!" << endl;
						SimpleMessagePackage response(Protocol::groupJoinFail);

						response.setMessage("Already joined in group " + groupName);
						response.send(*socket);
					} else {
						cout << "Join success!" << endl;
						group->joinGroup(currentUser);

						Package response(Protocol::groupJoinSuccess);

						socket->send(response);
					}
				} else {
					cout << "Group " << groupName << " does not exist!" << endl;
					SimpleMessagePackage response(Protocol::groupJoinFail);

					response.setMessage("Group " + groupName + " does not exist");
					response.send(*socket);
				}
			} else if (currentPackage.getPackageType() == Protocol::groupLeave) {
				/* User join group */
				// flush
				socket->receive(buff, sizeof(buff));

				// abusing this package class
				SimpleMessagePackage package = buff;

				if(Group::isGroupExists(package.getMessage())) {
					Group* group = Group::getGroup(package.getMessage());
					if(group->checkMembership(currentUser)) {
						group->leaveGroup(currentUser);
						Package response(Protocol::groupLeaveSuccess);

						response.send(*socket);
					} else {
						SimpleMessagePackage response(Protocol::groupLeaveFail);

						response.setMessage("You are not a member of " + group->getGroupName());
						response.send(*socket);
					}
				} else {
					SimpleMessagePackage response(Protocol::groupLeaveFail);

					response.setMessage("Group " + package.getMessage() + " does not exist");
					response.send(*socket);
				}
			} else if(currentPackage.getPackageType() == Protocol::messageRecvRequest) {
				// flush
				socket->receive(buff, sizeof(buff));
				SimpleMessagePackage requestPackage(buff);

				if(!currentUser.unseenMessage.empty()) {
					while(!currentUser.unseenMessage.empty()) {
						struct Message ms;
						ms = currentUser.unseenMessage[0];

						if(requestPackage.getMessage() == ms.sender) {

							MessageSendPackage response(ms.sender, ms.message);
							response.resetTime();
							response.send(*socket);

							currentUser.unseenMessage.erase(currentUser.unseenMessage.begin());
						}
					}
					Package last(Protocol::messageRecvEnd);

					last.send(*socket);
				} else {
					// no new messages
					Package last(Protocol::messageRecvEnd);

					last.send(*socket);
				}

			} else if (currentPackage.getPackageType() == Protocol::userLogout) {
				/* Logout */
				Utils::writeServerLog(threadName + " logged out");
				break;
			} else {
				//flush
				socket->receive(buff, sizeof(buff));
			}
		} catch (SocketException& e) {
			cerr << "Caught SocketException: " << e.what() << endl;
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
		vector<struct Message>& msgList = currentUser.unseenMessage;
		while(!msgList.empty()) {
			struct Message ms = msgList[0];

			MessageRecvPackage package(ms.sender, ms.time, ms.sender);
			package.send(*socket);

			msgList.erase(msgList.begin());
		}

		vector<string> userlist = currentUser.getUniqueSenderList();
		cout << NEW_NOTIFICATION;
		for (unsigned int i = 0; i < userlist.size();i++) {
			cout << userlist.at(i) << " ";
		}
		cout << endl;
	} else {
		// no need to send anything
	}
}

void ServerThread::acceptMessage(struct Message what) {
	currentUser.unseenMessage.push_back(what);
}
