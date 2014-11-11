/*
 * AirController.cpp
 *
 *  Created on: 21/07/2014
 *      Author: paco
 */

#include "AirController.h"
#include "Airport.h"
#include "Flight.h"
#include "Position.h"
#include <list>

AirController::AirController() {
	// TODO Auto-generated constructor stub

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void
AirController::doWork()
{
	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	std::list<Flight*>::iterator it;

	Position pos1(500.0, 0.0, 100.0);
	Position pos2(0.0, 0.0, 25.0);
	Position pos3(-750.0, 0.0, 25.0);

	Route r1, r2, r3;

	r1.pos = pos1;
	r1.speed = 500.0;
	r2.pos = pos2;
	r2.speed = 19.0;
	r3.pos = pos3;
	r3.speed = 15.0;

	for(it = flights.begin(); it!=flights.end(); ++it)
	{
		if((*it)->getRoute()->empty())
		{
			(*it)->getRoute()->push_back(r3);
			(*it)->getRoute()->push_front(r2);
			(*it)->getRoute()->push_front(r1);

		}
	}

}
