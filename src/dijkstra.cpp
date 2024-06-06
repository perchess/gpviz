#include "dijkstra.hpp"

std::vector<Vertex> Dijkstra::reconstructPath(std::unordered_map<int, Vertex>& came_from, Vertex& start, const Vertex& goal)
{
  std::vector<Vertex> path;
  Vertex current = goal;
  while (!(current == start))
  {
    path.push_back(current);
    current = came_from[current.x * grid_.size() + current.y];
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

std::vector<Vertex> Dijkstra::findPath(Vertex start, Vertex goal, sf::RenderWindow& window, std::vector<sf::RectangleShape>& grid)
{
  std::priority_queue<Vertex, std::vector<Vertex>, Compare> pq;
  std::unordered_map<int, Vertex> came_from;
  std::unordered_map<int, int> cost;

  pq.push(start);
  cost[start.x * grid_.size() + start.y] = 0;

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
      int new_cost = cost[current.x * grid_.size() + current.y] + next.weight;
      if (cost.find(next.x * grid_.size() + next.y) == cost.end() || new_cost < cost[next.x * grid_.size() + next.y])
      {
        cost[next.x * grid_.size() + next.y] = new_cost;
        next.weight = new_cost;
        pq.push(next);
        came_from[next.x * grid_.size() + next.y] = current;
      }
    }

    // Visualize the progress
    visualizeStep(current, start, goal);
  }

  return reconstructPath(came_from, start, goal);
}