#include "Graph.h"

Graph::Graph() {
    totalAirports = 0;
    totalRoutes = 0;
}

bool Graph::addAirport(const Airport& airport) {
    std::string airportCode = airport.getCode();

    if (hasAirport(airportCode))
        return false;

    airports[airportCode] = airport;
    adjacencyList[airportCode] = {};

    totalAirports++;

    return true;
}

bool Graph::addRoute(const std::string& sourceAirportCode, const RouteEdge& route) {
    std::string destinationAirportCode = route.getDestinationCode();

    if (!hasAirport(sourceAirportCode)) {
        return false;
    }

    if (!hasAirport(destinationAirportCode)) {
        return false;
    }

    adjacencyList[sourceAirportCode].push_back(route);
    totalRoutes++;

    return true;
}

bool Graph::hasAirport(const std::string& airportCode) const {
    if (airports.find(airportCode) != airports.end()) {
        return true;
    }

    return false;
}

bool Graph::getAirport(const std::string& airportCode,
                       Airport& airport) const {

    auto airportIterator = airports.find(airportCode);

    if (airportIterator == airports.end())
        return false;

    airport = airportIterator->second;

    return true;
}

std::vector<RouteEdge> Graph::getRoutes(
    const std::string& sourceAirportCode) const {

    auto routeIterator = adjacencyList.find(sourceAirportCode);

    if (routeIterator == adjacencyList.end()) {
        return {};
    }

    return routeIterator->second;
}

int Graph::getAirportCount() const {
    return totalAirports;
}

int Graph::getRouteCount() const {
    return totalRoutes;
}
