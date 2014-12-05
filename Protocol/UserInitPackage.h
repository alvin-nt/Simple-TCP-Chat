/* 
 * File:   UserSignupPackage.h
 * Author: alvin-nt
 *
 * Created on December 6, 2014, 4:18 AM
 */

#ifndef _UserInitPackage_H
#define	_UserInitPackage_H

#include "Package.h"
#include <openssl/sha.h>

class UserInitPackage : public Package {
private:
    char username[Protocol::USERNAME_MAXLENGTH];
    unsigned char passwordHash[SHA512_DIGEST_LENGTH];
public:
    UserInitPackage(int packageType);
    UserInitPackage(const UserInitPackage& orig);
    virtual ~UserInitPackage();
    
    const string getUserName() const;
    const string getUserPasswordHash() const;
    
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

