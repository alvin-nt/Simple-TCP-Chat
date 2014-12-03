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

void Utils::writeServerLog(string message) {
	cout << Utils::currentDateTime() << " " << message << endl;

	ofstream outfile;
	outfile.open("log.txt", ios::app);
	outfile << Utils::currentDateTime() << " " << message << endl;
	outfile.close();
}
