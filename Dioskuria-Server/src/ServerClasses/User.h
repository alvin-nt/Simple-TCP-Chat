/*
 * User.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef SERVERCLASSES_USER_H_
#define SERVERCLASSES_USER_H_

#include "Utils.h"

using namespace std;

class User {
public:
	User(string _username);
	virtual ~User();
	string getUserName();
	string getPassword();
	string queryUser();

private:
	string username;
	string password;
	//TODO add other attributes
};

#endif /* SERVERCLASSES_USER_H_ */
