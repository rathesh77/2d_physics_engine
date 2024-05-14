#include "CollisionDetector.hpp"

CollisionDetector::CollisionDetector() {

}

bool CollisionDetector::detectCollisionBetweenSquaredShapes(Body *a, Body *b) {

  return false;
}


Line* CollisionDetector::findAxis(Body *a) {

  float angle = a->getAngle();

  Vector2d position = a->getPosition();
  Vector2d center = position;

  Vector2d direction(1, 0);

  Line axisX = Line(center, direction.rotate(angle));
  Line axisY =  Line(center, direction.rotate(angle + 90));

  Line *axis = new Line[2];
  axis[0] = axisX;
  axis[1] = axisY;

  return axis;
}
