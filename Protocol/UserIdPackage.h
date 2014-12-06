/* 
 * File:   UserIdPackage.h
 * Author: alvin-nt
 *
 * Created on December 6, 2014, 6:41 AM
 */

#ifndef USERIDPACKAGE_H
#define	USERIDPACKAGE_H

#include "Package.h"

class UserIdPackage : public Package {
private:
    int userId;
public:
    UserIdPackage(int packageType, int userId);
    UserIdPackage(const UserIdPackage& orig);
    virtual ~UserIdPackage();
    
    const int getUserId() const;
    
    void setUserId(int userId);
private:
    void writeData(char* buff) const;
    void readData(const char* buff);
};

#endif	/* USERIDPACKAGE_H */

