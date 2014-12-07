/*
 * User.cpp
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#include "../ServerClasses/User.h"
#include <cstring>

using namespace std;

User::User() {

}

User::User(string _username, string _password) {
	username = _username;
	password = _password;
}

User::~User() {
}

string User::login(string _username, string _password) {
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
	username = _username;
	password = _password;
	bool isUserExist = queryUser();
	if (isUserExist) {
		string message = username + " already exists!";
		Utils::writeServerLog(message);
		return USER_SIGNUP_FAILED;
	}
	else {
		string ret = createUser();
		return ret;
	}
}

string User::getUserName() {
	return username;
}

string User::getPassword() {
	return password;
}

bool User::queryUser() {
	userFileMutex.lock();
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
	userFileMutex.unlock();
	return found;
}

string User::createUser() {
	userFileMutex.lock();
	ofstream outfile;
	outfile.open("UserDatabase.txt", ios::app);
	if (outfile.is_open()) {
		outfile << username << ";" << password << endl;
		outfile.close();
		userFileMutex.unlock();
		string message = username + " successfully signed up!";
		Utils::writeServerLog(message);
		return USER_SIGNUP_SUCCESS;
	} else {
		outfile.close();
		userFileMutex.unlock();
		string message = "Signup failed, cannot open file";
		Utils::writeServerLog(message);
		return USER_SIGNUP_FAILED;
	}
}

void User::loadMessages() {
	messageFileMutex.lock();

	string filename = username + "-messages.txt";
	ifstream input;
	input.open(filename.c_str(), ifstream::in);
	if (input.is_open()) {
		string process;
		string delimiter = ";";
		while (getline(input, process)) {
			struct Message temp;
			int initialDelimiter = process.find(delimiter);

			temp.sender = process.substr(0, initialDelimiter);

			string timeStr = process.substr(initialDelimiter + 1,
								process.rfind(delimiter) - temp.sender.length() - 1);

			cout << timeStr << endl;

			struct tm timeStruct;
			memset(&timeStruct, 0, sizeof(struct tm));
			strptime(timeStr.c_str(), "[%Y-%m-%d %X]", &timeStruct);

			temp.time = mktime(&timeStruct);

			temp.message = process.substr(process.rfind(delimiter) + 1);
			unseenMessage.push_back(temp);
		}
	}
	input.close();
	clearMessageFile();
	messageFileMutex.unlock();
}

vector<string> User::getMessageFrom(string user) {
	vector<int> temp;
	vector<string> ret;
	for(unsigned int i = 0; i < unseenMessage.size(); i++) {
		if (unseenMessage.at(i).sender == user) {
			temp.push_back(i);
			ret.push_back(unseenMessage.at(i).message);
		}
	}
	for (unsigned int i = 0; i < temp.size(); i++) {
		unseenMessage.erase(unseenMessage.begin()+temp.at(i)-i);
	}
	return ret;
}

void User::clearMessageFile() {
	string filename = username + "-messages.txt";
	ofstream output;
	output.open(filename.c_str(), fstream::out | fstream::trunc);
	output.close();
	remove(filename.c_str());
}

void User::dumpMessageTo(string user, time_t time, string message) {
	messageFileMutex.lock();

	string filename = user + "-messages.txt";
	ofstream outfile;
	outfile.open(filename.c_str(), ios::app);
	outfile << username << ";" << Utils::dateTime(time) + ";" + message << endl;
	outfile.close();

	messageFileMutex.unlock();
}

void User::dumpMessageTo(string groupname, string user, string message) {
	messageFileMutex.lock();
	string filename = user + "-messages.txt";
	ofstream outfile;
	outfile.open(filename.c_str(), ios::app);
	outfile << groupname << ";" << Utils::currentDateTime() + " " + message << endl;
	outfile.close();
	messageFileMutex.unlock();
}

vector<string> User::getUniqueSenderList() {
	vector<string> ret;
	for (unsigned int i = 0; i < unseenMessage.size(); i++) {
		string send = unseenMessage.at(i).sender;
		bool isPresent = (find(ret.begin(), ret.end(), send) != ret.end());
		if (!isPresent) {
			ret.push_back(unseenMessage.at(i).sender);
		}
	}
	return ret;
}

bool User::isUserExists(string user) {
	userFileMutex.lock();
	bool exists = false;
	string fileName = "UserDatabase.txt";
	ifstream userFile;
	userFile.open(fileName.c_str(), ifstream::in);
	string process;
	string delimiter = ";";
	while (getline(userFile, process) && !exists) {
		if (process.substr(0, process.find(delimiter)) == user) {
			exists = true;
		}
	}
	userFile.close();
	userFileMutex.unlock();
	return exists;
}
