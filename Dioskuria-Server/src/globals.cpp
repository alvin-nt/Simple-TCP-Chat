/*
 * globals.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: asseylum
 */

#include "ServerThread.h"
#include "ServerClasses/Group.h"
#include "ServerClasses/User.h"
#include <string>

using namespace std;

class Group;
class ServerThread;

std::vector<ServerThread*> threadPool;
std::vector<Group*> groupList;

bool isUserOnline(User user);
bool isUserOnline(string user);

bool isUserOnline(User user) {
	threadPoolMutex.lock();
	bool online = false;
	for(unsigned int i = 0; i < threadPool.size(); i++){
		if(user.getUserName() == threadPool.at(i)->threadName) {
			online = true;
			break;
		}
	}
	threadPoolMutex.unlock();
	return online;
}
bool isUserOnline(string user) {
	threadPoolMutex.lock();
	bool online = false;
	for(unsigned int i = 0; i < threadPool.size(); i++){
		if(user == threadPool.at(i)->threadName) {
			online = true;
			break;
		}
	}
	threadPoolMutex.unlock();
	return online;
}
