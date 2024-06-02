#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <thread>
#include <unordered_map>
#include <vector>

const int GRID_SIZE = 10;
const int CELL_SIZE = 20;
const int WIDTH = GRID_SIZE * CELL_SIZE;
const int HEIGHT = GRID_SIZE * CELL_SIZE;
const int DELAY_MS = 100;

struct Vertex
{
  int x, y, weight;
  bool operator>(const Vertex& other) const { return weight > other.weight; }
  bool operator==(const Vertex& other) const { return x == other.x && y == other.y; }
};

struct Compare
{
  bool operator()(const Vertex& a, const Vertex& b) const { return a.weight > b.weight; }
};

std::vector<sf::RectangleShape> createGrid()
{
  std::vector<sf::RectangleShape> grid;
  for (int x = 0; x < GRID_SIZE; ++x)
  {
    for (int y = 0; y < GRID_SIZE; ++y)
    {
      sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
      cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
      cell.setFillColor(sf::Color::White);
      cell.setOutlineThickness(1);
      cell.setOutlineColor(sf::Color::Black);
      grid.push_back(cell);
    }
  }
  return grid;
}

std::vector<Vertex> getNeighbors(const Vertex& node)
{
  std::vector<Vertex> neighbors;
  // std::vector<std::pair<int, int>> directions = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
  std::vector<std::pair<int, int>> directions = { { -1, 0 },  { 1, 0 }, { 0, -1 }, { 0, 1 },
                                                  { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 } };
  for (const auto& dir : directions)
  {
    int nx = node.x + dir.first;
    int ny = node.y + dir.second;
    if (nx >= 0 && ny >= 0 && nx < GRID_SIZE && ny < GRID_SIZE)
    {
      neighbors.push_back({ nx, ny, 1 });
    }
  }
  return neighbors;
}

std::vector<Vertex> reconstructPath(std::unordered_map<int, Vertex>& came_from, Vertex start, Vertex goal)
{
  std::vector<Vertex> path;
  Vertex current = goal;
  while (!(current == start))
  {
    path.push_back(current);
    current = came_from[current.x * GRID_SIZE + current.y];
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

void visualize(sf::RenderWindow& window,
               std::vector<sf::RectangleShape>& grid,
               const std::set<std::pair<int, int>>& visited,
               const std::vector<Vertex>& path,
               const Vertex& start,
               const Vertex& goal)
{
  window.clear();
  for (auto& cell : grid)
  {
    window.draw(cell);
  }
  for (const auto& node : visited)
  {
    grid[node.first * GRID_SIZE + node.second].setFillColor(sf::Color::Yellow);
  }
  for (const auto& node : path)
  {
    grid[node.x * GRID_SIZE + node.y].setFillColor(sf::Color::Red);
  }
  grid[start.x * GRID_SIZE + start.y].setFillColor(sf::Color::Green);
  grid[goal.x * GRID_SIZE + goal.y].setFillColor(sf::Color::Blue);
  for (auto& cell : grid)
  {
    window.draw(cell);
  }
  window.display();
  sf::sleep(sf::milliseconds(DELAY_MS));
}

std::vector<Vertex> dijkstra(Vertex start, Vertex goal, sf::RenderWindow& window, std::vector<sf::RectangleShape>& grid)
{
  std::priority_queue<Vertex, std::vector<Vertex>, Compare> pq;
  std::unordered_map<int, Vertex> came_from;
  std::unordered_map<int, int> cost_so_far;
  std::set<std::pair<int, int>> visited;

  pq.push(start);
  cost_so_far[start.x * GRID_SIZE + start.y] = 0;

  while (!pq.empty())
  {
    Vertex current = pq.top();
    pq.pop();
    visited.insert({ current.x, current.y });

    if (current == goal)
    {
      break;
    }

    for (Vertex next : getNeighbors(current))
    {
      int new_cost = cost_so_far[current.x * GRID_SIZE + current.y] + next.weight;
      if (cost_so_far.find(next.x * GRID_SIZE + next.y) == cost_so_far.end() ||
          new_cost < cost_so_far[next.x * GRID_SIZE + next.y])
      {
        cost_so_far[next.x * GRID_SIZE + next.y] = new_cost;
        next.weight = new_cost;
        pq.push(next);
        came_from[next.x * GRID_SIZE + next.y] = current;
      }
    }

    // Visualize the progress
    visualize(window, grid, visited, {}, start, goal);
  }

  return reconstructPath(came_from, start, goal);
}

std::vector<Vertex> astar(Vertex start, Vertex goal, sf::RenderWindow& window, std::vector<sf::RectangleShape>& grid)
{
  auto heuristic = [](Vertex a, Vertex b) { return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2)); };

  std::priority_queue<Vertex, std::vector<Vertex>, Compare> pq;
  std::unordered_map<int, Vertex> came_from;
  std::unordered_map<int, int> cost_so_far;
  std::set<std::pair<int, int>> visited;

  pq.push(start);
  cost_so_far[start.x * GRID_SIZE + start.y] = 0;

  while (!pq.empty())
  {
    Vertex current = pq.top();
    pq.pop();
    visited.insert({ current.x, current.y });

    if (current == goal)
    {
      break;
    }

    for (Vertex next : getNeighbors(current))
    {
      int new_cost = cost_so_far[current.x * GRID_SIZE + current.y] + next.weight;
      if (cost_so_far.find(next.x * GRID_SIZE + next.y) == cost_so_far.end() ||
          new_cost < cost_so_far[next.x * GRID_SIZE + next.y])
      {
        cost_so_far[next.x * GRID_SIZE + next.y] = new_cost;
        next.weight = new_cost + heuristic(next, goal);
        pq.push(next);
        came_from[next.x * GRID_SIZE + next.y] = current;
      }
    }

    // Visualize the progress
    visualize(window, grid, visited, {}, start, goal);
  }

  return reconstructPath(came_from, start, goal);
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pathfinding Visualization");
  std::vector<sf::RectangleShape> grid = createGrid();
  Vertex start = { 0, 0, 0 };
  Vertex goal = { GRID_SIZE - 1, GRID_SIZE - 1, 0 };

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    // Run Dijkstra's Algorithm
    std::vector<Vertex> path = dijkstra(start, goal, window, grid);
    visualize(window, grid, {}, path, start, goal);
    sf::sleep(sf::seconds(2));
    // Run A* Algorithm
    grid = createGrid();
    path = astar(start, goal, window, grid);
    visualize(window, grid, {}, path, start, goal);
    sf::sleep(sf::seconds(2));

    window.close();
  }

  return 0;
}
