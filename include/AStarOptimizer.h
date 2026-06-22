#ifndef ASTAR_OPTIMIZER_H
#define ASTAR_OPTIMIZER_H

#include <string>
#include "Graph.h"
#include "WeightCalculator.h"
#include "HaversineHelper.h"
#include "PathResult.h"

class AStarOptimizer {
public:
    AStarOptimizer(); // Simple constructor

    // Finds the best path from start to end using the A* (A-Star) Algorithm
    PathResult findShortestPath(const Graph& graph,
                                const WeightCalculator& weightCalculator,
                                const HaversineHelper& haversineHelper,
                                const std::string& startAirportCode,
                                const std::string& endAirportCode);
};

#endif
