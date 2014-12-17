/*
 * ProtocolUtils.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: alvin-nt
 */

#include "ProtocolUtils.h"

#include <algorithm>
#include <functional>
#include <locale>
#include <cctype>
#include <sstream>

using namespace std;

ProtocolUtils::ProtocolUtils() {
	// private constructor, not used
}

ProtocolUtils::~ProtocolUtils() {
	// ?
}

string& ProtocolUtils::ltrim(string& str) {
	str.erase(str.begin(), find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace))));

	return str;
}

string& ProtocolUtils::rtrim(string& str) {
	str.erase(find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace))).base(), str.end());

	return str;
}

string& ProtocolUtils::trim(string& str) {
	//str = ltrim(rtrim(str));

	stringstream ss;
	for(auto i = 0; i < str.length(); i++) {
		if(str[i] != '\0')
			ss << str[i];
	}

	str = ss.str();

	return str;
}
