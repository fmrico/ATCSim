#ifndef SIMULATOR_AIR_CONTROLLER_UTILS_H__
#define SIMULATOR_AIR_CONTROLLER_UTILS_H__

#include "Waypoint.h"

#include <string>
#include <list>
#include <unordered_map>

namespace atc_utils{

    static std::list<Waypoint*> waypoints;
    static std::unordered_map<std::string, Waypoint> wpt_map;

    void createWaypoints();
    std::list<Waypoint*> getWaypoints();

    void setWaypoints();
    Waypoint getWaypoint(std::string id);

};

#endif // SIMULATOR_AIR_CONTROLLER_UTILS_H__
