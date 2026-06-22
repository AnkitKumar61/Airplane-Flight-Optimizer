#ifndef PATH_RESULT_H
#define PATH_RESULT_H

#include <string>
#include <vector>

class PathResult {
public:
    PathResult();
    PathResult(bool pathExists,
               const std::vector<std::string>& path,
               double totalCost,
               int visitedNodes,
               const std::string& algorithmName);

    bool hasPath() const;
    std::vector<std::string> getPath() const;
    double getTotalCost() const;
    int getVisitedNodes() const;
    std::string getAlgorithmName() const;
    int getStopCount() const;

private:
    bool pathFound;
    std::vector<std::string> airportPath;
    double finalCost;
    int nodesVisited;
    std::string usedAlgorithm;
};

#endif
