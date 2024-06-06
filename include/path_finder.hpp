#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <vector>

struct Vertex
{
  int x, y;
  unsigned int weight;
  bool operator>(const Vertex& other) const { return weight > other.weight; }
  bool operator<(const Vertex& other) const { return weight < other.weight; }
  bool operator==(const Vertex& other) const { return x == other.x && y == other.y; }
  bool empty() const noexcept { return x == 0 && y == 0 && weight == 0; }
};

struct Compare
{
  bool operator()(const Vertex& a, const Vertex& b) const { return a.weight > b.weight; }
};

class PathFinder
{
public:
  explicit PathFinder(std::string window_name,
                      std::vector<std::vector<int>> int_grid,
                      Vertex goal,
                      Vertex start,
                      int display_dt = 30,
                      size_t cell_size = 20)
    : window_(sf::VideoMode(int_grid.size() * cell_size, int_grid[0].size() * cell_size), window_name),
      start_(start),
      goal_(goal),
      display_dt_(display_dt),
      window_name_(window_name),
      grid_shape_(std::make_pair(int_grid.size(), int_grid[0].size()))
  {
    init(int_grid);
  }

  void init(std::vector<std::vector<int>> int_grid, size_t cell_size = 20);
  void visualize(const Vertex& start, const Vertex& goal, const std::vector<Vertex>& visited = {});
  virtual std::vector<Vertex> findPath(Vertex start,
                                       Vertex goal,
                                       sf::RenderWindow& window,
                                       std::vector<sf::RectangleShape>& grid) = 0;
  void render();
  void setDirections(const std::vector<std::pair<int, int>>& dirs) { directions_ = dirs; }

protected:
  std::vector<Vertex> getNeighbors(const Vertex& node);
  void visualizeStep(const Vertex& visited, const Vertex& start, const Vertex& goal);

  sf::RenderWindow window_;
  std::vector<sf::RectangleShape> grid_;
  std::vector<Vertex> path_;
  Vertex start_;
  Vertex goal_;
  std::chrono::duration<double, std::milli> duration_;
  int display_dt_;
  std::vector<std::pair<int, int>> directions_ = { { -1, 0 },  { 1, 0 }, { 0, -1 }, { 0, 1 },
                                                   { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 } };
  std::string window_name_;
  std::pair<size_t, size_t> grid_shape_;
};