/*
 * Position.h
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

#ifndef POSITION_H_
#define POSITION_H_

class Position {
public:
	Position();
	Position(float _x, float _y, float _z);
	virtual ~Position();

	float get_x() {return x;};
	float get_y() {return y;};
	float get_z() {return z;};

	void set_x(float _x) {x = _x;};
	void set_y(float _y) {y = _y;};
	void set_z(float _z) {z = _z;};

	float distance(Position pos);
	void angles(Position pos, float &bearing, float &inclination);

private:
		float x, y, z;

};

#endif /* POSITION_H_ */
