#ifndef HAVERSINE_HELPER_H
#define HAVERSINE_HELPER_H

#include "Airport.h"

class HaversineHelper {
public:
    HaversineHelper(); // Simple constructor

    // Calculates the straight-line distance (in kilometers) between two airports
    // using their latitude and longitude.
    double calculateDistance(const Airport& airport1, const Airport& airport2) const;
};

#endif
