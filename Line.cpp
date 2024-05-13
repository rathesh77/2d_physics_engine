#include "Line.hpp"

Line::Line() {
  
}

Line::Line(Vector2d position, Vector2d direction) {

  this->m_position = position;
  this->m_direction = direction;

}
