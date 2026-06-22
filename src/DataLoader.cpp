#include "DataLoader.h"

#include <fstream>
#include <sstream>

bool DataLoader::loadAirports(const std::string& fileName, Graph& graph) {
    std::ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::vector<std::string> fields = splitLine(line);

        if (fields.size() != 6) {
            continue;
        }

        double latitude = 0.0;
        double longitude = 0.0;

        if (!convertToDouble(fields[4], latitude)) {
            continue;
        }

        if (!convertToDouble(fields[5], longitude)) {
            continue;
        }

        Airport airport(fields[0], fields[1], fields[2], fields[3], latitude, longitude);
        graph.addAirport(airport);
    }

    file.close();
    return true;
}

bool DataLoader::loadRoutes(const std::string& fileName, Graph& graph) {
    std::ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::vector<std::string> fields = splitLine(line);

        if (fields.size() != 5) {
            continue;
        }

        double distance = 0.0;
        double delayFactor = 0.0;
        int frequency = 0;

        if (!convertToDouble(fields[2], distance)) {
            continue;
        }

        if (!convertToDouble(fields[3], delayFactor)) {
            continue;
        }

        if (!convertToInt(fields[4], frequency)) {
            continue;
        }

        RouteEdge route(fields[1], distance, delayFactor, frequency);
        graph.addRoute(fields[0], route);
    }

    file.close();
    return true;
}

std::vector<std::string> DataLoader::splitLine(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream lineStream(line);
    std::string field;

    while (std::getline(lineStream, field, ',')) {
        fields.push_back(field);
    }

    return fields;
}

bool DataLoader::convertToDouble(const std::string& text, double& number) {
    std::stringstream numberStream(text);
    numberStream >> number;

    if (numberStream.fail()) {
        return false;
    }

    return true;
}

bool DataLoader::convertToInt(const std::string& text, int& number) {
    std::stringstream numberStream(text);
    numberStream >> number;

    if (numberStream.fail()) {
        return false;
    }

    return true;
}
