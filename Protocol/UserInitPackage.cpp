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

UserInitPackage::~UserInitPackage() {
}

const string UserInitPackage::getUserName() const {
    return string(username, sizeof(username));
}

const string UserInitPackage::getUserPasswordHash() const {
    char mdString[SHA512_DIGEST_LENGTH * 2 + 1];
    
    for(int i = 0; i < SHA512_DIGEST_LENGTH; i++)
         sprintf(&mdString[i*2], "%02x", (unsigned int)passwordHash[i]);
    return string(mdString, sizeof(mdString));
}

void UserInitPackage::setUserName(const char* username) {
    copy(username, username + Protocol::USERNAME_MAXLENGTH, this->username);
}

void UserInitPackage::setUserName(const string& username) {
    setUserName(username.substr(0, Protocol::USERNAME_MAXLENGTH).c_str());
}

void UserInitPackage::setUserPassword(const char* password) {
    SHA512((unsigned char*)password, strlen(password), passwordHash);
}

void UserInitPackage::setUserPassword(const string& password) {
    setUserPassword(password.c_str());
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