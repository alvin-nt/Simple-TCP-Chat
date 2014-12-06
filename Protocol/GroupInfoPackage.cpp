/* 
 * File:   GroupInfoPackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 7:39 PM
 */

#include "GroupInfoPackage.h"
#include <algorithm>
#include <cstring>

using std::copy;
using std::memcpy;

GroupInfoPackage::GroupInfoPackage(int groupId, int memberCount, 
        time_t creationTime, const char* groupName, const char* groupMasterName) 
        : Package(Protocol::groupInfo)
{
    this->groupId = groupId;
    this->memberCount = memberCount;
    this->creationTime = creationTime;
    
    copy(groupName, groupName + sizeof(this->groupName), this->groupName);
    copy(groupMasterName, groupMasterName + sizeof(this->groupMasterName), this->groupMasterName);
}

GroupInfoPackage::GroupInfoPackage(const GroupInfoPackage& orig) 
    : Package(orig)
{
    *this = orig;
}

GroupInfoPackage::~GroupInfoPackage() {
}

void GroupInfoPackage::operator=(const GroupInfoPackage& rhs)
{
    if(this != &rhs) {
        groupId = rhs.groupId;
        memberCount = rhs.memberCount;
        creationTime = rhs.creationTime;
    
        copy(rhs.groupName, rhs.groupName + sizeof(groupName), groupName);
        copy(rhs.groupMasterName, rhs.groupMasterName + sizeof(groupMasterName), groupMasterName);
    }
}

void GroupInfoPackage::operator=(const char* buff)
{
    readData(buff);
}

int GroupInfoPackage::getGroupId() const {
    return groupId;
}

void GroupInfoPackage::setGroupId(int groupId) {
    this->groupId = groupId;
}

int GroupInfoPackage::getMemberCount() const {
    return memberCount;
}
void GroupInfoPackage::setMemberCount(int memberCount) {
    this->memberCount = memberCount;
}

time_t GroupInfoPackage::getCreationTime() const {
    return creationTime;
}
void GroupInfoPackage::setCreationTime(time_t creationTime) {
    this->creationTime = creationTime;
}

const string GroupInfoPackage::getGroupName() const {
    return string(groupName);
}
void GroupInfoPackage::setGroupName(const string& groupName) {
    string cpy = groupName.substr(0, sizeof(this->groupName));
    
    copy(cpy.begin(), cpy.end(), this->groupName);
}

const string GroupInfoPackage::getGroupMasterName() const {
    return string(groupMasterName);
}

void GroupInfoPackage::setGroupMasterName(const string& groupMasterName) {
    string cpy = groupMasterName.substr(0, sizeof(this->groupMasterName));
    
    copy(cpy.begin(), cpy.end(), this->groupMasterName);
}

void GroupInfoPackage::readData(const char* buff) {
    Package::readData(buff);
    
    memcpy(this, &buff[dataOffset], sizeof(GroupInfoPackage));
}

void GroupInfoPackage::writeData(char* buff) const {
    Package::writeData(buff);
    
    memcpy(&buff[dataOffset], this, sizeof(GroupInfoPackage));
}