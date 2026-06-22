#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Airport.h"
#include "RouteEdge.h"

class Graph {
public:
    Graph();

    bool addAirport(const Airport& airport);
    bool addRoute(const std::string& sourceAirportCode, const RouteEdge& route);
    bool hasAirport(const std::string& airportCode) const;
    bool getAirport(const std::string& airportCode, Airport& airport) const;
    std::vector<RouteEdge> getRoutes(const std::string& sourceAirportCode) const;
    int getAirportCount() const;
    int getRouteCount() const;

private:
    std::unordered_map<std::string, Airport> airports;
    std::unordered_map<std::string, std::vector<RouteEdge> > adjacencyList;
    int totalAirports;
    int totalRoutes;
};

#endif
