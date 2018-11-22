
#ifndef SIMULATOR_WAYPOINT_H__
#define SIMULATOR_WAYPOINT_H__

#include <string>

class Waypoint {
public:
	//Waypoint();
	Waypoint(std::string name, float x, float y);
	~Waypoint();

    std::string getName() {return name_;};
	float getX() {return x_;};
	float getY() {return y_;};

    void setName(std::string name){name_ = name;};
	void setX(float x) {x_ = x;};
	void setY(float y) {y_ = y;};

private:
    std::string name_;
    float x_, y_;
};

#endif  // SIMULATOR_WAYPOINT_H__
