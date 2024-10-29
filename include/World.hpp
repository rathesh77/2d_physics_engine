#ifndef WORLD_H
#define WORLD_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "CollisionDetector.hpp"
#include "Body.hpp"
#include "WorldParameters.hpp"

#include <iostream>

class World
{
public:
  World(sf::RenderWindow *);
  ~World();

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
  WorldParameters m_WorldParameters;
};

#endif /* WORLD_H */
