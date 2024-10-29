#include "World.hpp"

World::World(sf::RenderWindow *window)
{
  this->m_WorldParameters = WorldParameters();
  this->m_window = window;
  this->m_bodies = new Body[bodies_count + 1];
  for (int i = 0; i < bodies_count; i++)
  {
    int x = (rand() % WINDOW_WIDTH - 20);
    int y = (rand() % WINDOW_HEIGHT - 20);
    this->m_bodies[i] = Body(this->m_WorldParameters, x, y, 30, 30, "test");
  }
  this->m_bodies[bodies_count] = Body();
  rect = Body(this->m_WorldParameters, 0, 0, 40, 80, "rectangle");
  rect.m_body.setOrigin(rect.getWidth() / 2, rect.getHeight() / 2);
  rect.rotate(40);

  targetRect = Body(this->m_WorldParameters, 400, 200, 40, 40, "rectangle");
  targetRect.m_body.setOrigin(targetRect.getWidth() / 2, targetRect.getHeight() / 2);
  targetRect.m_body.setFillColor(sf::Color(0, 255, 0));
  targetRect.rotate(20);
}

World::~World()
{
  delete []this->m_bodies;
}

void World::tick(sf::Clock *clock)
{
  sf::Event event;

  while (this->m_window->pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::Closed:
      this->m_window->close();
      return;
      break;
    case sf::Event::MouseButtonPressed:
      if (event.mouseButton.button == sf::Mouse::Left)
      {
        Body *bodies_tmp = new Body[++bodies_count + 1];
        for (int i = 0; i < bodies_count - 1; i++)
          bodies_tmp[i] = this->m_bodies[i];
        
        sf::Vector2i mousePos = sf::Mouse::getPosition(*this->m_window);
        int x = mousePos.x;
        int y = mousePos.y;
        std::cout << "x: " + std::to_string(x) << std::endl;
        std::cout << "y: " + std::to_string(y) << std::endl;

        bodies_tmp[bodies_count - 1] = Body(this->m_WorldParameters, x, y, 30, 30, "test");
        bodies_tmp[bodies_count] = Body();
        delete []this->m_bodies;
        this->m_bodies = bodies_tmp;
        bodies_tmp = NULL;
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
  rect.m_body.setPosition((sf::Vector2f)sf::Mouse::getPosition(*this->m_window));

  Line *axis = CollisionDetector::findAxis(&rect);
  Line *targetAxis = CollisionDetector::findAxis(&targetRect);

  Vector2d dest1 = axis[0].m_position.add(axis[0].m_direction);
  Vector2d dest2 = axis[1].m_position.add(axis[1].m_direction);

  sf::Vertex vertices1[2] =
      {
          sf::Vertex(sf::Vector2f(axis[0].m_position.m_x, axis[0].m_position.m_y), sf::Color::Black),
          sf::Vertex(sf::Vector2f(dest1.m_x, dest1.m_y), sf::Color::Black),
      };

  sf::Vertex vertices2[2] =
      {
          sf::Vertex(sf::Vector2f(axis[1].m_position.m_x, axis[1].m_position.m_y), sf::Color::Black),
          sf::Vertex(sf::Vector2f(dest2.m_x, dest2.m_y), sf::Color::Black),
      };

  Vector2d *corners = CollisionDetector::findCorners(&rect);

  this->m_window->draw(rect.m_body);

  this->m_window->draw(vertices1, 2, sf::Lines);
  this->m_window->draw(vertices2, 2, sf::Lines);


  ProjectionCorner *p = CollisionDetector::findProjectionsForSourceOnTarget(&rect, &targetRect);
  ProjectionCorner *p2 = CollisionDetector::findProjectionsForSourceOnTarget(&targetRect, &rect);

  this->drawRect(sf::Vector2f(5, 5), p[0].projection, sf::Color(0, 0, 255));
  this->drawRect(sf::Vector2f(5, 5), p[1].projection, sf::Color(0, 0, 255));

  this->drawRect(sf::Vector2f(5, 5), p[2].projection, sf::Color(0, 0, 255));
  this->drawRect(sf::Vector2f(5, 5), p[3].projection, sf::Color(0, 0, 255));

  this->drawLine(p[0].corner, p[0].projection, sf::Color(0, 0, 255));
  this->drawLine(p[1].corner, p[1].projection, sf::Color(0, 0, 255));

  this->drawLine(p[2].corner, p[2].projection, sf::Color(0, 0, 255));
  this->drawLine(p[3].corner, p[3].projection, sf::Color(0, 0, 255));

  this->drawRect(sf::Vector2f(5, 5), p2[0].projection, sf::Color(0, 0, 255));
  this->drawRect(sf::Vector2f(5, 5), p2[1].projection, sf::Color(0, 0, 255));

  this->drawRect(sf::Vector2f(5, 5), p2[2].projection, sf::Color(0, 0, 255));
  this->drawRect(sf::Vector2f(5, 5), p2[3].projection, sf::Color(0, 0, 255));

  this->drawLine(p2[0].corner, p2[0].projection, sf::Color(0, 0, 255));
  this->drawLine(p2[1].corner, p2[1].projection, sf::Color(0, 0, 255));

  this->drawLine(p2[2].corner, p2[2].projection, sf::Color(0, 0, 255));
  this->drawLine(p2[3].corner, p2[3].projection, sf::Color(0, 0, 255));

  Vector2d dest3 = targetAxis[0].m_position.add(targetAxis[0].m_direction);
  Vector2d dest4 = targetAxis[1].m_position.add(targetAxis[1].m_direction);

  this->drawLine(targetAxis[0].m_position, dest3, sf::Color::Black);
  this->drawLine(targetAxis[1].m_position, dest4, sf::Color::Black);

  this->drawLine(targetAxis[0].m_position, dest3, sf::Color::Black);
  this->drawLine(targetAxis[1].m_position, dest4, sf::Color::Black);

  bool collisionDetected = CollisionDetector::detectCollisionBetweenSquaredShapes(&rect, &targetRect);
  if (collisionDetected)
  {
    targetRect.m_body.setFillColor(sf::Color(255, 255, 255));
  }
  else
  {
    targetRect.m_body.setFillColor(sf::Color(0, 255, 0));
  }
  this->m_window->draw(targetRect.m_body);
  targetRect.rotate(1);
  rect.rotate(1);

  delete[] targetAxis;
  delete[] axis;
  delete[] p;
  delete[] p2;
  delete[] corners;
}

void World::drawLine(Vector2d pointOne, Vector2d pointTwo, sf::Color color)
{
  sf::Vertex vertices[2] = {
      sf::Vertex(sf::Vector2f(pointOne.m_x, pointOne.m_y), color),
      sf::Vertex(sf::Vector2f(pointTwo.m_x, pointTwo.m_y), color),
  };

  this->m_window->draw(vertices, 2, sf::Lines);
}

void World::drawRect(sf::Vector2f size, Vector2d position, sf::Color fillColor)
{
  sf::RectangleShape rect(size);

  rect.setPosition(position.m_x, position.m_y);
  rect.setOrigin(size.x / 2, size.y / 2);
  rect.setFillColor(sf::Color(0, 0, 255));
  this->m_window->draw(rect);
}