/*
 * AirController.cpp
 *
 *  Created on: 21/07/2014
 *      Author: paco
 *
 *  Copyright 2014 Francisco Martín
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

#include "AirController.h"
#include "Airport.h"
#include "Flight.h"
#include "Position.h"
#include <list>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <exception>

static std::unordered_map<std::string, Waypoint> wpt_map;

AirController::AirController() {
	setWaypoints();
}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}


static void setWaypoints(){
	// Get loaded Waypoints
	std::list<Waypoint*> waypoints = Airport::getInstance()->getWaypoints();
	std::list<Waypoint*>::iterator it_wpt;

	// Save it into a map in order to retrieve it by ID
	for(it_wpt = waypoints.begin(); it_wpt!=waypoints.end(); ++it_wpt){
		wpt_map.insert( std::pair<std::string, Waypoint>( (*it_wpt)->getName(), *(*it_wpt) ) );
	}
}

static Waypoint getWaypoint(std::string id){
	std::unordered_map<std::string, Waypoint>::iterator wpt_map_it;
	wpt_map_it = wpt_map.find(id);

	if(wpt_map_it != wpt_map.end()){		// Check if iterator is valid
		return wpt_map_it->second;
	}else{
		std::cerr << "ERROR: Waypoint not exists!" << std::endl;
		return Waypoint();	// return empty Waypoint
	}

}


void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;

/*
			Position pos0(3500.0, 0.0, 100.0);
			Position pos1(1500.0, 0.0, 50.0);
			Position pos2(200.0, 0.0, 25.0);
			Position pos3(-750.0, 0.0, 25.0);

			Route r0, r1, r2, r3;

			r0.pos = pos0;
			r0.speed = 500.0;
			r1.pos = pos1;
			r1.speed = 100.0;
			r2.pos = pos2;
			r2.speed = 19.0;
			r3.pos = pos3;
			r3.speed = 15.0;
			*/

			Route r3, r2, r1;

			r2.wpt = getWaypoint("ASBIN");
			r2.speed = 200;
			r2.alt = 500;
			r3.wpt = getWaypoint("TOBEK");
			r3.speed = 250;
			r3.alt = 200;
			Position pos3(750.0, 0.0, 200.0);
			r3.pos = pos3;
			r3.speed = 100.0;

			Position pos1(0.0, 0.0, 25.0);
			r1.pos = pos1;
			r1.speed = 15.0;

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getRoute()->empty())
				{
					(*it)->getRoute()->push_back(r2);
					(*it)->getRoute()->push_back(r3);
					(*it)->getRoute()->push_back(r1);
					//(*it)->getRoute()->push_front(r0);
				}
			}

}
