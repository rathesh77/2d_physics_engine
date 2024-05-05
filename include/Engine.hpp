#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "body.hpp"


class Engine {
public:
  Engine(sf::RenderWindow *);
  void tick(sf::Clock *);

private:
  int frameCount = 0;
  sf::RenderWindow *m_window;
  Body *m_bodies; 
  int bodies_count = 0;
};