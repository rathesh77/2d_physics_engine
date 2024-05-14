#include <math.h>
#include "Vector2d.hpp"

Vector2d::Vector2d() {}

Vector2d::Vector2d(float x, float y)
{
  this->m_x = x;
  this->m_y = y;
}

float Vector2d::magnitude()
{
  return sqrt(this->squaredMagnitude());
}

float Vector2d::squaredMagnitude()
{
  return (this->m_x * this->m_x) + (this->m_y * this->m_y);
}

Vector2d Vector2d::direction()
{
  return Vector2d(this->m_x / this->magnitude(), this->m_y / this->magnitude());
}

Vector2d Vector2d::componentProduct(Vector2d vec)
{
  return Vector2d(this->m_x * vec.m_x, this->m_y * vec.m_y);
}

float Vector2d::dotProduct(float scalar)
{
  return (this->m_x * scalar) + (this->m_y * scalar);
}

Vector2d Vector2d::add(Vector2d vec)
{
  return Vector2d(this->m_x + vec.m_x, this->m_y + vec.m_y);
}


Vector2d Vector2d::mult(float scalar)
{
  return Vector2d(this->m_x * scalar, this->m_y * scalar);
}
Vector2d Vector2d::sub(Vector2d vec)
{
  return Vector2d(this->m_x - vec.m_x, this->m_y - vec.m_y);
}

void Vector2d::u_componentProduct(Vector2d vec)
{
  this->m_x *= vec.m_x;
  this->m_y *= vec.m_y;
}

void Vector2d::u_add(Vector2d vec)
{
  this->m_x += vec.m_x;
  this->m_y += vec.m_y;
}

Vector2d Vector2d::rotate(float angle)
{
  double radians = angle * (M_PI / 180);
  return Vector2d((cos(radians) * this->m_x) - (sin(radians) * this->m_y), (sin(radians) * this->m_x) + (cos(radians) * this->m_y));
}
