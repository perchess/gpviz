#include "path_finder.hpp"
#include <iostream>

void PathFinder::init(std::vector<std::vector<int>> int_grid, size_t cell_size)
{
  std::vector<sf::RectangleShape> grid;
  for (size_t x = 0; x < int_grid.size(); ++x)
  {
    for (size_t y = 0; y < int_grid[0].size(); ++y)
    {
      sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
      cell.setPosition(x * cell_size, y * cell_size);
      sf::Color random_color = int_grid[x][y] == 1 ? sf::Color::Black : sf::Color::White;
      cell.setFillColor(random_color);
      cell.setOutlineThickness(1);
      cell.setOutlineColor(sf::Color::Black);
      grid.push_back(cell);
    }
  }
  grid_ = grid;
  // auto size = sf::Vector2u(int_grid.size() * cell_size, int_grid[0].size() * cell_size);
  // window_.setSize(size);

  // window_ = sf::RenderWindow(sf::VideoMode(int_grid.size() * cell_size, int_grid[0].size() * cell_size), window_name_);
}

void PathFinder::visualize(const Vertex& start, const Vertex& goal, const std::vector<Vertex>& visited)
{
  window_.clear();
  for (auto& cell : grid_)
  {
    window_.draw(cell);
  }
  for (const auto& node : visited)
  {
    grid_[node.x * grid_shape_.first + node.y].setFillColor(sf::Color::Yellow);
  }
  for (const auto& node : path_)
  {
    grid_[node.x * grid_shape_.first + node.y].setFillColor(sf::Color::Red);
  }
  grid_[start.x * grid_shape_.first + start.y].setFillColor(sf::Color::Green);
  grid_[goal.x * grid_shape_.first + goal.y].setFillColor(sf::Color::Blue);
  for (auto& cell : grid_)
  {
    window_.draw(cell);
  }
  window_.display();
  sf::sleep(sf::milliseconds(display_dt_));
}

std::vector<Vertex> PathFinder::getNeighbors(const Vertex& node)
{
  std::vector<Vertex> neighbors;
  int grid_size = grid_shape_.first;
  for (const auto& dir : directions_)
  {
    int nx = node.x + dir.first;
    int ny = node.y + dir.second;
    if (nx >= 0 && ny >= 0 && nx < grid_size && ny < grid_size)
    {
      auto& color = grid_[nx * grid_size + ny].getFillColor();
      uint weight = color == sf::Color::Black ? 255 : 1;
      neighbors.push_back({ nx, ny, weight });
    }
  }
  return neighbors;
}

void PathFinder::visualizeStep(const Vertex& visited, const Vertex& start, const Vertex& goal)
{
  grid_[visited.x * grid_shape_.first + visited.y].setFillColor(sf::Color::Yellow);
  grid_[start.x * grid_shape_.first + start.y].setFillColor(sf::Color::Green);
  grid_[goal.x * grid_shape_.first + goal.y].setFillColor(sf::Color::Blue);
  for (auto& cell : grid_)
  {
    window_.draw(cell);
  }
  window_.display();
  sf::sleep(sf::milliseconds(display_dt_));
}

void PathFinder::render()
{
  while (window_.isOpen())
  {
    sf::Event event;
    while (window_.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window_.close();
      }
    }

    path_ = findPath(start_, goal_, window_, grid_);
    visualize(start_, goal_);
    sf::sleep(sf::seconds(2));

    window_.close();
  }
}