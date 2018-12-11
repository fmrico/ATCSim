#include "Waypoint.h"
#include <math.h>

Waypoint::Waypoint(){
	name_ = "";
	lat_ = lon_ = 0.0;
}

Waypoint::Waypoint(std::string name, float lat, float lon){
	name_ = name;
	lat_ = -lat;
	lon_ = lon;
}

Waypoint::Waypoint(const Waypoint& other){
	name_ = other.name_;
	lat_ = other.lat_;
	lon_ = other.lon_;
}

Waypoint::~Waypoint() {

}
