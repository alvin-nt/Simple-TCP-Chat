/*
 * globals.h
 *
 *  Created on: Dec 4, 2014
 *      Author: asseylum
 */

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#include <vector>

#include "ServerThread.h"
#include "ServerClasses/Group.h"

class Group;
class ServerThread;
extern std::vector<ServerThread*> threadPool;
extern std::vector<Group*> groupList;




#endif /* SRC_GLOBALS_H_ */
