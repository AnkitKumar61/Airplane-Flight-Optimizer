#include "WeightCalculator.h"

WeightCalculator::WeightCalculator(double distPref, double delayPref) {
    // Save the user preferences into our class variables
    distancePreference = distPref;
    delayPreference = delayPref;
}

double WeightCalculator::calculateWeight(const RouteEdge& route) const {
    // 1. Get the raw attributes from the route
    double distance = route.getDistance();
    double delayFactor = route.getDelayFactor();
    int frequency = route.getFrequency();
    
    // 2. Calculate the penalty for low frequency
    double penalty = 0.0;
    if (frequency >= 10) {
        penalty = 0.0; // Frequent enough, no penalty
    } else {
        penalty = (10 - frequency) * 50.0; // Increase penalty for fewer flights
    }
    
    // 3. Combine them using the user's preferences
    double weight = (distance * distancePreference) + (delayFactor * delayPreference) + penalty;
    
    // 4. Ensure the weight is never negative.
    // Dijkstra's algorithm cannot handle negative edge weights, so this is a crucial safety check.
    if (weight < 0.0) {
        weight = 0.0;
    }
    
    return weight;
}
