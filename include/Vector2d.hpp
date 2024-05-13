#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class Vector2d
{
public:

  Vector2d(float, float);
  Vector2d();

  float m_x;
  float m_y;

  float magnitude();
  float squaredMagnitude();
  Vector2d direction();

  Vector2d componentProduct(Vector2d);
  Vector2d add(Vector2d);

  // u_ methods override current Vector object x and y coords
  void u_componentProduct(Vector2d);
  void u_add(Vector2d);

  float dotProduct(float); // scalar product
};

#endif /* VECTOR2D_H_ */
