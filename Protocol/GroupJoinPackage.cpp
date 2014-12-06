/* 
 * File:   GroupJoinPackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 9:31 PM
 */

#include "GroupJoinPackage.h"

#include <algorithm>

using namespace std;

GroupJoinPackage::GroupJoinPackage(int userId, const char* groupName) 
    : Package(Protocol::groupJoin)
{
    this->userId = userId;
    copy(groupName, groupName + sizeof(this->groupName), this->groupName);
}

GroupJoinPackage::GroupJoinPackage(const GroupJoinPackage& orig) 
    : Package(orig)
{
    *this = orig;
}

GroupJoinPackage::~GroupJoinPackage() 
{
}

void GroupJoinPackage::operator=(const GroupJoinPackage& rhs) {
    if(this != &rhs) {
        userId = rhs.userId;
        copy(rhs.groupName, rhs.groupName + sizeof(groupName), groupName);
    }
}

void GroupJoinPackage::operator=(const char* buff) {
    readData(buff);
}

int GroupJoinPackage::getUserId() const {
    return userId;
}
void GroupJoinPackage::setUserId(int userId) {
    this->userId = userId;
}

const string GroupJoinPackage::getGroupName() const {
    return string(groupName, sizeof(groupName));
}

void GroupJoinPackage::setGroupname(const string& groupName) {
    string cpy = groupName.substr(0, Protocol::USERNAME_MAXLENGTH);
    
    copy(cpy.begin(), cpy.end(), this->groupName);
}

void GroupJoinPackage::readData(const char* buff) {
    Package::readData(buff);
    
    int* ptrUserId = (int*)&buff[dataOffset];
    userId = *ptrUserId;
    
    copy(&buff[dataOffset + sizeof(userId)], 
            &buff[dataOffset + sizeof(userId)] + sizeof(groupName), 
         groupName);
}

void GroupJoinPackage::writeData(char* buff) const {
    Package::writeData(buff);
    
    int* ptrUserId = (int*)&buff[dataOffset];
    *ptrUserId = userId;
    
    copy(groupName, &(groupName[0 + sizeof(groupName)]), &buff[dataOffset + sizeof(userId)]);
}