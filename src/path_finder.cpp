#include "path_finder.hpp"
#include <iostream>

void PathFinder::createGrid(std::vector<std::vector<int>> int_grid, size_t cell_size)
{
  std::vector<sf::RectangleShape> grid;
  for (size_t y = 0; y < int_grid.size(); ++y)
  {
    for (size_t x = 0; x < int_grid[0].size(); ++x)
    {
      sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
      cell.setPosition(x * cell_size, y * cell_size);
      sf::Color random_color = int_grid[y][x] == 1 ? sf::Color::Black : sf::Color::White;
      cell.setFillColor(random_color);
      cell.setOutlineThickness(1);
      cell.setOutlineColor(sf::Color::Black);
      grid.push_back(cell);
    }
  }
  grid_ = grid;
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
    grid_[node.y * grid_shape_.first + node.x].setFillColor(sf::Color::Yellow);
  }
  for (const auto& node : path_)
  {
    grid_[node.y * grid_shape_.first + node.x].setFillColor(sf::Color::Red);
  }
  grid_[start.y * grid_shape_.first + start.x].setFillColor(sf::Color::Green);
  grid_[goal.y * grid_shape_.first + goal.x].setFillColor(sf::Color::Blue);
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
  for (const auto& dir : directions_)
  {
    int nx = node.x + dir.first;
    int ny = node.y + dir.second;
    if (nx >= 0 && ny >= 0 && nx < grid_shape_.first && ny < grid_shape_.second)
    {
      auto& color = grid_[ny * grid_shape_.first + nx].getFillColor();
      uint weight = color == sf::Color::Black ? 255 : 1;
      neighbors.push_back({ nx, ny, weight });
    }
  }
  return neighbors;
}

void PathFinder::replay(std::vector<Vertex>& visited)
{
  for (auto& current : visited)
  {
    grid_[current.y * grid_shape_.first + current.x].setFillColor(sf::Color::Yellow);
    grid_[start_.y * grid_shape_.first + start_.x].setFillColor(sf::Color::Green);
    grid_[goal_.y * grid_shape_.first + goal_.x].setFillColor(sf::Color::Blue);
    for (auto& cell : grid_)
    {
      window_.draw(cell);
    }
    window_.display();

    sf::sleep(sf::milliseconds(display_dt_));
  }
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
    std::vector<Vertex> visited;
    auto start = std::chrono::high_resolution_clock::now();
    path_ = findPath(start_, goal_, visited);
    duration_ = std::chrono::high_resolution_clock::now() - start;
    replay(visited);
    visualize(start_, goal_);
    sf::sleep(sf::seconds(2));

    window_.close();
  }
  // Print the duration
  std::cout << "Path finding execution time: " << duration_.count() << " milliseconds" << std::endl;
}

void PathFinder::clearWindow()
{
  // window_.clear();
  for (auto& cell : grid_)
  {
    // cell.setFillColor(sf::Color::White);
    window_.draw(cell);
  }
  // window_.display();
}