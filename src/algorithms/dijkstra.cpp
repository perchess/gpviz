#include "algorithms/dijkstra.hpp"

std::vector<Vertex> Dijkstra::reconstructPath(std::unordered_map<int, Vertex>& came_from, Vertex& start, const Vertex& goal)
{
  std::vector<Vertex> path;
  Vertex current = goal;
  while (!(current == start))
  {
    path.push_back(current);
    current = came_from[current.y * grid_shape_.first + current.x];
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

std::vector<Vertex> Dijkstra::findPath(Vertex start, Vertex goal, std::vector<Vertex>& visited)
{
  std::priority_queue<Vertex, std::vector<Vertex>, Compare> pq;
  std::unordered_map<int, Vertex> came_from;
  std::unordered_map<int, int> cost;

  pq.push(start);
  cost[start.y * grid_shape_.first + start.x] = 0;

  while (!pq.empty())
  {
    Vertex current = pq.top();
    pq.pop();

    if (current == goal)
    {
      break;
    }
    for (Vertex next : getNeighbors(current))
    {
      int new_cost = cost[current.y * grid_shape_.first + current.x] + next.weight;
      if (cost.find(next.y * grid_shape_.first + next.x) == cost.end() || new_cost < cost[next.y * grid_shape_.first + next.x])
      {
        cost[next.y * grid_shape_.first + next.x] = new_cost;
        next.weight = new_cost;
        pq.push(next);
        came_from[next.y * grid_shape_.first + next.x] = current;
      }
    }

    visited.push_back(current);
  }

  return reconstructPath(came_from, start, goal);
}