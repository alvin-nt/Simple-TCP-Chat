/* 
 * File:   MessageRecvPackage.h
 * Author: alvin-nt
 *
 * Created on December 6, 2014, 9:41 PM
 */
#include "Package.h"
#include <chrono>

#ifndef MESSAGERECVPACKAGE_H
#define	MESSAGERECVPACKAGE_H

using namespace std::chrono;

class MessageRecvPackage : public Package
{
public:
    static const char PACKAGE_END = '0';
    static const char PACKAGE_NEXT = '1';
    
private:
    char sender[Protocol::USERNAME_MAXLENGTH];
	time_t messageTime;
    string message;
public:
    static const size_t maxMessageSize = dataSize - sizeof(char) - sizeof(sender) - sizeof(messageTime);
    static const size_t messageOffset = dataOffset + sizeof(char) + sizeof(sender) - sizeof(messageTime);

    MessageRecvPackage(const string& sender, time_t messageTime = system_clock::to_time_t(system_clock::now()),
    					const string& message = "");
    MessageRecvPackage(const MessageRecvPackage& orig);
    MessageRecvPackage(const char* buff);
    virtual ~MessageRecvPackage();
    
    void operator=(const MessageRecvPackage& rhs);
    void operator=(const char* buff);
    
    string getMessageSender() const;
    void setMessageSender(const char* sender);
    void setMessageSender(const string& sender);

    time_t getMessageTime() const;
    void setMessageTime(time_t time);

    const string& getMessage() const;
    void setMessage(const string& message);
    ssize_t send(TCPStream& stream) const;

    static ssize_t receive(MessageRecvPackage& package, TCPStream& stream);
private:
    void writeData(char* buff, bool end, int offset, int len) const;
    void readData(const char* buff);
};

#endif	/* MESSAGERECVPACKAGE_H */

