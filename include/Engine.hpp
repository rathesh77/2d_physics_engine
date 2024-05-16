#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "body.hpp"
#include "CollisionDetector.hpp"

class Engine
{
public:
  Engine(sf::RenderWindow *);
  void tick(sf::Clock *);
  void drawLine(Vector2d, Vector2d, sf::Color);
  void drawRect(sf::Vector2f, Vector2d, sf::Color);

private:
  int frameCount = 0;
  sf::RenderWindow *m_window;
  Body *m_bodies;
  int bodies_count = 0;
  Body rect;
  Body targetRect;

};