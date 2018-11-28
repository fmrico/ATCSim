
#ifndef SIMULATOR_WAYPOINT_H__
#define SIMULATOR_WAYPOINT_H__

#include <string>

class Waypoint {
public:
	Waypoint();
	Waypoint(std::string name, float lat, float lon);
	Waypoint(const Waypoint& other);
	~Waypoint();

    std::string getName() {return name_;};
	float getLat() {return lat_;};
	float getLon() {return lon_;};

    void setName(std::string name){name_ = name;};
	void setLat(float lat) {lat_ = lat;};
	void setLon(float lon) {lon_ = lon;};

private:
    std::string name_;
    float lat_, lon_;
};

#endif  // SIMULATOR_WAYPOINT_H__
