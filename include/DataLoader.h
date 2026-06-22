#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <string>
#include <vector>

#include "Graph.h"

class DataLoader {
public:
    bool loadAirports(const std::string& fileName, Graph& graph);
    bool loadRoutes(const std::string& fileName, Graph& graph);

private:
    std::vector<std::string> splitLine(const std::string& line);
    bool convertToDouble(const std::string& text, double& number);
    bool convertToInt(const std::string& text, int& number);
};

#endif
