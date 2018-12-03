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

#ifndef SIMULATOR_AIRPORT_H__
#define SIMULATOR_AIRPORT_H__

#include "Singleton.h"
#include "Flight.h"
#include "Storm.h"
#include "ATCDisplay.h"
#include <math.h>

#include <list>



class Airport: public Singleton<Airport>, public ATCDisplay::AirportInterface
{
public:
	Airport();
	virtual ~Airport();

	void step();
	//void draw();

    void NextFocus();

	std::list<Flight*> getFlights() {return flights;};
	Storm* getStorm() {return storm;};
    Flight* getFocused(){return (*focus);};
    void UpdateSimTime(float inc);

	virtual ATCDisplay::ATCDFlights getFlights(const Ice::Current&);
	virtual ATCDisplay::ATCDStorm getStorm(const Ice::Current&);
	virtual ATCDisplay::ATCDAirport getAirportInfo(const Ice::Current&);
	virtual void UpdateSimT(float inc, const Ice::Current&);
	virtual void NextFocus(const Ice::Current&);
	virtual float getSimT(const Ice::Current&);
	virtual int getMaxFlights(const Ice::Current&);
	virtual int getPoints(const Ice::Current&);

  void book_landing() {any_landing_ = true;}
  bool is_booked_landing() { return any_landing_;}

private:

	void checkLandings();
	void checkCollisions();
	void checkCrashes();
	void checkFinishStorm();
	void generate_flight();
	void generate_storm();
	void checkFlightsInStorm();

	std::list<Flight*>::iterator removeFlight(std::string id);

	std::list<Flight*> flights;
	std::list<Flight*>::iterator focus;

	Storm *storm;


	struct timeval last_ts;
	Position final_pos;
	int sec;
	int points;
	int max_flights;
	long crono;
    float SimTimeMod;

    pthread_mutex_t mutex;

	float acum_; 

  bool any_landing_;

};

#endif  // SIMULATOR_AIRPORT_H__
