/*
 * Position.h
 *
 *  Created on: 15/07/2014
 *      Author: paco
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
