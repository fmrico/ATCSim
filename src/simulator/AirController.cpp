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
#include <stdlib.h>
#include <math.h>


#define MAX_X 18000
#define MIN_X -4000
#define MAX_Y 12000
#define MIN_Y -12000
#define XS { MAX_X, MAX_X, MIN_X, MIN_X }
#define YS { MIN_Y, MAX_Y, MAX_Y, MIN_Y } 


namespace atcsim {

	AirController::AirController() {
		// TODO Auto-generated constructor stub

	}

	AirController::~AirController() {
		// TODO Auto-generated destructor stub
	}

	int getNearNodo(Position pos) {
		int xs[4] = XS;
		int ys[4] = YS;
		int dist[4];
		int x = pos.get_x();
		int y = pos.get_y();
		for (int i = 0; i < 4; i++)
		{
			dist[i] = abs(xs[i] - x) + abs(ys[i] - y);
		}
		if (dist[0] < dist[1] && dist[0] < dist[2] && dist[0] < dist[3])
			return 0;
		if (dist[1] < dist[0] && dist[1] < dist[2] && dist[1] < dist[3])
			return 1;
		if (dist[2] < dist[1] && dist[2] < dist[0] && dist[2] < dist[3])
			return 2;
		if (dist[3] < dist[1] && dist[3] < dist[2] && dist[3] < dist[0])
			return 3;

	}

	void darRuta(Flight *vuelo)
	{
		int alturas[4];
		for (int i = 0, altura = 1000; i < 4; i++, altura += 1000)
			alturas[i] = altura;

		int xs[4] = XS;
		int ys[4] = YS;

		Route rutas[4];
		int z = vuelo->getPosition().get_z();
		int altura;
		if (z % 1000 == 0 && z / 1000 <= 4) altura = (z / 1000) - 1;
		else altura = rand() % 4;

		int nodo = getNearNodo(vuelo->getPosition());
		for (int i = 0; i < 4; i++)
		{
			rutas[i].pos = Position(xs[i], ys[i], alturas[altura]);
			rutas[i].speed = 500;
		}

		for (int i = 0; i < 4; i++, nodo = (nodo + 1) % 4)
			vuelo->getRoute()->push_back(rutas[nodo]);

	}

	void aterrizar(Flight *vuelo)
	{
		Position pos_aterrizaje(8000.0, 0.0, 800.0);
		Position pos_aterrizaje_0(3500.0, 0.0, 100.0);
		Position pos_aterrizaje_1(1500.0, 0.0, 50.0);
		Position pos_aterrizaje_2(200.0, 0.0, 25.0);
		Position pos_aterrizaje_3(-750.0, 0.0, 25.0);



		Route ra, ra0, ra1, ra2, ra3;

		ra.pos = pos_aterrizaje;
		ra.speed = 500.0;
		ra0.pos = pos_aterrizaje_0;
		ra0.speed = 500.0;
		ra1.pos = pos_aterrizaje_1;
		ra1.speed = 200.0;
		ra2.pos = pos_aterrizaje_2;
		ra2.speed = 75.0;
		ra3.pos = pos_aterrizaje_3;
		ra3.speed = 15.0;

		Route rutas_aterrizaje[5] = { ra, ra0, ra1, ra2, ra3 };

		Airport::getInstance()->book_landing();
		for (int i = 0; i < 5; i++)
			vuelo->getRoute()->push_back(rutas_aterrizaje[i]);

	}


	void
	AirController::doWork()
	{


		std::list<Flight*> flights = Airport::getInstance()->getFlights();
		std::list<Flight*>::iterator it;



		if (!Airport::getInstance()->is_booked_landing()) {
			Flight* primero = flights.front();
			primero->getRoute()->clear();     //limpia la ruta de vuelo
		}
		for (it = flights.begin(); it != flights.end(); ++it)
		{
			if ((*it)->getRoute()->empty())
			{
				if (Airport::getInstance()->is_booked_landing())
				{
					darRuta((*it));
				}
				else {
					aterrizar((*it));
				}
			}
		}

	}
}  // namespace atcsim
