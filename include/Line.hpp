#include "Vector2d.hpp"

class Line
{
public:
  Line();
  Line(Vector2d, Vector2d);
  Vector2d m_position;
  Vector2d m_direction;
};