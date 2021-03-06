/*
 * IO.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "../ServerClasses/Utils.h"

using namespace std;

const string Utils::currentDateTime() {
	    time_t     now = time(0);
	    struct tm  tstruct;
	    char       buf[80];
	    tstruct = *localtime(&now);
	    strftime(buf, sizeof(buf), "[%Y-%m-%d %X]", &tstruct);

	    return buf;
}

const string Utils::dateTime(const time_t time) {
	char buf[80];
	strftime(buf, sizeof(buf), "[%Y-%m-%d %X]", localtime(&time));

	return buf;
}

void Utils::writeServerLog(string message) {
	logFileMutex.lock();
	cout << Utils::currentDateTime() << " " << message << endl;

	ofstream outfile;
	outfile.open("log.txt", ios::app);
	outfile << Utils::currentDateTime() << " " << message << endl;
	outfile.close();
	logFileMutex.unlock();
}
