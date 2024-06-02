cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PathfindingVisualization)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(PathfindingVisualization graph_interactive.cpp)

# Link the SFML libraries
target_link_libraries(PathfindingVisualization sfml-graphics sfml-window sfml-system)
