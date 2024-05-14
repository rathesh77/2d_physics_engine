#include "Engine.hpp"
#include <iostream>

Engine::Engine(sf::RenderWindow *window)
{
  this->m_window = window;
  this->m_bodies = new Body[bodies_count + 1];
  for (int i = 0; i < bodies_count; i++)
  {
    int x = (rand() % WINDOW_WIDTH - 20);
    int y = (rand() % WINDOW_HEIGHT - 20);
    this->m_bodies[i] = Body(x, y, "test");
  }
  this->m_bodies[bodies_count] = Body();
  rect = Body(0, 0, "rectangle");
  rect.m_body.setOrigin(15, 15);
}

void Engine::tick(sf::Clock *clock)
{
  sf::Event event;

  while (this->m_window->pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::Closed:
      this->m_window->close();
      break;
    case sf::Event::MouseButtonPressed:
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        Body *bodies_tmp = new Body[++bodies_count + 1];
        memcpy(bodies_tmp, this->m_bodies, sizeof(Body) * (bodies_count - 1));
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this->m_window);
        int x = mousePos.x;
        int y = mousePos.y;
        std::cout << "x: " + std::to_string(x) << std::endl;
        std::cout << "y: " + std::to_string(y) << std::endl;

        bodies_tmp[bodies_count - 1] = Body(x, y, "test");

        bodies_tmp[bodies_count] = Body();
        this->m_bodies = bodies_tmp;
      }
      break;
    }
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
  }
  for (int i = 0; i < bodies_count; i++)
  {
    this->m_bodies[i].loop(m_bodies);
    this->m_window->draw(this->m_bodies[i].m_body);
  }

  rect.m_body.setFillColor(sf::Color(255, 0, 0));
  // rect.m_body.setOrigin(10, 10);
  rect.m_body.setPosition((sf::Vector2f)sf::Mouse::getPosition(*this->m_window));
  rect.rotate(1);

  Line *axis = CollisionDetector::findAxis(&rect);

  Vector2d dest1 = axis[0].m_position.add(axis[0].m_direction.mult(20));
  Vector2d dest2 = axis[1].m_position.add(axis[1].m_direction.mult(20));

  sf::Vertex vertices1[2] =
      {
          sf::Vertex(sf::Vector2f(axis[0].m_position.m_x, axis[0].m_position.m_y)),
          sf::Vertex(sf::Vector2f(dest1.m_x, dest1.m_y)),
      };

  sf::Vertex vertices2[2] =
      {
          sf::Vertex(sf::Vector2f(axis[1].m_position.m_x, axis[1].m_position.m_y)),
          sf::Vertex(sf::Vector2f(dest2.m_x, dest2.m_y)),
      };

  this->m_window->draw(rect.m_body);
  // this->m_window->draw(circle);
  // this->m_window->draw(circle2);

  this->m_window->draw(vertices1, 2, sf::Lines);
  this->m_window->draw(vertices2, 2, sf::Lines);
}