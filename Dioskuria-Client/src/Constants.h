/*
 * Constants.h
 *
 *  Created on: Dec 5, 2014
 *      Author: asseylum
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

#include <string>

using namespace std;

static const string NEW_MESSAGE = "----- New Message(s) -----";
static const string SIGNUP_SUCCESS = "Signup success!";
static const string SIGNUP_FAILED = "Signup failed! username already exists or it is a group name!";
static const string LOGIN_SUCCESS = "Login success!";
static const string LOGIN_FAILED = "Invalid username or password";
static const string MESSAGE_SENT = "Message sent.";
static const string MESSAGE_SENT_ERR_NXUSER = " doesn't exist!";
static const string GROUP_ERR_EXIST = " already exists!";
static const string GROUP_ERR_NXGROUP = " doesn’t exist.";
static const string GROUP_JOIN = "Joining group ";
static const string GROUP_CREATE = " group created";
static const string NOTIFICATION = "New message(s) from ";



#endif /* SRC_CONSTANTS_H_ */
