/* 
 * File:   MessageRecvPackage.h
 * Author: alvin-nt
 *
 * Created on December 6, 2014, 9:41 PM
 */
#include "MessageIdPackage.h"

#ifndef MESSAGERECVPACKAGE_H
#define	MESSAGERECVPACKAGE_H

class MessageRecvPackage : public MessageIdPackage
{
public:
    static const char PACKAGE_END = '0';
    static const char PACKAGE_NEXT = '1';
    
    static const int maxMessageSize = 486;
    static const int messageOffset = dataOffset + sizeof(char) + sizeof(messageId);;
private:
    string message;
public:
    MessageRecvPackage(const MessageId& messageId, const string& message = "");
    MessageRecvPackage(const MessageRecvPackage& orig);
    virtual ~MessageRecvPackage();
    
    void operator=(const MessageRecvPackage& rhs);
    void operator=(const char* buff);
    
    const string& getMessage() const;
    void setMessage(const string& message);
    ssize_t send(TCPStream& stream) const;
private:
    void writeData(char* buff, bool end, int offset, int len) const;
    void readData(const char* buff);
};

#endif	/* MESSAGERECVPACKAGE_H */

