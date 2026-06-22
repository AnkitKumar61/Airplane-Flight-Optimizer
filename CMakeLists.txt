cmake_minimum_required(VERSION 3.10)
project(FlightOptimizer VERSION 1.0)

# We are using C++17 as requested for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# List all of our C++ source code files
set(SOURCES
    src/main.cpp
    src/Airport.cpp
    src/RouteEdge.cpp
    src/Graph.cpp
    src/DataLoader.cpp
    src/WeightCalculator.cpp
    src/HaversineHelper.cpp
    src/PathResult.cpp
    src/DijkstraOptimizer.cpp
    src/AStarOptimizer.cpp
)

# Tell CMake to take those files and build an executable program called "FlightOptimizer"
add_executable(FlightOptimizer ${SOURCES})

# Tell CMake where to find all the header (.h) files
target_include_directories(FlightOptimizer PRIVATE include)
