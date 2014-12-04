/*
 * Group.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef SERVERCLASSES_GROUP_H_
#define SERVERCLASSES_GROUP_H_

#include <vector>
#include <iostream>
#include <fstream>
#include "User.h"
#include "Mutexes.h"
#include "../globals.h"

using namespace std;

class Group {
public:
	Group();
	Group(string name);
	virtual ~Group();
	string getGroupName();
	vector<User> getMembers();
	static bool createGroup(User user, string name);
	static bool isGroupExists(string name);
	void joinGroup(User user);
	void leaveGroup(User user);
	void broadcast(User broadcaster,string message);

private:
	string groupName;
	vector<User> members;


};

#endif /* SERVERCLASSES_GROUP_H_ */
