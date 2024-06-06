cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PathfindingVisualization)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)

# Add the executable
add_executable(PathfindingVisualization src/graph_interactive.cpp)
add_executable(Pathfinding 
src/path_finder.cpp
src/dijkstra.cpp
src/main.cpp
)

# Link the SFML libraries
target_link_libraries(PathfindingVisualization sfml-graphics sfml-window sfml-system)
target_link_libraries(Pathfinding sfml-graphics sfml-window sfml-system)
