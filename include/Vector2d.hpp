#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <math.h>

class Vector2d
{
public:
  Vector2d(float, float);
  Vector2d();

  float m_x;
  float m_y;

  float magnitude();
  float squaredMagnitude();
  float angle();

  Vector2d normalize();
  Vector2d rotate(float);
  Vector2d componentProduct(Vector2d);
  Vector2d add(Vector2d);
  Vector2d mult(float);
  Vector2d div(float);

  Vector2d sub(Vector2d);

  // u_ methods override current Vector object x and y coords
  void u_componentProduct(Vector2d);
  void u_add(Vector2d);

  float dotProduct(Vector2d); // scalar product
};

#endif /* VECTOR2D_H_ */
