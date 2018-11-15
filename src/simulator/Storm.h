/*
 * Storm.h
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
#include <string>

#ifndef TORMENTA_H__
#define TORMENTA_H__

#include "Position.h"
#include "Common.h"

class Storm {
public:
	Storm(Position _pos, float _bearing, float _speed, float _radious, float _height);
	virtual ~Storm();

	void update(float delta_t);
	void draw();


	Position getPosition() { return pos;};
	float getBearing() { return bearing;};
	float getSpeed() { return speed;};
	float getRadious() { return radious;};
	float getHeight() { return height;};

private:
	Position pos, last_pos;
	float bearing;
	float radious, height;
	float speed;
};

#endif  //  TORMENTA_H__
