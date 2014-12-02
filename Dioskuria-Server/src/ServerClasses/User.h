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

private:
	string username;
	string password;
	vector<string> unsentMessages;
	//TODO add other attributes
};

#endif /* SERVERCLASSES_USER_H_ */
