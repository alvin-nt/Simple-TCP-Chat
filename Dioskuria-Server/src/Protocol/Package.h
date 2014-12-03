#ifndef _Package_H
#define _Package_H

#include "Protocol.h"
#include "TCPStream.h"

class Package {
protected:
	static const int dataSize = 504;

	int packageType;
	time_t packageTime;
	char* data;
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
	 * Get the package's timestamp
	 * @return package timestamp, in {@link time_t}
	 */
	time_t getPackageTime() const;

	/**
	 * Get the pointer to package data
	 * @return pointer to package data
	 */
	const char* getDataPtr();

	/**
	 * Copies a package
	 * @param rhs the package going to be copied
	 */
	Package& operator=(const Package& rhs);

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
	void resetData();

	/**
	 * Sends a package through a TCPStream object
	 * @param  stream TCPStream reference
	 * @return        number of bytes written, in POSIX standard
	 */
	virtual ssize_t send(TCPStream& stream) const;
};

#endif