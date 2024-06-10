#include <SFML/Graphics.hpp>
#include <vector>

class MapCreator
{
public:
  MapCreator(unsigned int height, unsigned int width, unsigned int cellSize)
    : H(height),
      W(width),
      cellSize(cellSize),
      map(height, std::vector<int>(width, 0))
  {
    window.create(sf::VideoMode(width * cellSize, height * cellSize), "Grid Map");
    window.setFramerateLimit(60);
  }

  void run();
  void print();

  std::vector<std::vector<int>>& getMap() { return map; }

private:
  unsigned int H, W, cellSize;
  sf::RenderWindow window;
  std::vector<std::vector<int>> map;
  bool isMousePressed = false;

  void handleEvents();
  void draw();
};