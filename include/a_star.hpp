#include "path_finder.hpp"
#include <queue>
#include <unordered_map>

class AStar : public PathFinder
{
public:
  using PathFinder::PathFinder; // Inherit constructors from Base

private:
  std::vector<Vertex> reconstructPath(std::unordered_map<int, Vertex>& came_from, Vertex& start, const Vertex& goal);

  std::vector<Vertex> findPath(Vertex start, Vertex goal, std::vector<Vertex>& visited) override;
};