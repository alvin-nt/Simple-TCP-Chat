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
	}
	aGroupFile.close();
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
		Group *tem = new Group(name);
		groupListMutex.lock();
		groupList.push_back(tem);
		groupFileMutex.lock();
		string fileName = "GroupList.txt";
		ofstream groupFile;
		groupFile.open(fileName.c_str(),ofstream::app);
		groupFile << name << endl;
		groupFile.close();
		groupFileMutex.unlock();
		Utils::writeServerLog("Group "+name+" created");
		tem->joinGroup(user);
		groupListMutex.unlock();
		return true;
	}
}
bool Group::isGroupExists(string name) {
	groupListMutex.lock();
	bool found = false;
	for (unsigned int i = 0 ; i < groupList.size(); i++) {
		if (groupList.at(i)->getGroupName() == name) {
			found = true;
			break;
		}
	}
	groupListMutex.unlock();
	return found;
}


void Group::joinGroup(User user) {
	//thisGroupFileMutex.lock();
	string fileName = "group-" + groupName + ".txt";
	ofstream thisGroupFile;
	thisGroupFile.open(fileName.c_str(),ofstream::app);
	thisGroupFile << user.getUserName() << endl;
	thisGroupFile.close();
	//thisGroupFileMutex.unlock();
	Utils::writeServerLog(user.getUserName()+" joined "+groupName);
}

void Group::leaveGroup(User user) {
	//thisGroupFileMutex.lock();
	//groupListMutex.lock();
	for(unsigned i = 0; i < members.size(); i++) {
		if (members.at(i).getUserName() == user.getUserName()) {
			members.erase(members.begin()+i);
			break;
		}
	}

	string filename = "group-" + groupName + ".txt";
	string filename2 = "group-" + groupName + ".temp";
	ifstream input(filename);
	ofstream output(filename2);
	string process;
	while (getline(input, process)) {
		if (user.getUserName() != process) {
			output << process << endl;
		}
	}
	input.clear();
	input.seekg(0,ios::beg);
	input.close();
	output.close();
	remove(filename.c_str());
	rename(filename2.c_str(),filename.c_str());

	Utils::writeServerLog(user.getUserName()+" left "+groupName);

	//check for empty group
	if(members.size() == 0) {
		Utils::writeServerLog(groupName+" has zero member, deleting group");
		//groupFileMutex.lock();
		string filename = "GroupList.txt";
		string filename2 = "GroupList.temp";
		string filename3 = "group-" + groupName + ".txt";
		ifstream input(filename);
		ofstream output(filename2);
		string process;
		while (getline(input, process)) {
			if (groupName != process) {
				output << process << endl;
			}
		}
		input.clear();
		input.seekg(0,ios::beg);
		input.close();
		output.close();
		remove(filename.c_str());
		rename(filename2.c_str(),filename.c_str());
		remove(filename3.c_str());

		for(unsigned int i = 0; i < groupList.size(); i++) {
			if (groupList.at(i)->getGroupName() == groupName) {
				groupList.erase(groupList.begin()+i);
				break;
			}
		}

		//groupFileMutex.unlock();
	}

	//thisGroupFileMutex.unlock();
	//groupListMutex.unlock();

}

bool Group::checkMembership(User user) {
	//groupListMutex.lock();
	bool found = false;
	for(unsigned i = 0; i < members.size(); i++) {
		if (members.at(i).getUserName() == user.getUserName()) {
			found = true;
			break;
		}
	}
	//groupListMutex.unlock();
	return found;
}

void Group::broadcast(User broadcaster, string message) {
	Utils::writeServerLog(broadcaster.getUserName()+" messages "+groupName);
	for(unsigned int i = 0 ; i < members.size(); i++) {
		if(members.at(i).getUserName() != broadcaster.getUserName()) {
			if(isUserOnline(members.at(i))) {
	//			threadPoolMutex.lock();
				for(unsigned int j = 0; j < threadPool.size();j++) {
					if(threadPool.at(j)->threadName == members.at(i).getUserName()) {
						struct Message temp;
						temp.sender = groupName;
						temp.message = Utils::currentDateTime()+" "+broadcaster.getUserName()+" : "+message;
						threadPool.at(j)->acceptMessage(temp);
						break;
					}
				}
	//			threadPoolMutex.unlock();
			} else {
				string msg = broadcaster.getUserName()+" : "+message;
				broadcaster.dumpMessageTo(groupName,members.at(i).getUserName(),msg);
			}
		}
	}
}

Group* Group::getGroup(string name) {
	//groupListMutex.lock();
	for(unsigned int i = 0; i < groupList.size();i++) {
		if(groupList.at(i)->getGroupName() == name) {
			return groupList.at(i);
		}
	}
	return NULL;
	//groupListMutex.unlock();
}
