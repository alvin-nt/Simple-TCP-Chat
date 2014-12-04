/*
 * Mutexes.h
 *
 *  Created on: Dec 3, 2014
 *      Author: asseylum
 */

#ifndef SRC_SERVERCLASSES_MUTEXES_H_
#define SRC_SERVERCLASSES_MUTEXES_H_

#include <mutex>

using namespace std;


static mutex logFileMutex;
static mutex userFileMutex;
static mutex messageFileMutex;



#endif /* SRC_SERVERCLASSES_MUTEXES_H_ */
