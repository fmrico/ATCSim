/*
 * Airport.h
 *
 *  Created on: 17/07/2014
 *      Author: paco
 */

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include "Singleton.h"
#include "Flight.h"

#include <math.h>

#include <list>



class Airport: public Singleton<Airport> {
public:
	Airport();
	virtual ~Airport();

	void step();

	void NextFocus();

	Flight* getFocused(){return (*focus);};

	void draw();

	std::list<Flight*> getFlights() {return flights;};

private:
	void checkLandings();
	void checkCollisions();
	void checkCrashes();
	void generate_flight();

	std::list<Flight*>::iterator removeFlight(std::string id);

	std::list<Flight*> flights;
	std::list<Flight*>::iterator focus;

	struct timeval last_ts;
	Position final_pos;
	int sec;
	int points;
	int max_flights;
	long crono;
};

#endif /* AIRPORT_H_ */
