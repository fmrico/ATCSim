/*
 * Flight.h
 *
 *  Created on: 15/07/2014
 *      Author: paco
 */

#include <string>

#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "Position.h"
#include "Common.h"
#include <list>

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
	void setFocused(bool state) { focused = state;};
	bool getFocused() { return focused;};
	Position getPosition() { return pos;};
	float getInclination() { return inclination;};
	float getBearing() { return bearing;};
	float getSpeed() { return speed;};
	float getPoints() {return points;};
	std::string getId(){return id;};

private:
	std::string id;
	Position pos, last_pos;
	float bearing, inclination;
	float speed;
	std::list<Route> route;
	bool focused;

	float points;
};

#endif /* FLIGHT_H_ */
