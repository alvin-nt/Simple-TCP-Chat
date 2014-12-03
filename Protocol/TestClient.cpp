#include "TCPStream.h"
#include "TCPConnector.h"
#include "Package.h"

#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <cstring>

#include "SocketException.h"

using namespace std;

bool programExit;

void inputListen();

int main(int argc, char** argv) {
	TCPConnector connector;
	TCPStream* stream;

	programExit = false;

	if(argc == 3) {
		thread inputListener(inputListen);
		promise<bool> p;

		// get the future object
		auto future = p.get_future();

		stream = connector.connect(atoi(argv[2]), argv[1]);

		if(stream != NULL) {
			while(!programExit) {
				char buff[512];
				try {
					memset(buff, 0, sizeof(buff));

					stream->receive(buff, sizeof(buff));
					cout << "Received message: " << string(buff, sizeof(buff)) << endl;
				} catch (SocketException& e) {
					cerr << "Caught SocketException: " << e.what() << endl;
					programExit = true;
				}
			}
		}

		// close the connection
		delete stream;

		// get the thread status after 0.1s
		auto status = future.wait_for(chrono::milliseconds(100));

		if(status == std::future_status::ready) {
			// thread is complete
		} else {
			// thread is still running
			cout << "Press [Enter] to exit..";
		}
		
		inputListener.join();
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
		} else if(cmd.empty()) {
			// empty command; close silently
		} else {
			cerr << "unknown command: " << cmd << endl;
		}
	}
}