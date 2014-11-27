/*
 * DioskuriaMain.h
 *
 *  Created on: Nov 27, 2014
 *      Author: asseylum
 */

#ifndef DIOSKURIAMAIN_H_
#define DIOSKURIAMAIN_H_

#include "ServerThread.h"
#include <vector>

class DioskuriaMain {
public:
	DioskuriaMain();
	virtual ~DioskuriaMain();

	//static server wide shared variables here
	static std::vector<ServerThread> ThreadPool;
};

#endif /* DIOSKURIAMAIN_H_ */
