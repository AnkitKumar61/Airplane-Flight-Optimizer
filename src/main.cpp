#include <iostream>
#include <string>
#include <vector>
#include <chrono> // Added for execution timing

#include "../include/Graph.h"
#include "../include/DataLoader.h"
#include "../include/WeightCalculator.h"
#include "../include/HaversineHelper.h"
#include "../include/DijkstraOptimizer.h"
#include "../include/AStarOptimizer.h"
#include "../include/PathResult.h"

// Helper function to safely print a PathResult formatted as JSON, including coordinates and execution time
void printPathJSON(const PathResult& result, const Graph& graph, double timeMs) {
    std::cout << "  \"found\": " << (result.hasPath() ? "true" : "false") << "," << std::endl;
    std::cout << "  \"cost\": " << result.getTotalCost() << "," << std::endl;
    std::cout << "  \"visited\": " << result.getVisitedNodes() << "," << std::endl;
    std::cout << "  \"timeMs\": " << timeMs << "," << std::endl;
    std::cout << "  \"path\": [";
    
    std::vector<std::string> path = result.getPath();
    for (size_t i = 0; i < path.size(); i++) {
        std::string code = path[i];
        Airport a;
        if (graph.getAirport(code, a)) {
            std::cout << "{\"code\": \"" << code << "\", \"lat\": " << a.getLatitude() << ", \"lng\": " << a.getLongitude() << "}";
        } else {
            std::cout << "{\"code\": \"" << code << "\", \"lat\": 0, \"lng\": 0}";
        }
        
        if (i < path.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main(int argc, char* argv[]) {
    bool jsonMode = false;
    std::string startAirport = "JFK"; // Default
    std::string endAirport = "LAX";   // Default

    if (argc >= 3) {
        jsonMode = true;
        startAirport = argv[1];
        endAirport = argv[2];
    }

    Graph flightNetwork;
    DataLoader loader;
    
    bool airportsLoaded = loader.loadAirports("data/airports.csv", flightNetwork);
    if (!airportsLoaded) airportsLoaded = loader.loadAirports("../data/airports.csv", flightNetwork);
    
    bool routesLoaded = loader.loadRoutes("data/routes.csv", flightNetwork);
    if (!routesLoaded) routesLoaded = loader.loadRoutes("../data/routes.csv", flightNetwork);

    if (!jsonMode) {
        std::cout << "--- Welcome to the Airplane Flight Optimizer ---" << std::endl;
        std::cout << "Success! Loaded airports and routes." << std::endl;
        std::cout << "------------------------------------------------\n" << std::endl;
    }

    WeightCalculator weightCalc(1.0, 1.0);
    HaversineHelper haversine;
    DijkstraOptimizer dijkstra;
    AStarOptimizer astar;

    // Time Dijkstra
    auto startDijkstra = std::chrono::high_resolution_clock::now();
    PathResult dijkstraResult = dijkstra.findShortestPath(flightNetwork, weightCalc, startAirport, endAirport);
    auto endDijkstra = std::chrono::high_resolution_clock::now();
    double dijkstraTimeMs = std::chrono::duration<double, std::milli>(endDijkstra - startDijkstra).count();

    // Time A*
    auto startAstar = std::chrono::high_resolution_clock::now();
    PathResult astarResult = astar.findShortestPath(flightNetwork, weightCalc, haversine, startAirport, endAirport);
    auto endAstar = std::chrono::high_resolution_clock::now();
    double astarTimeMs = std::chrono::duration<double, std::milli>(endAstar - startAstar).count();

    if (jsonMode) {
        std::cout << "{" << std::endl;
        std::cout << "\"dijkstra\": {" << std::endl;
        printPathJSON(dijkstraResult, flightNetwork, dijkstraTimeMs);
        std::cout << "}," << std::endl;
        std::cout << "\"astar\": {" << std::endl;
        printPathJSON(astarResult, flightNetwork, astarTimeMs);
        std::cout << "}" << std::endl;
        std::cout << "}" << std::endl;
    } else {
        std::cout << "Finding shortest path from " << startAirport << " to " << endAirport << "...\n" << std::endl;

        std::cout << "[ Running Dijkstra's Algorithm ]" << std::endl;
        if (dijkstraResult.hasPath()) {
            std::cout << "Path found! Cost: " << dijkstraResult.getTotalCost() << std::endl;
            std::cout << "Airports visited (loops): " << dijkstraResult.getVisitedNodes() << std::endl;
            std::cout << "Execution time: " << dijkstraTimeMs << " ms" << std::endl;
        } else {
            std::cout << "No path found!" << std::endl;
        }
        std::cout << std::endl;

        std::cout << "[ Running A* (A-Star) Algorithm ]" << std::endl;
        if (astarResult.hasPath()) {
            std::cout << "Path found! Cost: " << astarResult.getTotalCost() << std::endl;
            std::cout << "Airports visited (loops): " << astarResult.getVisitedNodes() << std::endl;
            std::cout << "Execution time: " << astarTimeMs << " ms" << std::endl;
        } else {
            std::cout << "No path found!" << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
