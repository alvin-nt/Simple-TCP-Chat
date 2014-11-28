#include "TCPStream.h"
#include "TCPAcceptor.h"
#include "Package.h"

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void listenInput();

static TCPAcceptor acceptor(10000, "localhost");

static vector<TCPStream*> clients;

bool programExit;

int main()
{
	int start = acceptor.start();
	programExit = false;

	thread inputListener(listenInput);

	if(start == 0) {
		cout << "Server listening on " 
			 << acceptor.getListeningAddress() << ":" << acceptor.getListeningPort() << endl;
		while(!programExit) {
			TCPStream* client = acceptor.accept();

			if(client != NULL) {
				clients.push_back(client);
			} else {
				cerr << "NULL client received!" << endl;
			}
		}
	} else {
		cerr << "Error code: " << start << endl;
	}

	for(TCPStream* client: clients) {
		delete client;
	}
	clients.clear();

	return 0;
}

void listenInput() {
	string cmd, message;

	while(!programExit) {
		cin >> cmd;

		if(cmd == "exit") {
			message = "serverExit";
			programExit = true;
		} else if(cmd == "echo") {
			cin >> message;
		} else {
			cerr << "unknown command: " << cmd << endl;
		}

		if(!message.empty()) {
			cout << "Sending message:" << message << endl;

			for(TCPStream* client: clients) {
				client->send(message.c_str(), message.length());
			}
		}

		message.clear();
	}
}