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

using namespace std;

class Group {
public:
	Group();
	Group(string name);
	virtual ~Group();
	string getGroupName();
	vector<User> getMembers();
	void joinGroup(User user);
	void createGroup(User user);
	void leaveGroup(User user);


private:
	string groupName;
	vector<User> members;
};

#endif /* SERVERCLASSES_GROUP_H_ */
