#include "PathResult.h"

PathResult::PathResult() {
    pathFound = false;
    airportPath = std::vector<std::string>();
    finalCost = 0.0;
    nodesVisited = 0;
    usedAlgorithm = "";
}

PathResult::PathResult(bool pathExists,
                       const std::vector<std::string>& path,
                       double totalCost,
                       int visitedNodes,
                       const std::string& algorithmName) {
    pathFound = pathExists;
    airportPath = path;
    finalCost = totalCost;
    nodesVisited = visitedNodes;
    usedAlgorithm = algorithmName;
}

bool PathResult::hasPath() const {
    return pathFound;
}

std::vector<std::string> PathResult::getPath() const {
    return airportPath;
}

double PathResult::getTotalCost() const {
    return finalCost;
}

int PathResult::getVisitedNodes() const {
    return nodesVisited;
}

std::string PathResult::getAlgorithmName() const {
    return usedAlgorithm;
}

int PathResult::getStopCount() const {
    if (airportPath.empty() || airportPath.size() == 1) {
        return 0;
    }

    return static_cast<int>(airportPath.size()) - 1;
}
