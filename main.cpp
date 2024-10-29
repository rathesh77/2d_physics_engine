#include <SFML/Graphics.hpp>
#include <iostream>

#include "Constants.hpp"
#include "World.hpp"

int main()
{

  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Physics engine", sf::Style::Close);
  window.setFramerateLimit(40);
  window.setKeyRepeatEnabled(true);
  // window.setSize(sf::Vector2u(800, 600));
  World e(&window);
  sf::Clock clock;
  while (window.isOpen())
  {
    window.clear(sf::Color(255, 255, 255));
    e.tick(&clock);
    window.display();
  }

  return EXIT_SUCCESS;
}