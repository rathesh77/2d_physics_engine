#include "body.hpp"
#include "Line.hpp"

// it will detect collision between two <T> shape
class CollisionDetector
{
public:
  static bool detectCollisionBetweenSquaredShapes(Body*, Body*);
  static Line* findAxis(Body *);
  static Vector2d* findCorners(Body *);
  static Vector2d projectCornerOnAxis(Vector2d, Line, Body *);

private:
  CollisionDetector();

};