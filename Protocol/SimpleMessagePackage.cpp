/* 
 * File:   SimpleMessagePackage.cpp
 * Author: alvin-nt
 * 
 * Created on December 6, 2014, 5:38 AM
 */

#include "SimpleMessagePackage.h"
#include <string>
#include <algorithm>

SimpleMessagePackage::SimpleMessagePackage(int packageType)
    : Package(packageType)
{
    message = "";
}

SimpleMessagePackage::SimpleMessagePackage(const SimpleMessagePackage& orig) 
    : Package(orig)
{
    message = orig.message;
}

SimpleMessagePackage::SimpleMessagePackage(const char* buff)
	: Package(buff)
{
	readData(buff);
}

SimpleMessagePackage::~SimpleMessagePackage()
{
    
}

const string& SimpleMessagePackage::getMessage() const {
    return message;
}

void SimpleMessagePackage::setMessage(const string& message) {
    this->message = message.substr(0, dataSize > message.length() ? dataSize : message.length());
}

void SimpleMessagePackage::writeData(char* buff) const {
    Package::writeData(buff);
    
    std::copy(message.begin(), message.end(), &buff[dataOffset]);
}

void SimpleMessagePackage::readData(const char* buff) {
    Package::readData(buff);
    
    message = string(&buff[dataOffset], dataSize);
}
