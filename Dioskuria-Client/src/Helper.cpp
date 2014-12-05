/*
 * Helper.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: asseylum
 */

#include "Helper.h"

Helper::Helper() {
	// TODO Auto-generated constructor stub

}

Helper::~Helper() {
	// TODO Auto-generated destructor stub
}

vector<string> Helper::fetchFromFile(string usernameMessage) {
	string filename = usernameMessage + "-messages.txt";
	ifstream file;
	file.open(filename.c_str(), ifstream::in);
	string process;
	vector<string> ret;
	while(getline(file,process)) {
		ret.push_back(process);
	}
	return ret;
}

