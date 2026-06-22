#include "AStarOptimizer.h"
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

// Helper structure for the A* Min-Heap Priority Queue
struct AStarNode {
    std::string airportCode;
    double estimatedCost; // f-score

    // We want a Min-Heap, so we use the > operator
    bool operator>(const AStarNode& other) const {
        return estimatedCost > other.estimatedCost;
    }
};

AStarOptimizer::AStarOptimizer() {
    // Empty constructor
}

PathResult AStarOptimizer::findShortestPath(const Graph& graph,
                                            const WeightCalculator& weightCalculator,
                                            const HaversineHelper& haversineHelper,
                                            const std::string& startAirportCode,
                                            const std::string& endAirportCode) {
    
    // Safety check: make sure both airports exist in our data
    if (!graph.hasAirport(startAirportCode) || !graph.hasAirport(endAirportCode)) {
        std::vector<std::string> emptyPath;
        return PathResult(false, emptyPath, 0.0, 0, "A-Star");
    }

    // Get the destination airport object so we know its latitude and longitude
    Airport endAirport;
    graph.getAirport(endAirportCode, endAirport);

    // Three notebooks, just like Dijkstra
    std::unordered_map<std::string, double> exactDistances;       // "g-score": exactly how far we have traveled
    std::unordered_map<std::string, double> estimatedTotalCosts;  // "f-score": exact distance + guessed distance to end
    std::unordered_map<std::string, std::string> previousNode;    // For walking backward at the end
    std::unordered_map<std::string, bool> visited;                // Airports we are done looking at
    
    // Create the Min-Heap Priority Queue for A*
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> pq;
    
    // Start at the beginning
    exactDistances[startAirportCode] = 0.0;
    
    // Guess the distance from the start directly to the end
    Airport startAirport;
    graph.getAirport(startAirportCode, startAirport);
    double initialGuess = haversineHelper.calculateDistance(startAirport, endAirport);
    estimatedTotalCosts[startAirportCode] = initialGuess;
    
    // Add start node to the Priority Queue
    pq.push({startAirportCode, initialGuess});
    
    int nodesVisitedCount = 0;
    
    // Main A* Loop
    while (!pq.empty()) {
        // Step 1: Get the airport with the smallest ESTIMATED total cost (f-score) from the Min-Heap
        AStarNode current = pq.top();
        pq.pop();
        
        std::string currentNode = current.airportCode;
        
        // If we reached our final destination, stop early! A* is very fast at this.
        if (currentNode == endAirportCode) {
            break;
        }
        
        // If we already visited this airport from a shorter path, skip it
        if (visited[currentNode]) {
            continue;
        }
        
        // Step 2: Mark current airport as visited
        visited[currentNode] = true;
        nodesVisitedCount++;
        
        // Step 3: Look at all flights leaving this airport
        std::vector<RouteEdge> routes = graph.getRoutes(currentNode);
        for (size_t i = 0; i < routes.size(); i++) {
            RouteEdge edge = routes[i];
            std::string neighborNodeCode = edge.getDestinationCode();
            
            // Exact distance calculation (same as Dijkstra)
            double edgeWeight = weightCalculator.calculateWeight(edge);
            double newExactDistance = exactDistances[currentNode] + edgeWeight;
            
            bool isNewAirport = (exactDistances.find(neighborNodeCode) == exactDistances.end());
            
            // If this is a new shorter way to the neighbor, save it!
            if (isNewAirport || newExactDistance < exactDistances[neighborNodeCode]) {
                
                // Save the new exact distance
                exactDistances[neighborNodeCode] = newExactDistance;
                previousNode[neighborNodeCode] = currentNode;
                
                // Now A* magic: add the exact distance + a straight-line guess to the end!
                Airport neighborAirport;
                graph.getAirport(neighborNodeCode, neighborAirport);
                double guessToEnd = haversineHelper.calculateDistance(neighborAirport, endAirport);
                
                double newEstimatedCost = newExactDistance + guessToEnd;
                estimatedTotalCosts[neighborNodeCode] = newEstimatedCost;
                
                // Add the neighbor to the Priority Queue with its new f-score
                pq.push({neighborNodeCode, newEstimatedCost});
            }
        }
    }
    
    // Step 4: Build the final path by walking backwards
    std::vector<std::string> path;
    
    if (exactDistances.find(endAirportCode) == exactDistances.end()) {
        return PathResult(false, path, 0.0, nodesVisitedCount, "A-Star");
    }
    
    std::string current = endAirportCode;
    while (current != "") {
        path.push_back(current);
        if (previousNode.find(current) != previousNode.end()) {
            current = previousNode[current];
        } else {
            current = "";
        }
    }
    
    std::reverse(path.begin(), path.end());
    double totalCost = exactDistances[endAirportCode]; // The true cost
    
    return PathResult(true, path, totalCost, nodesVisitedCount, "A-Star");
}
