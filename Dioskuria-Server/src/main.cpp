/*
 * main.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "DioskuriaServer.h"

using namespace std;

int main() {
	int PORT=18213;
	DioskuriaServer* server = new DioskuriaServer(PORT);
	delete server;

	return 0;
}


