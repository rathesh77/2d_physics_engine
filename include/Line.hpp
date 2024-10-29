
#ifndef LINE_H_
#define LINE_H_


#include "Vector2d.hpp"

class Line
{
public:
  Line();
  Line(Vector2d, Vector2d);
  Vector2d m_position;
  Vector2d m_direction;
};

#endif /* VECTOR2D_H_ */

