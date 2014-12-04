#include <algorithm>
#include <cstring>
#include <cstdio>
#include <chrono>

#include "Package.h"

using namespace std::chrono;

using std::copy;
using std::memset;
using std::sprintf;

Package::Package(int packageType) {
	this->packageType = packageType;

	this->reset();
}

Package::Package(const Package& package) {
	*this = package;
}

Package::Package(const char* buffer) {
	*this = buffer;
}

Package::~Package() {}

int Package::getPackageSize() {
	return dataSize + dataOffset;
}

int Package::getPackageType() const {
	return packageType;
}

void Package::setPackageType(int messageNum) {
	packageType = messageNum;
}

time_t Package::getPackageTime() const {
	return packageTime;
}

void Package::resetData() {
	// no action
}

Package& Package::operator=(const Package& rhs) {
	if(this != &rhs) {
		this->packageType = rhs.packageType;
		this->packageTime = rhs.packageTime;
	}

	return *this;
}

Package& Package::operator=(const char* buff) {
	this->packageType = (int)buff[0];
	this->packageTime = (time_t)buff[4];

	return *this;
}

void Package::reset() {
	this->resetTime();
}

void Package::resetTime() {
	packageTime = system_clock::to_time_t(system_clock::now());
}

ssize_t Package::send(TCPStream& stream) const {
	char buff[getPackageSize()];
	memset(buff, 0, sizeof(buff));

	sprintf(buff, "%d%d", packageType, (int)packageTime);

	ssize_t sent = stream.send(buff, getPackageSize());

	return sent;
}
