/* 
 * File:   GroupJoinPackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 9:31 PM
 */

#include "GroupJoinPackage.h"

#include <algorithm>

using namespace std;

GroupJoinPackage::GroupJoinPackage(const string& userName, const string& groupName)
    : Package(Protocol::groupJoin)
{
    setUserName(userName);
    setGroupName(groupName);
}

GroupJoinPackage::GroupJoinPackage(const GroupJoinPackage& orig) 
    : Package(orig)
{
    *this = orig;
}

GroupJoinPackage::GroupJoinPackage(const char* buff)
	: Package(buff)
{
	readData(buff);
}

GroupJoinPackage::~GroupJoinPackage() 
{
}

void GroupJoinPackage::operator=(const GroupJoinPackage& rhs) {
    if(this != &rhs) {
        copy(rhs.userName, rhs.userName + sizeof(userName), userName);
        copy(rhs.groupName, rhs.groupName + sizeof(groupName), groupName);
    }
}

void GroupJoinPackage::operator=(const char* buff) {
    readData(buff);
}

string GroupJoinPackage::getUserName() const {
    return string(userName, sizeof(userName));
}
void GroupJoinPackage::setUserName(const char* userName) {
    copy(userName, userName + sizeof(this->userName), this->userName);
}

void GroupJoinPackage::setUserName(const string& userName) {
	setUserName(userName.substr(0, sizeof(this->userName)).c_str());
}

const string GroupJoinPackage::getGroupName() const {
    return string(groupName, sizeof(groupName));
}

void GroupJoinPackage::setGroupName(const string& groupName) {
    string cpy = groupName.substr(0, Protocol::USERNAME_MAXLENGTH);
    
    copy(cpy.begin(), cpy.end(), this->groupName);
}

void GroupJoinPackage::readData(const char* buff) {
    Package::readData(buff);
    
    copy(&buff[dataOffset], &buff[dataOffset] + sizeof(userName), userName);
    
    copy(&buff[dataOffset + sizeof(userName)],
            &buff[dataOffset + sizeof(userName)] + sizeof(groupName),
         groupName);
}

void GroupJoinPackage::writeData(char* buff) const {
    Package::writeData(buff);
    
    copy(userName, userName + sizeof(userName), &buff[dataOffset]);
    
    copy(groupName, &(groupName[0 + sizeof(groupName)]), &buff[dataOffset + sizeof(userName)]);
}
