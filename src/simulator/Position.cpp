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

namespace atcsim{

Position::Position() {

	name = "";
	x = y = 0.0;
	z = MAINTAIN_ALT;
}

Position::Position(float _x, float _y)
{
	name = "";
	x = _x;
	y = _y;
	z = MAINTAIN_ALT;
}

Position::Position(float _x, float _y, float _z)
{
	name = "";
	x = _x;
	y = _y;
	z = _z;
}

Position::Position(std::string _name, float _x, float _y)
{
	name = check_name(_name);
	x = _x;
	y = _y;
	z = MAINTAIN_ALT;
}

Position::Position(std::string _name, float _x, float _y, float _z)
{
	name = check_name(_name);
	x = _x;
	y = _y;
	z = _z;
}

Position::~Position() {

}

std::string Position::check_name(std::string name)
{
	ushort max_length = 5;
	std::string aux;
	// Limit name to 5 characters
	if(name.length() > max_length)
	{
		aux = name.substr(0, max_length);
	}
	// Fill name to 5 characters
	else if(name.length() < max_length)
	{
		aux = name.substr(0, name.length());
		for(int i=name.length(); i<max_length; i++)
		aux += "0";
	}
	else
	{
		aux = name;
	}

	return aux;
}

float
Position::distance(Position pos)
{
	return sqrtf( ( (x - pos.get_x()) * (x - pos.get_x()) ) +
			      ( (y - pos.get_y()) * (y - pos.get_y()) ) +
		       	  ( (z - pos.get_z()) * (z - pos.get_z()) ) );
}

float
Position::distanceXY(Position pos)
{
	return sqrtf( ((x-pos.get_x())*(x-pos.get_x())) + ((y-pos.get_y())*(y-pos.get_y())));
}

float
Position::distX_EjeBody(Position pos1, Position pos2)
{
	float betta = atan2f(pos1.get_y()-y, pos1.get_x()-x);

	return cos(betta)*(pos2.get_x()-pos1.get_x()) + sin(betta)*(pos2.get_y()-pos1.get_y());
}

float
Position::get_angle(Position pos1, Position pos2)
{
	float u1, u2, v1, v2;

	u1 = pos1.get_x()-x;
	u2 = pos1.get_y()-y;
	v1 = pos2.get_x()-pos1.get_x();
	v2 = pos2.get_y()-pos1.get_y();

	return acos((fabs(u1*v1+u2*v2)) / (sqrt(u1*u1+u2*u2)*sqrt(v1*v1+v2*v2)));
}

void
Position::angles(Position pos, float &bearing, float &inclination)
{
	float distxy;

	distxy = sqrtf( ((x-pos.get_x())*(x-pos.get_x())) + ((y-pos.get_y())*(y-pos.get_y())));

	bearing = atan2f(y-pos.get_y(), x-pos.get_x());
	inclination = atan2f(pos.get_z()-z, distxy);
}

}  // namespace atcsim
