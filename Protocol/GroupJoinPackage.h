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
    int userId;
    char groupName[Protocol::USERNAME_MAXLENGTH];
public:
    GroupJoinPackage(int userId, const char* groupName = "");
    GroupJoinPackage(const GroupJoinPackage& orig);
    virtual ~GroupJoinPackage();
    
    void operator=(const GroupJoinPackage& rhs);
    void operator=(const char* buff);
    
    int getUserId() const;
    void setUserId(int userId);
    
    const string getGroupName() const;
    void setGroupname(const string& groupName);
private:
    void readData(const char* buff);
    void writeData(char* buff) const;
};

#endif	/* GROUPJOINPACKAGE_H */

