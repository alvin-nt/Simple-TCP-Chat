/* 
 * File:   GroupCreatePackage.h
 * Author: alvin-nt
 *
 * Created on December 6, 2014, 5:18 PM
 */

#ifndef GROUPCREATEPACKAGE_H
#define	GROUPCREATEPACKAGE_H

#include "Package.h"

class GroupCreatePackage : public Package {
private:
    int creatorId;
    char groupName[Protocol::USERNAME_MAXLENGTH];
    string description;
public:
    GroupCreatePackage(int creatorId, const string& groupName = "", const string& description = "");
    GroupCreatePackage(const GroupCreatePackage& orig);
    
    virtual ~GroupCreatePackage();
    
    void operator=(const GroupCreatePackage& rhs);
    
    void operator=(const char* buff);
    
    const int getCreatorId() const;
    
    void setCreatorId(int creatorId);
    
    const string getGroupName() const;
    
    void setGroupName(const string& groupName);
    
    const string& getGroupDescription() const;
    
    void setGroupDescription(const string& groupDescription);
private:
    void writeData(char* buff) const;
    
    void readData(const char* buff);
};

#endif	/* GROUPCREATEPACKAGE_H */

