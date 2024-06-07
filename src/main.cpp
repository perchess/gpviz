#include "dijkstra.hpp"
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
  unsigned int height = 10;   // Height of the grid
  unsigned int width = 30;    // Width of the grid
  unsigned int cellSize = 20; // Size of each cell in pixels

  MapCreator gridMap(height, width, cellSize);
  gridMap.run();
  gridMap.print();

  std::vector<std::vector<int>> map = gridMap.getMap();
  Vertex start = { 0, 0, 0 };
  Vertex goal = { int(map.size() - 1), int(map[0].size() - 1), 0 };
  Dijkstra dijkstra("Dijkstra", map, goal, start, 1, cellSize);
  dijkstra.render();
  return 0;
}