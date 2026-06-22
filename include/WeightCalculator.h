#ifndef WEIGHT_CALCULATOR_H
#define WEIGHT_CALCULATOR_H

#include "RouteEdge.h"

class WeightCalculator {
public:
    // Constructor now takes user preferences
    WeightCalculator(double distPref, double delayPref);

    // Converts a route's distance, delay, and frequency into a single numeric cost.
    double calculateWeight(const RouteEdge& route) const;

private:
    double distancePreference;
    double delayPreference;
};

#endif
