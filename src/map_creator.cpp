#include "map_creator.hpp"

void MapCreator::run()
{
  while (window.isOpen())
  {
    handleEvents();
    draw();
  }
}

void MapCreator::print()
{
  for (auto& row : map)
  {
    for (auto& col : row)
    {
      std::cout << " " << col << " ";
    }
    std::cout << std::endl;
  }
}

void MapCreator::handleEvents()
{
  sf::Event event;
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      window.close();
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        isMousePressed = true;
      }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        isMousePressed = false;
      }
    }
  }

  if (isMousePressed)
  {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int x = mousePos.x / cellSize;
    int y = mousePos.y / cellSize;
    if (x >= 0 && x < W && y >= 0 && y < H)
    {
      map[y][x] = 1;
    }
  }
}

void MapCreator::draw()
{
  window.clear(sf::Color::White);

  for (unsigned int i = 0; i < H; ++i)
  {
    for (unsigned int j = 0; j < W; ++j)
    {
      sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
      cell.setPosition(j * cellSize, i * cellSize);
      if (map[i][j] == 1)
      {
        cell.setFillColor(sf::Color::Black);
      }
      else
      {
        cell.setFillColor(sf::Color::White);
      }
      cell.setOutlineThickness(1);
      cell.setOutlineColor(sf::Color::Black);
      window.draw(cell);
    }
  }

  window.display();
}

// Example
// int main()
// {
//   unsigned int height = 50;   // Height of the grid
//   unsigned int width = 50;    // Width of the grid
//   unsigned int cellSize = 10; // Size of each cell in pixels

//   MapCreator gridMap(height, width, cellSize);
//   gridMap.run();
//   // gridMap.print();

//   return 0;
// }
