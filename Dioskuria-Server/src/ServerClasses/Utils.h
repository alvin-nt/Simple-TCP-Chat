/*
 * IO.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef SERVERCLASSES_IO_H_
#define SERVERCLASSES_IO_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <fstream>

using namespace std;

class Utils {
public:
	static const string currentDateTime();
	static void writeServerLog(string message);

private:
	static const string logFileName;
};

#endif /* SERVERCLASSES_IO_H_ */
