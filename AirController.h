/*
 * AirController.h
 *
 *  Created on: 21/07/2014
 *      Author: paco
 */

#ifndef AIRCONTROLLER_H_
#define AIRCONTROLLER_H_

#include "Singleton.h"

class AirController: public Singleton<AirController> {
public:
	AirController();
	virtual ~AirController();

	void doWork();
};

#endif /* AIRCONTROLLER_H_ */
