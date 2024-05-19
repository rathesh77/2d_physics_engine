#include "body.hpp"
#include "Line.hpp"

struct ProjectionCorner {
  Vector2d corner;
  Vector2d projection;
  Line axis;

};

// it will detect collision between two <T> shape
class CollisionDetector
{
public:
  static bool detectCollisionBetweenSquaredShapes(Body*, Body*);
  static Line* findAxis(Body *);
  static Vector2d* findCorners(Body *);
  static ProjectionCorner projectCornerOnAxis(Vector2d, Line, Body *);
  static ProjectionCorner* findProjectionsForSourceOnTarget(Body*, Body*);
  static bool checkIfPairOfProjectionsOverlapsRectangle(ProjectionCorner, ProjectionCorner);

private:
  CollisionDetector();

};