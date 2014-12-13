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

ProtocolUtils::ProtocolUtils() {
	// private constructor, not used
}

ProtocolUtils::~ProtocolUtils() {
	// ?
}

string& ProtocolUtils::ltrim(string& str) {
	str.erase(str.begin(), find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace))));
	str.erase(str.begin(), find_if(str.begin(), str.end(), not1('\0')));

	return str;
}

