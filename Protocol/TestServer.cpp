#include <iostream>
#include <vector>
#include <future>
#include <chrono>
#include <thread>
#include <cstring>

#include "TCPStream.h"
#include "TCPAcceptor.h"
#include "Package.h"
#include "SocketException.h"
#include "ClientThreadExample.h"

using namespace std;

void listenInput();

static TCPAcceptor acceptor(10000, "localhost");

static vector<ClientThreadExample> clients;

bool programExit;

int main()
{
	int start = acceptor.start();
	programExit = false;

	thread inputListener(listenInput);

	promise<bool> p;
	// get the future object
	auto future = p.get_future();

	if(start == 0) {
		cout << "Server listening on " 
			 << acceptor.getListeningAddress() << ":" << acceptor.getListeningPort() << endl;
		while(!programExit) {
			TCPStream* client = acceptor.accept();

			if(client != NULL) {
				ClientThreadExample clientThread(client);
				clientThread.start();

				clients.push_back(std::move(clientThread));
			} else {
				cerr << "NULL client received!" << endl;
			}
		}
	} else {
		cerr << "Error code: " << start << endl;
	}

	clients.clear();

	// check the inputListener thread
	// get the thread status after 0.1s
	auto status = future.wait_for(chrono::milliseconds(100));

	if(status == std::future_status::ready) {
		// thread is complete
	} else {
		// thread is still running
		cout << "Press [Enter] to exit..";
	}
	
	inputListener.join();

	return 0;
}

void listenInput() {
	string cmd, message;
	char buff[512];

	while(!programExit) {
		memset(buff, 0, sizeof(buff));
		cin >> cmd;

		if(cmd == "exit") {
			if(!programExit) {
				message = "serverExit";
				programExit = true;
			}
		} else if(cmd == "echo") {
			if(!programExit) {
				cin >> message;
				copy(message.begin(), message.end(), buff);
			}
		} else {
			if(!programExit)
				cerr << "unknown command: " << cmd << endl;
		}

		if(!message.empty()) {
			cout << "Sending message: " << message << endl;

			for(auto it = clients.begin(); it != clients.end(); it++) {
				int sentBytes = 0;
				try {
					sentBytes = it->send(buff, sizeof(buff));
					
					cout << "Sent " << sentBytes << " bytes to " << it->getPort() << endl;
				} catch (SocketException& e) {
					cerr << "Caught SocketException from port " << it->getPort() << ": " << e.what() << endl;
				}
			}
		}

		message.clear();
	}
}