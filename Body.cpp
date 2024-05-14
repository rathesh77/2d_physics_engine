#include "Body.hpp"

#include <iostream>

Body::Body()
{
  this->m_type = "NULL";
  this->m_ground = WINDOW_HEIGHT;
}

// x, y, type
Body::Body(float posX, float posY, std::string type)
{
  this->m_type = type;

  this->m_width = 30;
  this->m_height = 30;
  this->m_body = sf::RectangleShape(sf::Vector2f(this->m_width, this->m_height));
  this->m_body.setPosition(posX, posY);
  this->m_body.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
  this->m_ground = WINDOW_HEIGHT;
}

void Body::loop(Body *bodies)
{
  if (this->isOverlaping())
  {
    this->m_overlap = false;
  }
  this->updateHorizontalVelocity();
  this->updateVerticalVelocity();
  this->handleCollision(bodies);

  this->moveX();
  this->moveY();
  this->resetY();
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
  if (direction != 0)
    this->m_lookingRight = direction == 1 ? true : false;

  if (!this->m_lookingRight && !this->m_flipped)
  {
    this->m_body.scale(-1.0f, 1.0f);
    this->m_body.setOrigin(this->m_width, 0);
    this->m_flipped = true;
  }
  else if (this->m_flipped && this->m_lookingRight)
  {
    this->m_body.scale(-1.0f, 1.0f);
    this->m_body.setOrigin(0, 0);
    this->m_flipped = false;
  }

  this->m_direction = direction;
}

int Body::getDirection() { return this->m_direction; }

std::map<std::string, std::vector<Body *>> Body::detectCollisions(Body *bodies)
{
  std::map<std::string, std::vector<Body *>> collidedObjects = {
      {"up", std::vector<Body *>{}},
      {"up-left", std::vector<Body *>{}},
      {"up-right", std::vector<Body *>{}},

      {"down", std::vector<Body *>{}},
      {"side", std::vector<Body *>{}}

  };
  Body nextPos = Body();
  nextPos.m_body.setPosition(
      this->getPositionVector2f() +
      sf::Vector2f(this->m_velocityX, -this->m_velocityY));
  nextPos.m_width = this->m_width;
  nextPos.m_height = this->m_height;

  while (true)
  {
    if (bodies->m_type == "NULL" || bodies->m_type == "")
      break;
    if (compare(this, bodies))
    {
      // two of the same type of body cannot collide each other
      bodies++;
      continue;
    }
    sf::Vector2f objectPos = bodies->getPositionVector2f();

    if (this->collides(&nextPos, bodies))
    {
      if (this->getY() + this->m_height <= objectPos.y)
      {
        if (this->getX() + this->m_width >= objectPos.x + 2 &&
            this->getX() <= objectPos.x + bodies->m_width - 2)
        {
          if (this->getX() + this->m_width < objectPos.x + (this->m_width / 2))
          {
            collidedObjects["up-left"].push_back(bodies);
          }
          else if (this->getX() > objectPos.x + bodies->m_width - (this->m_width / 2))
          {
            collidedObjects["up-right"].push_back(bodies);
          }
          else
          {

            collidedObjects["up"].push_back(bodies);
          }
        }
      }
      else if (this->getY() >= objectPos.y + bodies->m_height)
      {
        collidedObjects["down"].push_back(bodies);
      }
      else
      {
        collidedObjects["side"].push_back(bodies);
      }
    }
    bodies++;
  }
  return collidedObjects;
}

void Body::handleCollision(Body *bodies)
{
  std::map<std::string, std::vector<Body *>> collidedObjects =
      this->detectCollisions(bodies);
  bool hit = false;
  for (Body *body : collidedObjects["up"])
  {
    sf::Vector2f position = body->getPositionVector2f();
    hit = true;
    // this->m_ground = position.y;
    this->m_velocityY = this->getY() - (position.y - this->m_height);
  }
  for (Body *body : collidedObjects["up-right"])
  {
    // this->m_body.setOrigin(sf::Vector2f(0,0) + sf::Vector2f(this->m_width, this->m_height));

    sf::Vector2f position = body->getPositionVector2f();
    hit = true;
    // this->m_ground = position.y;
    this->m_velocityY = this->getY() - (position.y - this->m_height);
    /*this->m_body.setOrigin(this->m_width, this->m_height);
    this->m_body.move(this->m_width, this->m_height);
    this->m_body.rotate(10);*/
    // this->m_velocityY = 0;
  }
  for (Body *body : collidedObjects["up-left"])
  {

    sf::Vector2f position = body->getPositionVector2f();
    hit = true;
    // this->m_ground = position.y;
    this->m_velocityY = this->getY() - (position.y - this->m_height);
  }
  for (Body *object : collidedObjects["down"])
  {
    hit = true;
    if (this->m_velocityY > 0)
      this->m_velocityY = 0.0f;
  }
  for (Body *object : collidedObjects["side"])
  {
    hit = true;
    this->m_direction = -this->m_direction;
    this->m_velocityX = 0;
  }
  if (this->getY() - this->m_velocityY + this->m_height >= m_ground)
  {
    this->m_velocityY = this->getY() - (this->m_ground - this->m_height);
    hit = true;
  }
  // hit = false;

  if (!hit)
  {
    this->m_overlap = false;
    this->m_ground = WINDOW_HEIGHT;
    this->m_isJumping = true;
    this->m_jumpEnabled = false;
  }
  else
  {
    this->m_overlap = true;
  }
  // we reset the origin
  // this->m_body.setOrigin(0,0);
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
  if (this->m_isJumping)
  {
    this->m_body.move(sf::Vector2f(0, -this->m_velocityY));
  }
}
void Body::updateHorizontalVelocity()
{
  float goal = this->m_maxVelocityX * this->m_direction;
  float dt = this->m_accOffset;
  float current = this->m_velocityX;
  this->m_velocityX = lerp(current, goal, dt);

  if (std::abs(this->m_velocityX) < std::abs(current))
  {
    this->m_decelerating = true;
  }
  else
  {
    this->m_decelerating = false;
  }
}

void Body::updateVerticalVelocity()
{
  if (this->m_isJumping)
    this->m_velocityY -= this->m_gravity;
}

void Body::jump()
{
  if (this->m_jumpEnabled)
  {
    this->m_isJumping = true;
    this->m_velocityY = this->m_initialVelocityY;
    this->m_jumpEnabled = false;
  }
}

void Body::resetY()
{
  if (this->getY() + this->m_height >= this->m_ground &&
      this->m_velocityY != this->m_initialVelocityY)
  {
    this->m_isJumping = false;
    this->m_velocityY = 0;
    this->m_jumpEnabled = true;
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

bool Body::isOverlaping() { return this->m_overlap; }
