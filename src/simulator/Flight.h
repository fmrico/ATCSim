/*
 * Flight.h
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


#ifndef FLIGHT_H_
#define FLIGHT_H_
#include <string>
#include "Position.h"
#include "Common.h"
#include <list>

namespace atcsim{

typedef struct {
	Position pos;
	float speed;
} Route;

class Flight {
public:
	Flight(std::string _id, Position _pos, float _bearing, float _inclination, float _speed);
	virtual ~Flight();

	void update(float delta_t);
	void draw();


	std::list<Route> *getRoute() { return &route;};
	bool routed() { return !route.empty();};
	Position getPosition() { return pos;};
	float getInclination() { return inclination;};
	float getBearing() { return bearing;};
	float getInitBearing() { return init_bearing;};
	float getSpeed() { return speed;};
	void setSpeed(float tgt_speed) {speed = checkSpeedLimits(tgt_speed);}
	float getPoints() {return points;};
	std::string getId(){return id;};
	void setFocused(bool state) { focused = state;};
	bool getFocused() { return focused;};

	bool getInStorm() {return inStorm;};
	void setInStorm(bool in) {inStorm=in;};

private:
	std::string id;
	Position pos, last_pos;
	float init_bearing, bearing, inclination;
	float speed, w_speed;
	std::list<Route> route;
	bool focused;

	bool inStorm;

	float points;

	float checkSpeedLimits(float tgt_speed);
};

};  // namespace atcsim

#endif /* FLIGHT_H_ */
