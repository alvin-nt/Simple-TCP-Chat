/*
 * User.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "../ServerClasses/User.h"

using namespace std;

User::User(string _username) {
	// TODO Auto-generated constructor stub

}

User::~User() {
	// TODO Auto-generated destructor stub
}

string User::getUserName() {
	return username;
}

string User::getPassword() {
	return password;
}

string User::queryUser() {
	//TODO some lookup to file on user pass list
}
