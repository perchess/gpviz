#include "dijkstra.hpp"

int main()
{
  std::vector<std::vector<int>> map = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
                                        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }, { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },
                                        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
  Vertex start = { 0, 0, 0 };
  Vertex goal = { int(map.size() - 1), int(map[0].size() - 1), 0 };
  Dijkstra dijkstra("Dijkstra", map, goal, start);
  dijkstra.render();
  return 0;
}