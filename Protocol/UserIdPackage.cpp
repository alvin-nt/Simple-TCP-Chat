/* 
 * File:   UserIdPackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 6:41 AM
 */

#include "UserIdPackage.h"

UserIdPackage::UserIdPackage(int packageType, int userId)
    : Package(packageType)
{
    this->userId = userId;
}

UserIdPackage::UserIdPackage(const UserIdPackage& orig) 
    : Package(packageType)
{
    userId = orig.userId;
}

UserIdPackage::~UserIdPackage() {
}

const int UserIdPackage::getUserId() const {
    return userId;
}

void UserIdPackage::setUserId(int userId) {
    this->userId = userId;
}

void UserIdPackage::writeData(char* buff) const {
    Package::writeData(buff);
    
    int* ptrUserId = (int*)&buff[dataOffset];
    *ptrUserId = userId;
}

void UserIdPackage::readData(const char* buff) {
    Package::readData(buff);
    
    int* ptrUserId = (int*)&buff[dataOffset];
    userId = *ptrUserId;
}