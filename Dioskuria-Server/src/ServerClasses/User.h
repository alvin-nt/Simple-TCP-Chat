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
#include "../Constants.h"


using namespace std;

class User {
public:
	User();
	User(string _username, string _password);
	virtual ~User();
	string getUserName();
	string getPassword();
	bool queryUser();
	string newUser(string _username, string _password);
	string login(string _username, string _password);
	string createUser();
	void loadMessages();
	void clearMessageFile();
	vector<string> getMessageFrom(string user);


	vector<struct QueuedMessage> unseenMessage;
private:
	string username;
	string password;
	//TODO add other attributes


};

struct QueuedMessage {
	string sender;
	string message;
};

#endif /* SERVERCLASSES_USER_H_ */
