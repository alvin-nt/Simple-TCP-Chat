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

#include "Protocol/GroupJoinPackage.h"
#include "Protocol/GroupCreatePackage.h"
#include "Protocol/MessageRecvPackage.h"
#include "Protocol/MessageSendPackage.h"
#include "Protocol/SimpleMessagePackage.h"
#include "Protocol/UserInitPackage.h"

#include <cstring>
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

	string userName;

	while(1) {
		char buffer[512] = {};

		cout << "> "; getline(cin, input);
		if(input == "signup" && !isSignedIn) {
			string username, password;
			cout << "Name		: "; cin >> username;
			cout << "Password	: "; cin >> password;
			
			UserInitPackage toSend(Protocol::userSignup);
			toSend.setUserName(username);
			toSend.setUserPassword(password);

			toSend.send(*stream);

			stream->receive(buffer, sizeof(buffer));

			SimpleMessagePackage response = buffer;
			if (response.getPackageType() == Protocol::userSignupSuccess) {
				isSignedIn = true;
				userName = username;
				cout << SIGNUP_SUCCESS << endl;
			} else if (response.getPackageType() == Protocol::userSignupFail) {
				cout << SIGNUP_FAILED << endl;
			}
		} else if (input == "login" && !isSignedIn) {
			string username, password;
			cout << "Name		: "; cin >> username;
			cout << "Password	: "; cin >> password;

			//process login begins here
			//TODO add real data to package, refer to ServerThread.cpp for server dummy implementation
			UserInitPackage toSend(Protocol::userLogin);
			toSend.setUserName(username);
			toSend.setUserPassword(password);

			toSend.send(*stream);

			stream->receive(buffer, sizeof(buffer));

			SimpleMessagePackage response(buffer);
			if (response.getPackageType() == Protocol::userLoginSuccess) {
				isSignedIn = true;
				userName = username;
				cout << LOGIN_SUCCESS << endl;
			} else if (response.getPackageType() == Protocol::userLoginFail) {
				cout << LOGIN_FAILED << ": " << response.getMessage() << endl;
			}
		} else if (input.substr(0,7) == "message" && isSignedIn) {
			string recipient, message;
			recipient = input.substr(8);
			cout << "Message : " << endl;
			getline(cin, message);

			cout << recipient << " " << message << endl;

			//process message here
			MessageSendPackage package(recipient, message);
			package.send(*stream);

			stream->receive(buffer, sizeof(buffer));

			SimpleMessagePackage response = buffer;
			int packageType = response.getPackageType();
			if(packageType == Protocol::messageSendSuccess) {
				cout << "Message sent successfully" << endl;
			} else if (packageType == Protocol::messageSendFailed) {
				cout << "Error:  " << response.getMessage() << endl;
			}
		} else if (input.substr(0,6) == "create" && isSignedIn) {
			string groupName;
			groupName = input.substr(7);

			cout << groupName << endl;

			//process here
			GroupCreatePackage package(userName, groupName);
			package.send(*stream);

			stream->receive(buffer, sizeof(buffer));

			SimpleMessagePackage response = buffer;
			int packageType = response.getPackageType();
			if(packageType == Protocol::groupCreateSuccess) {
				cout << "Group created successfully" << endl;
			} else if (packageType == Protocol::groupCreateFail) {
				cout << "Error:  " << response.getMessage() << endl;
			}

		} else if (input.substr(0,4) == "join" && isSignedIn) {
			string groupName;
			groupName = input.substr(5);

			cout << groupName << endl;

			GroupJoinPackage package(userName, groupName);
			package.send(*stream);

			stream->receive(buffer, sizeof(buffer));

			SimpleMessagePackage response = buffer;
			int packageType = response.getPackageType();
			if(packageType == Protocol::groupJoinSuccess) {
				cout << "Joined group " << groupName << endl;
			} else if (packageType == Protocol::groupJoinFail) {
				cout << "Error:  " << response.getMessage() << endl;
			}
		} else if (input.substr(0,5) == "leave" && isSignedIn) {
			string groupName;
			groupName = input.substr(6);

			SimpleMessagePackage package(Protocol::groupLeave);
			package.setMessage(groupName.substr(0, Protocol::USERNAME_MAXLENGTH));

			package.send(*stream);

			SimpleMessagePackage response = buffer;
			int packageType = response.getPackageType();
			if(packageType == Protocol::groupLeaveSuccess) {
				cout << "Left group " << groupName << endl;
			} else if (packageType == Protocol::groupLeaveFail) {
				cout << "Error:  " << response.getMessage() << endl;
			}
		} else if (input.substr(0,4) == "show" && isSignedIn) {
			string showFromUser;
			showFromUser = input.substr(5);

			vector<string> messages;
			messages = helper.fetchFromFile(showFromUser);

			// pushback all fetched new message from server
			Package request(Protocol::messageRecvRequest);
			request.send(*stream);

			stream->receive(buffer, sizeof(buffer), MSG_PEEK);
			// read the responses from here
			MessageRecvPackage receivedMessage = buffer;

			while (receivedMessage.getPackageType() == Protocol::messageRecv) {
				MessageRecvPackage::receive(receivedMessage, *stream);

				char buff[100] = {};
				time_t msgTime = receivedMessage.getMessageTime();
				strftime(buff, sizeof(buff), "%F %T", localtime(&msgTime));

				string format = "[" + string() + buff +
								" - " + receivedMessage.getMessageSender() + "]" +
								receivedMessage.getMessage();

				messages.push_back(format);

				stream->receive(buffer, sizeof(buffer), MSG_PEEK);
				receivedMessage = buffer;
			}

			// flush
			stream->receive(buffer, sizeof(buffer));

			if(!messages.empty()) {
				cout << NEW_MESSAGE << endl;
				for (auto message: messages) {
					cout << message << endl;
				}
			} else {
				cout << "No new messages" << endl;
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
