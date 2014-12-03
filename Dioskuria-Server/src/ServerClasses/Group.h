/*
 * Group.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef SERVERCLASSES_GROUP_H_
#define SERVERCLASSES_GROUP_H_

#include <vector>
#include "User.h"

using namespace std;

class Group {
public:
	Group();
	virtual ~Group();

private:
	vector<User> Members;
};

#endif /* SERVERCLASSES_GROUP_H_ */
