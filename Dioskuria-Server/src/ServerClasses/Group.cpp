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
	string fileName = "group-" + name;
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


