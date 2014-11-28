#include "TCPStream.h"
#include "TCPConnector.h"
#include "Package.h"

#include <iostream>
#include <thread>
#include <cstring>

using namespace std;

bool programExit;

void inputListen();

int main(int argc, char** argv) {
	TCPConnector connector;
	TCPStream* stream;

	programExit = false;

	if(argc == 3) {
		thread inputListener(inputListen);

		stream = connector.connect(atoi(argv[2]), argv[1]);

		if(stream != NULL) {
			while(!programExit) {
				char buff[2048];
				memset(buff, 0, sizeof(buff));

				stream->receive(buff, sizeof(buff));
				cout << "Received message: " << string(buff, sizeof(buff)) << endl;
			}
		}

		delete stream;
	} else {
		cerr << "Usage: " << argv[0] << " [server address] [server port]" << endl;
	}

	return 0;
}

void inputListen() {
	string cmd;

	while(!programExit) {
		cin >> cmd;

		if(cmd == "exit") {
			programExit = true;
		} else {
			cerr << "unknown command: " << cmd << endl;
		}
	}
}