#include "HaversineHelper.h"
#include <cmath>

HaversineHelper::HaversineHelper() {
    // Empty constructor
}

double HaversineHelper::calculateDistance(const Airport& airport1, const Airport& airport2) const {
    // Math constant for Pi
    double PI = 3.14159265358979323846;
    
    // Earth's radius in kilometers
    double earthRadiusKm = 6371.0; 

    // Convert latitude and longitude from degrees to radians
    double lat1Rad = airport1.getLatitude() * (PI / 180.0);
    double lon1Rad = airport1.getLongitude() * (PI / 180.0);
    double lat2Rad = airport2.getLatitude() * (PI / 180.0);
    double lon2Rad = airport2.getLongitude() * (PI / 180.0);

    // Haversine formula math steps
    double diffLat = lat2Rad - lat1Rad;
    double diffLon = lon2Rad - lon1Rad;

    double a = std::sin(diffLat / 2.0) * std::sin(diffLat / 2.0) +
               std::cos(lat1Rad) * std::cos(lat2Rad) *
               std::sin(diffLon / 2.0) * std::sin(diffLon / 2.0);

    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    // Final straight-line distance
    return earthRadiusKm * c;
}
