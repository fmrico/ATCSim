#ifndef CIRCUIT_ROUTE_H_
#define CIRCUIT_ROUTE_H_

#include <string>
#include <unordered_map>

#include "Position.h"

namespace atcsim{

static std::string pointsFileName = "../navdata/points.nav";
static std::string circuitsFileName = "../navdata/circuits.nav";

static std::unordered_map<std::string, Position> routePoints;

class CircuitRoute {
public:
	CircuitRoute();
	virtual ~CircuitRoute();

private:

};

void loadNavPoints();

Position getRoutePoint(std::string id);
std::unordered_map<std::string, Position> getRoutePoints();


}  // namespace atcsim

#endif /* CIRCUIT_ROUTE_H_ */
