#ifndef CIRCUIT_ROUTE_H_
#define CIRCUIT_ROUTE_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "Position.h"

namespace atcsim{

static std::string pointsFileName = "../navdata/points.nav";
static std::string circuitsFileName = "../navdata/circuits.nav";

static std::unordered_map<std::string, Position> routePoints;
static std::unordered_map<std::string, std::vector<Position> > routeCircuits;


int loadNavPoints();
int loadNavCircuits();

Position getRoutePoint(std::string id);
std::vector<Position> getRouteCircuit(std::string id);

std::unordered_map<std::string, Position> getRoutePoints();
std::unordered_map<std::string, std::vector<Position> > getRouteCircuits();


}  // namespace atcsim

#endif /* CIRCUIT_ROUTE_H_ */
