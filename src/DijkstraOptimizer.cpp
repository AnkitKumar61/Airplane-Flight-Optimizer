#include "DijkstraOptimizer.h"
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <queue>

// Helper structure for the Min-Heap Priority Queue
struct QueueNode {
    std::string airportCode;
    double distance;

    // We want a Min-Heap, so we use the > operator
    // The Priority Queue keeps the smallest distance at the top
    bool operator>(const QueueNode& other) const {
        return distance > other.distance;
    }
};

DijkstraOptimizer::DijkstraOptimizer() {
    // Empty constructor
}

PathResult DijkstraOptimizer::findShortestPath(const Graph& graph,
                                               const WeightCalculator& weightCalculator,
                                               const std::string& startAirport,
                                               const std::string& endAirport) {
    
    // Safety check: if start or end airport is not in our data, we can't fly there
    if (!graph.hasAirport(startAirport) || !graph.hasAirport(endAirport)) {
        std::vector<std::string> emptyPath;
        return PathResult(false, emptyPath, 0.0, 0, "Dijkstra");
    }

    // These maps will store our progress
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> previousNode;
    std::unordered_map<std::string, bool> visited;
    
    // Create the Min-Heap Priority Queue
    std::priority_queue<QueueNode, std::vector<QueueNode>, std::greater<QueueNode>> pq;
    
    // We start at the beginning, so the distance to the start is 0
    distances[startAirport] = 0.0;
    pq.push({startAirport, 0.0});
    
    int nodesVisitedCount = 0;
    
    // The main loop for Dijkstra's Algorithm
    while (!pq.empty()) {
        // Step 1: Get the closest unvisited airport from the top of the Min-Heap
        QueueNode current = pq.top();
        pq.pop();
        
        std::string currentNode = current.airportCode;
        double currentDist = current.distance;
        
        // If we reached our final destination airport, we can stop early to save time!
        if (currentNode == endAirport) {
            break;
        }
        
        // If we already found a shorter path to this node and visited it, skip it
        if (visited[currentNode]) {
            continue;
        }
        
        // Step 2: Mark this airport as visited so we don't check it again
        visited[currentNode] = true;
        nodesVisitedCount++;
        
        // Step 3: Look at all flights leaving from this current airport
        std::vector<RouteEdge> routes = graph.getRoutes(currentNode);
        for (size_t i = 0; i < routes.size(); i++) {
            RouteEdge edge = routes[i];
            std::string neighborNode = edge.getDestinationCode();
            
            // Ask WeightCalculator how "hard" this flight is
            double edgeWeight = weightCalculator.calculateWeight(edge);
            
            // Total distance to the neighbor is: distance to current airport + weight of this flight
            double newDistance = distances[currentNode] + edgeWeight;
            
            // Check if we have never seen this neighbor before
            bool isNewAirport = (distances.find(neighborNode) == distances.end());
            
            // If it is new, OR if we found a better (shorter) way to get there, update it!
            if (isNewAirport || newDistance < distances[neighborNode]) {
                distances[neighborNode] = newDistance;
                previousNode[neighborNode] = currentNode; // Remember how we got here
                
                // Add the neighbor to the Priority Queue with its new, shorter distance
                pq.push({neighborNode, newDistance});
            }
        }
    }
    
    // Step 4: Build the final path by walking backwards from the end airport
    std::vector<std::string> path;
    
    // If the end airport has no distance recorded, it means we never reached it
    if (distances.find(endAirport) == distances.end()) {
        return PathResult(false, path, 0.0, nodesVisitedCount, "Dijkstra");
    }
    
    // Walk backwards using the "previousNode" map
    std::string current = endAirport;
    while (current != "") {
        path.push_back(current);
        
        // Try to go to the previous airport
        if (previousNode.find(current) != previousNode.end()) {
            current = previousNode[current];
        } else {
            current = ""; // Stop when we reach the start airport
        }
    }
    
    // The path is currently backwards (End -> Start). We need to flip it.
    std::reverse(path.begin(), path.end());
    
    // Get the total final cost
    double totalCost = distances[endAirport];
    
    return PathResult(true, path, totalCost, nodesVisitedCount, "Dijkstra");
}
