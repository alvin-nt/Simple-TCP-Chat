/* 
 * File:   GroupCreatePackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 5:18 PM
 */

#include "GroupCreatePackage.h"
#include "ProtocolUtils.h"

#include <algorithm>
#include <cstring>

using namespace std;

GroupCreatePackage::GroupCreatePackage(const string& creatorName, const string& groupName, const string& description)
        : Package(Protocol::groupCreate)
{
	string copyStr = creatorName.substr(0, Protocol::USERNAME_MAXLENGTH);

	copy(copyStr.begin(), copyStr.end(), this->creatorName);

    copyStr = groupName.substr(0, Protocol::USERNAME_MAXLENGTH);
    
    copy(copyStr.begin(), copyStr.end(), this->groupName);
    
    this->description = description.substr(0, dataSize - (Protocol::USERNAME_MAXLENGTH << 1));
}

GroupCreatePackage::GroupCreatePackage(const GroupCreatePackage& orig) 
    : Package(orig)
{
    *this = orig;
}

GroupCreatePackage::GroupCreatePackage(const char* buff) {
	readData(buff);
}

GroupCreatePackage::~GroupCreatePackage() {
}

void GroupCreatePackage::operator=(const GroupCreatePackage& rhs)
{
    if(this != &rhs) {
        std::copy(rhs.creatorName, rhs.creatorName + sizeof(creatorName), creatorName);
    
        std::copy(rhs.groupName, rhs.groupName + sizeof(groupName), this->groupName);
    
        this->description = rhs.description;
    }
}
    
void GroupCreatePackage::operator=(const char* buff)
{
    readData(buff);
}

string GroupCreatePackage::getCreatorName() const {
	string ret(creatorName, sizeof(creatorName));
	ret = ProtocolUtils::trim(ret);

    return ret;
}

void GroupCreatePackage::setCreatorName(const char* creatorName) {
    copy(creatorName, creatorName + strnlen(creatorName, sizeof(this->creatorName)), this->creatorName);
}

void GroupCreatePackage::setCreatorName(const string& creatorName) {
	setCreatorName(creatorName.substr(0, sizeof(this->creatorName)).c_str());
}

const string GroupCreatePackage::getGroupName() const {
	string ret(groupName, sizeof(groupName));
	ret = ProtocolUtils::trim(ret);

	return ret;
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
    
    std::copy(creatorName, creatorName + sizeof(creatorName), &buff[dataOffset]);
    
    std::copy(groupName, groupName + sizeof(groupName), &buff[dataOffset + sizeof(creatorName)]);
    
    std::copy(description.begin(), description.end(), &buff[dataOffset + sizeof(creatorName) + sizeof(groupName)]);
}

void GroupCreatePackage::readData(const char* buff) {
    Package::readData(buff);
    
    copy(&buff[dataOffset], &buff[dataOffset] + sizeof(creatorName), creatorName);
    
    copy(&buff[dataOffset + sizeof(creatorName)],
            &buff[dataOffset + sizeof(creatorName)] + sizeof(groupName), groupName);
    
    description = string(&buff[dataOffset + sizeof(creatorName) + sizeof(groupName)],
                            dataSize - sizeof(creatorName) - sizeof(groupName));
    description = ProtocolUtils::trim(description);
}
