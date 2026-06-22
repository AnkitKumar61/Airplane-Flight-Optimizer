#include "Airport.h"

Airport::Airport() {
    code_ = "";
    name_ = "";
    city_ = "";
    country_ = "";
    latitude_ = 0.0;
    longitude_ = 0.0;
}

Airport::Airport(const std::string& code,
                 const std::string& name,
                 const std::string& city,
                 const std::string& country,
                 double latitude,
                 double longitude) {
    code_ = code;
    name_ = name;
    city_ = city;
    country_ = country;
    latitude_ = latitude;
    longitude_ = longitude;
}

const std::string& Airport::getCode() const {
    return code_;
}

const std::string& Airport::getName() const {
    return name_;
}

const std::string& Airport::getCity() const {
    return city_;
}

const std::string& Airport::getCountry() const {
    return country_;
}

double Airport::getLatitude() const {
    return latitude_;
}

double Airport::getLongitude() const {
    return longitude_;
}
