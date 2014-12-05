/*
 * Helper.h
 *
 *  Created on: Dec 5, 2014
 *      Author: asseylum
 */

#ifndef SRC_HELPER_H_
#define SRC_HELPER_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Helper {
public:
	Helper();
	virtual ~Helper();
	vector<string> fetchFromFile(string usernameMessage);
};

#endif /* SRC_HELPER_H_ */
