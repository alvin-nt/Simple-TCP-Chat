#ifndef _Package_H
#define _Package_H

#include "Protocol.h"
#include "TCPStream.h"

class Package {
protected:
	static const int dataSize = 504;

	int packageType;
	time_t packageTime;

	static const int dataOffset = sizeof(packageType) + sizeof(packageTime);
public:
	/**
	 * Initializes an empty package
	 * @param packageType the type of package, as defined in {@link Protocol}
	 */
	Package(int packageType);

	/**
	 * Clones a package
	 * @param package the package going to be cloned
	 */
	Package(const Package& package);

	/**
	 * Create a package from a char* buffer
	 *
	 * NOTE: this assumes that the char* buffer length is 512
	 */
	Package(const char* buffer);

	/**
	 * Destroys this package: clears the data, and then returns it to the heap
	 */
	~Package();

	/**
	 * Get the package size in int
	 * @return the package size
	 */
	static int getPackageSize();

	/**
	 * Get the type of package
	 * @return packageType, as defined in the protocol
	 */
	int getPackageType() const;

	/**
	 * Set the type of package
	 * @param messageNum the packageType, as defined in the protocol
	 */
	void setPackageType(int messageNum);

	/**
	 * Get the package's timestamp
	 * @return package timestamp, in {@link time_t}
	 */
	time_t getPackageTime() const;

	/**
	 * Copies a package
	 * @param rhs the package going to be copied
	 * @return self-reference
	 */
	Package& operator=(const Package& rhs);

	/**
	 * Assigns the values in the package based on a char buffer
	 * @param buff the char buffer
	 * @return self-reference
	 */
	Package& operator=(const char* buff);

	/**
	 * Clears a package, and resets the time
	 * wrapper for resetTime() and resetData();
	 */
	void reset();

	/**
	 * Resets the time to the current time
	 */
	void resetTime();

	/**
	 * Clears the data
	 */
	virtual void resetData();

	/**
	 * Sends a package through a TCPStream object
	 * @param  stream TCPStream reference
	 * @return        number of bytes written, in POSIX standard
	 */
	virtual ssize_t send(TCPStream& stream) const;

protected:
	/**
	 * Writes the package data into a buffer
	 * @param buff the data buffer
	 */
	virtual void writeData(char* buff) const;

	/**
	 * Read the package data from a buffer
	 * @param buff the data buffer
	 */
	virtual void readData(const char* buff);
};

#endif