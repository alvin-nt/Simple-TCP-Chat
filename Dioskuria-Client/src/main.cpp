/*
 * main.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: asseylum
 */

#include "Helper.h"
#include "Constants.h"
#include <iostream>
#include <string>

using namespace std;

int main(void) {
	string input,dummy;
	Helper helper;
	while(1){
		cout << "> "; getline(cin, input);
		if(input == "signup") {
			string username, password;
			cout << "Name		: "; cin >> username;
			cout << "Password	: "; cin >> password;
			cout << username << " " << password << endl;
			//proses signup begins here
		} else if (input == "login") {
			string username, password;
			cout << "Name		: "; cin >> username;
			cout << "Password	: "; cin >> password;
			cout << username << " " << password << endl;
			//process login begins here
		} else if (input.substr(0,7) == "message") {
			string recipient, message;
			recipient = input.substr(8);
			cout << "Message : " << endl;
			getline(cin, message);

			cout << recipient << " " << message << endl;
			//process message here
		} else if (input.substr(0,6) == "create") {
			string groupName;
			groupName = input.substr(7);

			cout << groupName << endl;
			//process here
		} else if (input.substr(0,4) == "join") {
			string groupName;
			groupName = input.substr(5);

			cout << groupName << endl;
			//process join here
		} else if (input.substr(0,5) == "leave") {
			string groupName;
			groupName = input.substr(6);

			//process leave here
		} else if (input.substr(0,4) == "show") {
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

