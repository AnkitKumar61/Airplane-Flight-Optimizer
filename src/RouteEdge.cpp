#include "RouteEdge.h"

RouteEdge::RouteEdge() {
    nextAirportCode = "";
    routeDistance = 0.0;
    routeDelayFactor = 0.0;
    weeklyFrequency = 0;
}

RouteEdge::RouteEdge(const std::string& destinationCode,
                     double distance,
                     double delayFactor,
                     int frequency) {
    nextAirportCode = destinationCode;
    routeDistance = distance;
    routeDelayFactor = delayFactor;
    weeklyFrequency = frequency;
}

std::string RouteEdge::getDestinationCode() const {
    return nextAirportCode;
}

double RouteEdge::getDistance() const {
    return routeDistance;
}

double RouteEdge::getDelayFactor() const {
    return routeDelayFactor;
}

int RouteEdge::getFrequency() const {
    return weeklyFrequency;
}
