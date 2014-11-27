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

	this->resetTime();
	this->resetData();
}

Package::Package(const Package& package) {
	*this = package;
}

Package::Package(const char* buffer) {
	this->packageType = (int)buffer[0];
	this->packageTime = (time_t)buffer[4];

	this->resetData();
	
	copy(buffer + 8, buffer + getPackageSize(), this->data);
}

Package::~Package() {
	delete data;
}

int Package::getPackageSize() {
	return dataSize + sizeof(int) + sizeof(time_t);
}

int Package::getPackageType() const {
	return packageType;
}

time_t Package::getPackageTime() const {
	return packageTime;
}

const char* Package::getDataPtr() {
	return data;
}

Package& Package::operator=(const Package& rhs) {
	if(this != &rhs) {
		this->packageType = rhs.packageType;
		this->packageTime = rhs.packageTime;

		this->resetData();
		copy(rhs.data, rhs.data + dataSize, this->data);
	}

	return *this;
}

void Package::reset() {
	this->resetTime();
	this->resetData();
}

void Package::resetTime() {
	packageTime = system_clock::to_time_t(system_clock::now());
}

void Package::resetData() {
	if(this->data == NULL) {
		this->data = new char[dataSize];
	}

	memset(this->data, 0, dataSize);
}

ssize_t Package::send(TCPStream& stream) const {
	char buff[getPackageSize()];
	memset(buff, 0, sizeof(buff));

	sprintf(buff, "%d%d", packageType, (int)packageTime);

	copy(data, data + dataSize, &buff[8]);

	ssize_t sent = stream.send(buff, getPackageSize());

	return sent;
}
