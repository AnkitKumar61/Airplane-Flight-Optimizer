#ifndef DIJKSTRA_OPTIMIZER_H
#define DIJKSTRA_OPTIMIZER_H

#include <string>
#include "Graph.h"
#include "WeightCalculator.h"
#include "PathResult.h"

class DijkstraOptimizer {
public:
    DijkstraOptimizer(); // Simple constructor

    // Finds the best path from start to end using Dijkstra's Algorithm
    PathResult findShortestPath(const Graph& graph,
                                const WeightCalculator& weightCalculator,
                                const std::string& startAirport,
                                const std::string& endAirport);
};

#endif
