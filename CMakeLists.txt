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
add_library(MapCreator src/map_creator.cpp)
add_executable(Pathfinding 
src/path_finder.cpp
src/algorithms/dijkstra.cpp
src/algorithms/a_star.cpp
src/main.cpp
)

# Link the SFML libraries
target_link_libraries(Pathfinding sfml-graphics sfml-window sfml-system MapCreator)
target_link_libraries(MapCreator sfml-graphics sfml-window sfml-system)
