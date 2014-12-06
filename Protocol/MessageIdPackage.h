/* 
 * File:   MessageIdPackage.h
 * Author: alvin-nt
 *
 * Created on December 6, 2014, 6:47 AM
 */

#ifndef MESSAGEIDPACKAGE_H
#define	MESSAGEIDPACKAGE_H

#include "Package.h"
#include "MessageId.h"

class MessageIdPackage : public Package {
private:
    MessageId messageId;
public:
    MessageIdPackage(const MessageId& messageId, int packageType = Protocol::messageRead);
    MessageIdPackage(const MessageIdPackage& orig);
    
    virtual ~MessageIdPackage();
    
    MessageId& getMessageId();
    const MessageId& getConstMessageId() const;
    
    void setMessageId(const MessageId& messageId);
private:
    void writeData(char* buff) const;
    void readData(const char* buff);
};

#endif	/* MESSAGEIDPACKAGE_H */

