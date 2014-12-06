/* 
 * File:   GroupInfoPackage.h
 * Author: alvin-nt
 *
 * Created on December 6, 2014, 7:39 PM
 */

#ifndef GROUPINFOPACKAGE_H
#define	GROUPINFOPACKAGE_H

#include "Package.h"

class GroupInfoPackage : public Package {
private:
    int groupId;
    int memberCount;
    time_t creationTime;
    char groupName[64];
    char groupMasterName[64];
public:
    GroupInfoPackage(int groupId, int memberCount, time_t creationTime, const char* groupName, const char* groupMasterName);
    GroupInfoPackage(const GroupInfoPackage& orig);

    virtual ~GroupInfoPackage();
    
    void operator=(const GroupInfoPackage& rhs);
    void operator=(const char* buff);
    
    int getGroupId() const;
    void setGroupId(int groupId);
    
    int getMemberCount() const;
    void setMemberCount(int memberCount);
    
    time_t getCreationTime() const;
    void setCreationTime(time_t creationTime);
    
    const string getGroupName() const;
    void setGroupName(const string& groupName);
    
    const string getGroupMasterName() const;
    void setGroupMasterName(const string& groupMasterName);
private:
    void writeData(char* buff) const;
    void readData(const char* buff);
};

#endif	/* GROUPINFOPACKAGE_H */

