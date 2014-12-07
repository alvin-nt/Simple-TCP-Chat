/*
 * User.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef SERVERCLASSES_USER_H_
#define SERVERCLASSES_USER_H_

#include "Utils.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include "../Constants.h"


using namespace std;

class User {
public:
	User();
	User(string _username, string _password);
	virtual ~User();
	string getUserName();
	string getPassword();
	string newUser(string _username, string _password);
	string login(string _username, string _password);
	string createUser();
	void loadMessages();
	vector<string> getMessageFrom(string user);
	void dumpMessageTo(string user, string message);
	void dumpMessageTo(string groupname, string user, string message);
	vector<string> getUniqueSenderList();

	static bool isUserExists(string user);


	vector<struct Message> unseenMessage;
private:
	string username;
	string password;

	// TODO: add other attributes

	bool queryUser();
	void clearMessageFile();
};

struct Message {
	string sender;
	time_t time;
	string message;
};

#endif /* SERVERCLASSES_USER_H_ */
