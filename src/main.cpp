#include "algorithms/a_star.hpp"
#include "algorithms/dijkstra.hpp"
#include "map_creator.hpp"

int main()
{
  // std::vector<std::vector<int>> map = { { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 }, //
  //                                       { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 }, //
  //                                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, //
  //                                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
  //                                       { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, //
  //                                       { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, //
  //                                       { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, //
  //                                       { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 }, //
  //                                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //
  //                                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
  // Create a map
  unsigned int height = 50;   // Height of the grid
  unsigned int width = 50;    // Width of the grid
  unsigned int cellSize = 10; // Size of each cell in pixels

  MapCreator gridMap(height, width, cellSize);
  gridMap.run();

  std::vector<std::vector<int>> map = gridMap.getMap();
  Vertex start = { 0, 0, 0 };
  Vertex goal = { int(map[0].size() - 1), int(map.size() - 1), 0 };
  Dijkstra dijkstra("Dijkstra", map, goal, start, 1, cellSize);
  dijkstra.render();
  AStar astar("Astar", map, goal, start, 1, cellSize);
  astar.render();
  return 0;
}