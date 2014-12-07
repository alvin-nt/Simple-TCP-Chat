/* 
 * File:   GroupJoinPackage.h
 * Author: alvin-nt
 *
 * Created on December 6, 2014, 9:31 PM
 */

#ifndef GROUPJOINPACKAGE_H
#define	GROUPJOINPACKAGE_H

#include "Package.h"

class GroupJoinPackage : public Package {
private:
    char userName[Protocol::USERNAME_MAXLENGTH];
    char groupName[Protocol::USERNAME_MAXLENGTH];
public:
    GroupJoinPackage(const string& userName, const string& groupName = "");
    GroupJoinPackage(const GroupJoinPackage& orig);
    GroupJoinPackage(const char* buff);
    virtual ~GroupJoinPackage();
    
    void operator=(const GroupJoinPackage& rhs);
    void operator=(const char* buff);
    
    string getUserName() const;
    void setUserName(const char* userName);
    void setUserName(const string& userName);
    
    const string getGroupName() const;
    void setGroupName(const string& groupName);
private:
    void readData(const char* buff);
    void writeData(char* buff) const;
};

#endif	/* GROUPJOINPACKAGE_H */

