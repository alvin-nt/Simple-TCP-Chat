/*
 * ProtocolUtils.h
 *
 *  Created on: Dec 13, 2014
 *      Author: alvin-nt
 */

#ifndef SRC_PROTOCOL_PROTOCOLUTILS_H_
#define SRC_PROTOCOL_PROTOCOLUTILS_H_

#include <string>

using namespace std;

class ProtocolUtils {
public:
	static string& ltrim(string& str);
	static string& rtrim(string& str);
	static string& trim(string& str);
private:
	ProtocolUtils();
public:
	virtual ~ProtocolUtils();
};

#endif /* SRC_PROTOCOL_PROTOCOLUTILS_H_ */
