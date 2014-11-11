/*
 * Airport.h
 *
 *  Created on: 17/07/2014
 *      Author: fmartin
 *
 *      Copyright 2014 Francisco Martín
 *
 *  This file is part of ATCSim.
 *
 *  ATCSim is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ATCSim is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ATCSim.  If not, see <http://www.gnu.org/licenses/>.
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
	void draw();
    

    void NextFocus();
    
	std::list<Flight*> getFlights() {return flights;};
    Flight* getFocused(){return (*focus);};
    void UpdateSimTime(float inc);

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
    float SimTimeMod;
};

#endif /* AIRPORT_H_ */
