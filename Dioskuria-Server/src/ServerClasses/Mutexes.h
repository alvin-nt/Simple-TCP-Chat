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


extern mutex logFileMutex;
extern mutex userFileMutex;
extern mutex messageFileMutex;
extern mutex groupFileMutex;
extern mutex thisGroupFileMutex;
extern mutex groupListMutex;



#endif /* SRC_SERVERCLASSES_MUTEXES_H_ */
