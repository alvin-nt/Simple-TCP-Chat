/*
 * IO.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef SERVERCLASSES_UTILS_H_
#define SERVERCLASSES_UTILS_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include "Mutexes.h"

using namespace std;

class Utils {
public:
	static const string currentDateTime();
	static const string dateTime(const time_t msgTime);
	static void writeServerLog(string message);


};

#endif /* SERVERCLASSES_IO_H_ */
