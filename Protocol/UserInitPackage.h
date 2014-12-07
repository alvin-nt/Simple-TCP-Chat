/* 
 * File:   UserSignupPackage.h
 * Author: alvin-nt
 *
 * Created on December 6, 2014, 4:18 AM
 */

#ifndef _UserInitPackage_H
#define	_UserInitPackage_H

#include "Package.h"

class UserInitPackage : public Package {
private:
    char username[Protocol::USERNAME_MAXLENGTH];
    unsigned char passwordHash[Protocol::USERNAME_MAXLENGTH];
public:
    UserInitPackage(int packageType = Protocol::userLogin);
    UserInitPackage(const UserInitPackage& orig);
    virtual ~UserInitPackage();
    
    const string getUserName() const;
    const string getUserPassword() const;
    
    void operator=(const UserInitPackage& rhs);
    void operator=(const char* buff);
    
    void setUserName(const char* username);
    void setUserName(const string& username);
    
    void setUserPassword(const char* password);
    void setUserPassword(const string& password);
    
    void setUserPasswordHash(const char* passwordHash);
private:
    void writeData(char* buff) const;
    void readData(const char* buff);
};

#endif	/* USERSIGNUPPACKAGE_H */

