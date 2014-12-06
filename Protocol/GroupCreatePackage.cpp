/* 
 * File:   GroupCreatePackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 5:18 PM
 */

#include "GroupCreatePackage.h"
#include <algorithm>

GroupCreatePackage::GroupCreatePackage(int creatorId, const string& groupName, const string& description) 
        : Package(Protocol::groupCreate)
{
    this->creatorId = creatorId;
    
    string copyStr = groupName.substr(0, Protocol::USERNAME_MAXLENGTH);
    
    std::copy(copyStr.begin(), copyStr.end(), this->groupName);
    
    this->description = description.substr(0, dataSize - Protocol::USERNAME_MAXLENGTH);
}

GroupCreatePackage::GroupCreatePackage(const GroupCreatePackage& orig) 
    : Package(orig)
{
    *this = orig;
}

GroupCreatePackage::~GroupCreatePackage() {
}

void GroupCreatePackage::operator=(const GroupCreatePackage& rhs)
{
    if(this != &rhs) {
        creatorId = rhs.creatorId;    
    
        std::copy(rhs.groupName, rhs.groupName + sizeof(groupName), this->groupName);
    
        this->description = rhs.description;
    }
}
    
void GroupCreatePackage::operator=(const char* buff)
{
    readData(buff);
}

const int GroupCreatePackage::getCreatorId() const {
    return creatorId;
}

void GroupCreatePackage::setCreatorId(int creatorId) {
    this->creatorId = creatorId;
}

const string GroupCreatePackage::getGroupName() const {
    return string(groupName, sizeof(groupName));
}

void GroupCreatePackage::setGroupName(const string& groupName) {
    string cpyStr = groupName.substr(0, Protocol::USERNAME_MAXLENGTH);
    
    std::copy(cpyStr.begin(), cpyStr.end(), this->groupName);
}

const string& GroupCreatePackage::getGroupDescription() const {
    return description;
}

void GroupCreatePackage::setGroupDescription(const string& groupDescription) {
    this->description = groupDescription;
}

void GroupCreatePackage::writeData(char* buff) const {
    Package::writeData(buff);
    
    int* ptrCreatorId = (int*)&buff[dataOffset];
    *ptrCreatorId = creatorId;
    
    std::copy(groupName, groupName + sizeof(groupName), &buff[dataOffset + sizeof(creatorId)]);
    
    std::copy(description.begin(), description.end(), &buff[dataOffset + sizeof(creatorId) + sizeof(groupName)]);
}

void GroupCreatePackage::readData(const char* buff) {
    Package::readData(buff);
    
    int* ptrCreatorId = (int*)&buff[dataOffset];
    creatorId = *ptrCreatorId;
    
    std::copy(&buff[dataOffset + sizeof(creatorId)], 
            &buff[dataOffset + sizeof(creatorId)] + sizeof(groupName), groupName);
    
    description = string(&buff[dataOffset + sizeof(creatorId) + sizeof(groupName)], 
                            dataSize - sizeof(creatorId) - sizeof(groupName));
}