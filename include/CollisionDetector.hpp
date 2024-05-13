#include "body.hpp"
#include "Line.hpp"

// it will detect collision between two <T> shape
class CollisionDetector
{
public:
  static bool detectCollisionBetweenSquaredShapes(Body*, Body*);
  Line* findAxis(Body *);

private:
  CollisionDetector();

};