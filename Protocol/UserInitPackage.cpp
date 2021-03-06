/* 
 * File:   UserSignupPackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 4:18 AM
 */

#include "UserInitPackage.h"
#include <algorithm>
#include <cstring>
#include <exception>
#include <sstream>

using namespace std;

UserInitPackage::UserInitPackage(int packageType) : Package(packageType)
{
    memset(username, 0, sizeof(username));
    memset(passwordHash, 0, sizeof(passwordHash));
}

UserInitPackage::UserInitPackage(const UserInitPackage& orig) 
    : Package(orig)
{
    copy(orig.username, orig.username + sizeof(username), username);
    copy(orig.passwordHash, orig.passwordHash + sizeof(passwordHash), passwordHash);
}

UserInitPackage::UserInitPackage(const char* buff)
	: Package(buff)
{
	*this = buff;
}

UserInitPackage::~UserInitPackage() {
}

const string UserInitPackage::getUserName() const {
	stringstream ss;
	for(unsigned i = 0; i < sizeof(username); i++) {
		if(username[i] != 0x00)
			ss << username[i];
	}

    return ss.str();
}

const string UserInitPackage::getUserPassword() const {
	stringstream ss;
	for(unsigned i = 0; i < sizeof(passwordHash); i++) {
		if(passwordHash[i] != 0x00)
			ss << passwordHash[i];
	}

    return ss.str();
}

void UserInitPackage::setUserName(const char* username) {
    copy(username, username + strnlen(username, sizeof(this->username)), this->username);
}

void UserInitPackage::setUserName(const string& username) {
    setUserName(username.substr(0, Protocol::USERNAME_MAXLENGTH).c_str());
}

void UserInitPackage::setUserPassword(const char* password) {
	copy(password, password + strnlen(password, sizeof(this->passwordHash)), this->passwordHash);
}

void UserInitPackage::setUserPassword(const string& password) {
    setUserPassword(password.c_str());
}

void UserInitPackage::operator=(const UserInitPackage& rhs) {
    if(this != &rhs) {
        packageType = rhs.packageType;
        copy(rhs.username, rhs.username + sizeof(username), username);
        copy(rhs.passwordHash, rhs.passwordHash + sizeof(passwordHash), passwordHash);
    }
}

void UserInitPackage::operator=(const char* buff) {
    readData(buff);
}

void UserInitPackage::writeData(char* buff) const {
    Package::writeData(buff);
    
    copy(username, username + sizeof(username), &buff[dataOffset]);
    
    copy(passwordHash, passwordHash + sizeof(passwordHash), &buff[dataOffset + sizeof(username)]);
}

void UserInitPackage::readData(const char* buff) {
    Package::readData(buff);
    
    copy(&buff[dataOffset], &buff[dataOffset] + sizeof(username), username);
    
    copy(&buff[dataOffset + sizeof(username)],
            &buff[dataOffset + sizeof(username)] + sizeof(passwordHash), passwordHash);
}
