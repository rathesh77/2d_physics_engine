#include "Body.hpp"

Body::Body()
{
  this->m_type = "NULL";
  this->m_ground = WINDOW_HEIGHT;
}

// x, y, type
Body::Body(WorldParameters WorldParameters, float posX, float posY, float width, float height, std::string type)
{
  this->m_type = type;

  this->m_width = width;
  this->m_height = height;
  this->m_body = sf::RectangleShape(sf::Vector2f(this->m_width, this->m_height));
  this->m_body.setPosition(posX, posY);
  this->m_body.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
  this->m_ground = WINDOW_HEIGHT;
  this->m_WorldParameters = WorldParameters;
}

void Body::loop(Body *bodies)
{

  this->updateHorizontalVelocity();
  this->updateVerticalVelocity();
  this->handleCollision(bodies);
  this->resetY();

  this->moveX();
  this->moveY();
}

Vector2d Body::getPosition()
{
  sf::Vector2f pos = this->m_body.getPosition();
  return Vector2d(pos.x, pos.y);
}

sf::Vector2f Body::getPositionVector2f()
{
  return this->m_body.getPosition();
}
void Body::setDirectionX(int direction)
{
  this->m_direction = direction;
}

int Body::getDirection() { return this->m_direction; }

std::map<std::string, std::vector<Body *>> Body::detectCollisions(Body *bodies)
{
  return std::map<std::string, std::vector<Body *>>{};
}

void Body::handleCollision(Body *bodies)
{
 
}

bool Body::compare(Body *a, Body *b) { return a == b; }

bool Body::collides(Body *a, Body *b)
{
  return a->getX() >= b->getX() - a->m_width + 2 &&
         a->getX() <= b->getX() + b->m_width - 2 &&
         a->getY() >= b->getY() - a->m_height &&
         a->getY() <= b->getY() + b->m_height;
}
void Body::moveX() // no collisions handling here. Only moving sprite
{
  this->m_body.move(sf::Vector2f(this->m_velocityX, 0));
}

void Body::moveY()
{
    this->m_body.move(sf::Vector2f(0, -this->m_velocityY));
}
void Body::updateHorizontalVelocity()
{
  float goal = this->m_maxVelocityX * this->m_direction;
  float dt = this->m_accOffset;
  float current = this->m_velocityX;
  this->m_velocityX = lerp(current, goal, dt);
}

void Body::updateVerticalVelocity()
{
    this->m_velocityY -= this->m_WorldParameters.m_gravity;
}


void Body::resetY()
{
  if (this->getY() + this->m_height >= this->m_ground &&
      this->m_velocityY != this->m_initialVelocityY)
  {
    this->m_velocityY = 0;
    // this->m_body.setPosition(this->getX(), WINDOW_HEIGHT - 20);
  }
}

float Body::lerp(float current, float goal, float dt)
{
  if (current + dt < goal)
    return current + dt;

  if (goal < current)
    return current - dt;

  return goal;
}


void Body::rotate(float angle)
{
  this->m_angle += angle;
  this->m_body.rotate(angle);
}


float Body::getWidth() { return this->m_width; }

float Body::getHeight() { return this->m_height; }

float Body::getAngle() { return this->m_angle; }

float Body::getVelocityX() { return this->m_velocityX; }

float Body::getX() { return this->getPositionVector2f().x; }

float Body::getY() { return this->getPositionVector2f().y; }

