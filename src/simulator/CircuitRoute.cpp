#include "CircuitRoute.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace atcsim{

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
		std::cout << "Loaded " << count << " point(s) of route from file '"
					<< pointsFileName << "'" << std::endl;
		infile.close();
	}else{
		std::cerr << "Error opening file '" << pointsFileName << "'!" << std::endl;
	}

}

void loadNavCircuits(){

	//std::cout << "Loading external files of routes..." << std::endl;

	std::ifstream infile(circuitsFileName, std::ifstream::in);

	if(infile.is_open()){
		std::string name;

		uint count = 0;
		std::string lineRead, line, token;
		while(std::getline(infile, lineRead))
		{
			std::vector<Position> points;

			// Trim white-spaces
			for(int i=0; i<lineRead.length(); i++){
				if(lineRead[i] != ' '){
					line += lineRead[i];
				}
			}

			// Get name of route
			name = line.substr(0, line.find(':'));
			line = line.substr(line.find(':')+1, line.length()-1);

			std::cout << "\t·" << name << ": ";

			// Get points of route
			std::istringstream iss(line);
			while(std::getline(iss, token, ','))
			{
				std::cout << token << ",";
				points.push_back(getRoutePoint(token));
			}

			line.clear();
			std::cout << std::endl;

			routeCircuits.insert({name, points});
			count++;
		}//while
		std::cout << "Loaded " << count << " route(s) from file '"
					<< circuitsFileName << "'" << std::endl;
		infile.close();
	}else{
		std::cerr << "Error opening file '" << circuitsFileName << "'!" << std::endl;
	}

}


Position getRoutePoint(std::string id){

	Position pos;
	std::unordered_map<std::string, Position>::const_iterator it = routePoints.find(id);

	if ( it != routePoints.end() )	// if element exists
    	pos = it->second;

	return pos;
}

std::vector<Position> getRouteCircuit(std::string id){

	std::vector<Position> circ;
	std::unordered_map<std::string, std::vector<Position> >::const_iterator it = routeCircuits.find(id);

	if ( it != routeCircuits.end() )	// if element exists
    	circ = it->second;

	return circ;
}


std::unordered_map<std::string, Position> getRoutePoints(){
	return routePoints;
}

std::unordered_map<std::string, std::vector<Position> > getRouteCircuits(){
	return routeCircuits;
}


}  // namespace atcsim
