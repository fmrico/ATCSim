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
#include <fstream>

namespace atcsim {

	AirController::AirController() {
		// TODO Auto-generated constructor stub

	}

	AirController::~AirController() {
		// TODO Auto-generated destructor stub
	}

	void crearRuta(Flight *fl)
	{
		int x = fl->getPosition().get_x();
		int y = fl->getPosition().get_y();
		int z = fl->getPosition().get_z();

		Route ruta[4];

		int este_oeste;
		if (y > 0) este_oeste = -1;
		else este_oeste = 1;

		Position p0((x + 200), (y + (200 * este_oeste)), z);
		Position p1(x, (y + (400 * este_oeste)), z);
		Position p2((x - 200), (y + (200 * este_oeste)), z);
		Position p3(x, y, z);
		Position posiciones[4] = { p0,p1,p2,p3 };
		for (int i = 0; i < 4; i++)
		{
			ruta[i].pos = posiciones[i];
			ruta[i].speed = 20;
			fl->getRoute()->push_back(ruta[i]);
		}
	}


	void
	AirController::doWork()
	{
		std::list<Flight*> flights = Airport::getInstance()->getFlights();
		std::list<Flight*>::iterator it;

		Position pos_aterrizaje_0(3500.0, 0.0, 100.0);
		Position pos_aterrizaje_1(1500.0, 0.0, 50.0);
		Position pos_aterrizaje_2(200.0, 0.0, 25.0);
		Position pos_aterrizaje_3(-750.0, 0.0, 25.0);

		Route ra0, ra1, ra2, ra3;

		ra0.pos = pos_aterrizaje_0;
		ra0.speed = 500.0;
		ra1.pos = pos_aterrizaje_1;
		ra1.speed = 200.0;
		ra2.pos = pos_aterrizaje_2;
		ra2.speed = 50.0;
		ra3.pos = pos_aterrizaje_3;
		ra3.speed = 15.0;


		if (!Airport::getInstance()->is_booked_landing()) {
			Flight* primero = flights.front();
			primero->getRoute()->clear();     //limpia la ruta de vuelo
		}
		for (it = flights.begin(); it != flights.end(); ++it)
		{
			if ((*it)->getRoute()->empty())
			{
				if (Airport::getInstance()->is_booked_landing()) {
					crearRuta((*it));
				}
				else {
					Airport::getInstance()->book_landing();
					(*it)->getRoute()->push_back(ra0);
					(*it)->getRoute()->push_back(ra1);
					(*it)->getRoute()->push_back(ra2);
					(*it)->getRoute()->push_back(ra3);
				}
			}
		}
	}
}  // namespace atcsim
