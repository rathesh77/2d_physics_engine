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

  Vector2d direction = Vector2d(1, 0);

   
  Line axisX = Line(center, direction.mult(a->getWidth() / 2).rotate(angle));
  Line axisY =  Line(center, direction.mult(a->getHeight() / 2).rotate(angle + 90));

  Line *axis = new Line[2];
  axis[0] = axisX;
  axis[1] = axisY;

  return axis;
}

Vector2d* CollisionDetector::findCorners(Body *a) {


  Vector2d center = a->getPosition();

  Vector2d direction = Vector2d(1,0).rotate(a->getAngle()).mult(10);

  Vector2d topLeft = center.add(direction.rotate(90 + 45));
  Vector2d topRight = center.add(direction.rotate(45).mult(1));


  Vector2d bottomLeft = center.add(direction.rotate(-(90 + 45)).mult(1));
  Vector2d bottomRight = center.add(direction.rotate(-45).mult(1));

  Vector2d *corners = new Vector2d[4];

  corners[0] = topLeft;
  corners[1] = topRight;
  corners[2] = bottomLeft;
  corners[3] = bottomRight;

  return corners;
}
