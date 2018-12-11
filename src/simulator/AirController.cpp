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

namespace atcsim{

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

			Position pos_circuito_0(8000.0, -6000, 500.0);
			Position pos_circuito_1(8000.0, 6000, 500.0);
			Position pos_circuito_2(5000.0, 6000, 500.0);
			Position pos_circuito_3(5000.0, -6000, 500.0);
			Position pos_aterrizaje_0(3500.0, 0.0, 100.0);
			Position pos_aterrizaje_1(1500.0, 0.0, 50.0);
			Position pos_aterrizaje_2(200.0, 0.0, 25.0);
			Position pos_aterrizaje_3(-750.0, 0.0, 25.0);

			Route ra0, ra1, ra2, ra3;
			Route rc0, rc1, rc2, rc3;

			ra0.pos = pos_aterrizaje_0;
			ra0.speed = 500.0;
			ra1.pos = pos_aterrizaje_1;
			ra1.speed = 100.0;
			ra2.pos = pos_aterrizaje_2;
			ra2.speed = 19.0;
			ra3.pos = pos_circuito_3;
			ra3.speed = 15.0;

			rc0.pos = pos_circuito_0;
			rc0.speed = 500.0;
			rc1.pos = pos_circuito_1;
			rc1.speed = 500.0;
			rc2.pos = pos_circuito_2;
			rc2.speed = 500.0;
			rc3.pos = pos_circuito_3;
			rc3.speed = 500.0;

			if (!Airport::getInstance()->is_booked_landing()) {
				Flight* primero = *(flights.begin());
				primero -> getRoute()->clear();     //limpia la ruta de vuelo
			}
			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getRoute()->empty())
				{
					if (Airport::getInstance()->is_booked_landing()) {
						(*it)->getRoute()->push_back(rc0);
						(*it)->getRoute()->push_front(rc1);
						(*it)->getRoute()->push_front(rc2);
						(*it)->getRoute()->push_front(rc3);
					}else{
						Airport::getInstance()->book_landing();
						(*it)->getRoute()->push_back(ra0);
						(*it)->getRoute()->push_front(ra1);
						(*it)->getRoute()->push_front(ra2);
						(*it)->getRoute()->push_front(ra3);
					}
				}
			}
		}
}
