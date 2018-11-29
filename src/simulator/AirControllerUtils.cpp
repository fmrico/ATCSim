
#include <iostream>
#include "AirControllerUtils.h"

void atc_utils::createWaypoints(){
    //TODO: read from file
    Waypoint *wpt1 = new Waypoint("TOBEK", -2000, 0);
    Waypoint *wpt2 = new Waypoint("ASBIN", -5000, 2000);
    atc_utils::waypoints.push_back(wpt1);
    atc_utils::waypoints.push_back(wpt2);
}

std::list<Waypoint*> atc_utils::getWaypoints(){
    return atc_utils::waypoints;
}

void atc_utils::setWaypoints(){
	// Get loaded Waypoints
	//std::list<Waypoint*> waypoints = Airport::getInstance()->getWaypoints();
    std::list<Waypoint*> waypoints = atc_utils::getWaypoints();
	std::list<Waypoint*>::iterator it_wpt;

	// Save it into a map in order to retrieve it by ID
	for(it_wpt = waypoints.begin(); it_wpt!=waypoints.end(); ++it_wpt){
		wpt_map.insert( std::pair<std::string, Waypoint>( (*it_wpt)->getName(), *(*it_wpt) ) );
	}
}

Waypoint atc_utils::getWaypoint(std::string id){
	std::unordered_map<std::string, Waypoint>::iterator wpt_map_it;
	wpt_map_it = wpt_map.find(id);

	if(wpt_map_it != wpt_map.end()){		// Check if iterator is valid
		return wpt_map_it->second;
	}else{
		//std::cerr << "ERROR: Waypoint not exists!" << std::endl;
		return Waypoint();	// return empty Waypoint
	}

}
