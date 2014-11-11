/*
 * Position.cpp
 *
 *  Created on: 15/07/2014
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

#include "Position.h"
#include <math.h>

Position::Position() {

	x = y = z = 0.0;

}

Position::Position(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Position::~Position() {

}

float
Position::distance(Position pos)
{
	return sqrtf( ( (x - pos.get_x()) * (x - pos.get_x()) ) +
			      ( (y - pos.get_y()) * (y - pos.get_y()) ) +
		       	  ( (z - pos.get_z()) * (z - pos.get_z()) ) );
}

void
Position::angles(Position pos, float &bearing, float &inclination)
{
	float distxy;

	distxy = sqrtf( ((x-pos.get_x())*(x-pos.get_x())) + ((y-pos.get_y())*(y-pos.get_y())));

	bearing = atan2f(y-pos.get_y(), x-pos.get_x());
	inclination = atan2f(pos.get_z()-z, distxy);
}
