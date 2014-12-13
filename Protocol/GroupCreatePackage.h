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
    char creatorName[Protocol::USERNAME_MAXLENGTH];
    char groupName[Protocol::USERNAME_MAXLENGTH];
    string description;
public:
    GroupCreatePackage(const string& creatorName, const string& groupName = "", const string& description = "");
    GroupCreatePackage(const GroupCreatePackage& orig);
    GroupCreatePackage(const char* buff);
    
    virtual ~GroupCreatePackage();
    
    void operator=(const GroupCreatePackage& rhs);
    
    void operator=(const char* buff);
    
    string getCreatorName() const;
    
    void setCreatorName(const char* creatorName);

    void setCreatorName(const string& creatorName);
    
    const string getGroupName() const;
    
    void setGroupName(const string& groupName);
    
    const string& getGroupDescription() const;
    
    void setGroupDescription(const string& groupDescription);
private:
    void writeData(char* buff) const;
    
    void readData(const char* buff);
};

#endif	/* GROUPCREATEPACKAGE_H */

