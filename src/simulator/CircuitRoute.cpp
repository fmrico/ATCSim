#include "CircuitRoute.h"

#include <iostream>
#include <fstream>

namespace atcsim{

CircuitRoute::CircuitRoute() {

}

CircuitRoute::~CircuitRoute() {

}

void loadNavPoints(){

	//std::cout << "Loading external files of points of route..." << std::endl;

	std::ifstream infile(pointsFileName, std::ifstream::in);

	if(infile.is_open()){
		float x, y, z;
		std::string name;
		uint count = 0;
		while(infile >> name >> x >> y >> z)
		{
			//std::cout << "\t-Position(" << name << ", " << x << ", " << y << ", " << z << ")" << std::endl;
			routePoints.insert({name, Position(name, x, y, z)});
			count++;
		}//while
		std::cout << "Loaded " << count << " points of route from '"
					<< pointsFileName << "'" << std::endl;
		infile.close();
	}else{
		std::cerr << "Error opening file '" << pointsFileName << "'!" << std::endl;
	}

}

/*
static std::unordered_map<std::string, Position> getRoutePoints(){
	return routePoints;
}
*/

}  // namespace atcsim
