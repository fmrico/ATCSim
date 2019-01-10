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

  for(it = flights.begin(); it!=flights.end(); ++it)
  {
    if((*it)->getRoute()->empty())
    {
      (*it)->getRoute()->push_back(r3);
      (*it)->getRoute()->push_front(r2);
      (*it)->getRoute()->push_front(r1);
      (*it)->getRoute()->push_front(r0);
		}
	}
}

}  // namespace atcsim
