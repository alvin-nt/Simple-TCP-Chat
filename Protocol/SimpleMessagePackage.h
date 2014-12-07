/* 
 * File:   SimpleMessagePackage.h
 * Author: alvin-nt
 *
 * Created on December 6, 2014, 5:38 AM
 */

#ifndef SIMPLEMESSAGEPACKAGE_H
#define	SIMPLEMESSAGEPACKAGE_H

#include "Package.h"

class SimpleMessagePackage : public Package {
private:
    string message;
public:
    SimpleMessagePackage(int packageType);
    SimpleMessagePackage(const SimpleMessagePackage& orig);
    SimpleMessagePackage(const char* buff);
    
    const string& getMessage() const;
    
    void setMessage(const string& message);
    
    virtual ~SimpleMessagePackage();
private:
    void writeData(char* buff) const;
    void readData(const char* buff);
};

#endif	/* SIMPLEMESSAGEPACKAGE_H */

