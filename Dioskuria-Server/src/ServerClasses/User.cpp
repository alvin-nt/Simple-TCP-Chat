/*
 * User.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "../ServerClasses/User.h"

using namespace std;

User::User() {

}

User::User(string _username, string _password) {
	username = _username;
	password = _password;
}

User::~User() {
	// TODO Auto-generated destructor stub
}

string User::login(string _username, string _password) {
	//TODO pengecekan password dan log
	username = _username;
	bool res = queryUser();
	if (res && (password == _password)) {
		Utils::writeServerLog(username + " logged in");
		return USER_LOGIN_SUCCESS;
	} else {
		return USER_LOGIN_INVALID;
	}
}

string User::newUser(string _username, string _password) {
	//TODO pengecekan user exist dan log
	username = _username;
	password = _password;
	if (queryUser()) {
		string message = username + " already exists!";
		Utils::writeServerLog(message);
		return USER_SIGNUP_FAILED;
	} else {
		return createUser();
	}
}

string User::getUserName() {
	return username;
}

string User::getPassword() {
	return password;
}

bool User::queryUser() {
	//TODO some lookup to file on user pass list, add mutex
	fstream userFile;
	bool found = false;
	userFile.open("UserDatabase.txt", fstream::in | fstream::out | fstream::app);
	string process, process2;
	string delimiter = ";";
	while (getline(userFile, process) && !found) {
		process2 = process.substr(0, process.find(delimiter));
		if (process2 == username) {
			password = process.substr(process.find(delimiter)+1);
			found = true;
		}
	}
	userFile.close();
	return found;
}

string User::createUser() {
	//TODO some mutex
	if (!queryUser()) {
		ofstream outfile;
		outfile.open("UserDatabase.txt", ios::app);
		if (outfile.is_open()) {
			outfile << username << ";" << password << endl;
			outfile.close();
			string message = username + " successfully signed up!";
			Utils::writeServerLog(message);
			return USER_SIGNUP_SUCCESS;
		} else {
			string message = "Signup failed, cannot open file";
			Utils::writeServerLog(message);
			outfile.close();
			return USER_SIGNUP_FAILED;
		}
	} else {
		string message = "Signup failed, user already exist";
		Utils::writeServerLog(message);
		return USER_SIGNUP_FAILED;
	}
}

void User::loadMessages() {
	string filename = username + "-messages.txt";
	ifstream input;
	input.open(filename.c_str(), ifstream::in);
	if (input.is_open()) {
		string process;
		string delimiter = ";";
		while (getline(input, process)) {
			struct QueuedMessage temp;
			temp.sender = process.substr(0, process.find(delimiter));
			temp.message = process.substr(process.find(delimiter)+1);
			unseenMessage.push_back(temp);
		}
	}
	input.close();
	clearMessageFile();
}

void User::deleteMessageFrom(string user) {
	string filename = username + "-messages.txt";
	string filename2 = username + "-messages-temp.txt";
	ifstream input(filename);
	ofstream output(filename2);
	string process, process2;
	string delimiter = ";";
	while (getline(input, process)) {
		if (user != process.substr(0, process.find(delimiter))) {
			output << process << endl;
		}
	}
	input.clear();
	input.seekg(0,ios::beg);
	input.close();
	output.close();
	remove(filename.c_str());
	rename(filename2.c_str(),filename.c_str());
}

void User::clearMessageFile() {
	string filename = username + "-messages.txt";
	ofstream output;
	output.open(filename.c_str(), fstream::out | fstream::trunc);
	output.close();
}
