/*
 * main.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: asseylum
 */

#include "Helper.h"
#include "Constants.h"
#include "Protocol/TCPStream.h"
#include "Protocol/TCPConnector.h"
#include "Protocol/Protocol.h"
#include "Protocol/Package.h"
#include <iostream>
#include <string>

using namespace std;

bool isSignedIn;

int main(void) {
	isSignedIn = false;
	string input,dummy;
	Helper helper;
	TCPConnector* connector = new TCPConnector();
	TCPStream* stream = connector->connect(18213,"localhost");
	while(1){
		cout << "> "; getline(cin, input);
		if(input == "signup" && !isSignedIn) {
			string username, password;
			cout << "Name		: "; cin >> username;
			cout << "Password	: "; cin >> password;
			//proses signup begins here
			//TODO add real data to package
			Package toSend(Protocol::userSignup);
			toSend.send(*stream);
			Package response(stream->receive());
			if (response.getPackageType() == Protocol::userSignupSuccess) {
				isSignedIn = true;
				cout << SIGNUP_SUCCESS << endl;
			} else if (response.getPackageType() == Protocol::userSignupFail) {
				cout << SIGNUP_FAILED << endl;
			}
		} else if (input == "login" && !isSignedIn) {
			string username, password;
			cout << "Name		: "; cin >> username;
			cout << "Password	: "; cin >> password;
			cout << username << " " << password << endl;
			//process login begins here
			//TODO add real data to package, refer to ServerThread.cpp for server dummy implementation
			Package toSend(Protocol::userLogin);
			toSend.send(*stream);
			Package response(stream->receive());
			if (response.getPackageType() == Protocol::userLoginSuccess) {
				isSignedIn = true;
				cout << LOGIN_SUCCESS << endl;
			} else if (response.getPackageType() == Protocol::userLoginFail) {
				cout << LOGIN_FAILED << endl;
			}
		} else if (input.substr(0,7) == "message" && isSignedIn) {
			string recipient, message;
			recipient = input.substr(8);
			cout << "Message : " << endl;
			getline(cin, message);

			cout << recipient << " " << message << endl;
			//process message here
		} else if (input.substr(0,6) == "create" && isSignedIn) {
			string groupName;
			groupName = input.substr(7);

			cout << groupName << endl;
			//process here
		} else if (input.substr(0,4) == "join" && isSignedIn) {
			string groupName;
			groupName = input.substr(5);

			cout << groupName << endl;
			//process join here
		} else if (input.substr(0,5) == "leave" && isSignedIn) {
			string groupName;
			groupName = input.substr(6);

			//process leave here
		} else if (input.substr(0,4) == "show" && isSignedIn) {
			string showFromUser;
			showFromUser = input.substr(5);

			//process show here
			//show protocol:
			//read from file
			//print new message str
			//ask from server
			vector<string> messages;
			messages = helper.fetchFromFile(showFromUser);
			messages.push_back(NEW_MESSAGE);
			//pushback all fetched new message from server
			string process;
			for (unsigned int i = 0; i < messages.size(); i++) {
				process = messages.at(i);
				cout << process << endl;
			}
		} else if (input.substr(0,6) == "logout" && isSignedIn) {
			//send logout
			Package toSend(Protocol::userLogout);
			toSend.send(*stream);
			break;
		}

		else {
			cout << "Invalid input, press enter to continue";
		}

		//here always check from server for new notif

		cout << endl;
		cin.ignore();
		cin.clear();
	}

}

