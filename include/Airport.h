#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>

class Airport {
public:
    Airport();
    Airport(const std::string& code,
            const std::string& name,
            const std::string& city,
            const std::string& country,
            double latitude,
            double longitude);

    // it is the getter function  -- use to read the private data
    const std::string& getCode() const;
    const std::string& getName() const;
    const std::string& getCity() const;
    const std::string& getCountry() const;
    double getLatitude() const;
    double getLongitude() const;

private:
    std::string code_;
    std::string name_;
    std::string city_;
    std::string country_;
    double latitude_;
    double longitude_;
};

#endif
