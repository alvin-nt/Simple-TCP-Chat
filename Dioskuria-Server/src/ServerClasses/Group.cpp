/*
 * Group.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "../ServerClasses/Group.h"

using namespace std;

Group::Group() {

}

Group::Group(string name){
	groupName = name;
	string fileName = "group-" + name + ".txt";
	ifstream aGroupFile;
	aGroupFile.open(fileName.c_str(), ifstream::in);
	string process;
	while(getline(aGroupFile,process)) {
		User *tem = new User(process,"GROUP");
		members.push_back(*tem);
		cout << "Member name: " << process << endl;
	}
}

Group::~Group() {
}

string Group::getGroupName() {
	return groupName;
}
vector<User> Group::getMembers(){
	return members;
}

bool Group::createGroup(User user, string name) {
	if (isGroupExists(name)) {
		Utils::writeServerLog("Group "+name+" already exists!");
		return false;
	} else {
		Group tem(name);
		groupListMutex.lock();
		groupList.push_back(tem);
		groupFileMutex.lock();
		string fileName = "GroupList.txt";
		ofstream groupFile;
		groupFile.open(fileName.c_str(),ofstream::app);
		groupFile << name << endl;
		groupFileMutex.unlock();
		Utils::writeServerLog("Group "+name+" created");
		tem.joinGroup(user);
		groupListMutex.unlock();
		return true;
	}
}
bool Group::isGroupExists(string name) {
	groupListMutex.lock();
	bool found = false;
	cout << groupList.size() << endl;
	for (unsigned int i = 0;i < groupList.size();i++) {
		if (groupList.at(i).getGroupName() == name) {
			found = true;
			break;
		}
	}
	groupListMutex.unlock();
	return found;
}


void Group::joinGroup(User user) {
	thisGroupFileMutex.lock();
	string fileName = "group-" + groupName + ".txt";
	ofstream thisGroupFile;
	thisGroupFile.open(fileName.c_str(),ofstream::app);
	thisGroupFile << user.getUserName() << endl;
	thisGroupFileMutex.unlock();
	Utils::writeServerLog(user.getUserName()+" joined "+groupName);
}

