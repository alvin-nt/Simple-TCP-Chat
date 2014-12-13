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

string& ProtocolUtils::rtrim(string& str) {
	str.erase(find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace))).base(), str.end());
	str.erase(find_if(str.rbegin(), str.rend(), not1('\0')).base(), str.end());

	return str;
}

string& ProtocolUtils::trim(string& str) {
	return ltrim(rtrim(str));
}
