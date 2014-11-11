/*
 * Position.cpp
 *
 *  Created on: 15/07/2014
 *      Author: paco
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
