#ifndef ROUTE_EDGE_H
#define ROUTE_EDGE_H

#include <string>

class RouteEdge {
public:
    RouteEdge();
    RouteEdge(const std::string& destinationCode,
              double distance,
              double delayFactor,
              int frequency);

    std::string getDestinationCode() const;
    double getDistance() const;
    double getDelayFactor() const;
    int getFrequency() const;

private:
    std::string nextAirportCode;
    double routeDistance;
    double routeDelayFactor;
    int weeklyFrequency;
};

#endif
