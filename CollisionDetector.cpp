#include "CollisionDetector.hpp"
#include <iostream>

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

  Vector2d topLeft = center.sub(Vector2d(a->getWidth() / 2, a->getHeight() / 2).rotate(a->getAngle()));
  Vector2d topRight = center.add(Vector2d(a->getWidth() / 2, -a->getHeight() / 2).rotate(a->getAngle()));


  Vector2d bottomLeft = center.sub(Vector2d(a->getWidth() / 2, -a->getHeight() / 2).rotate(a->getAngle()));
  Vector2d bottomRight = center.add(Vector2d(a->getWidth() / 2, a->getHeight() / 2).rotate(a->getAngle()));
  Vector2d *corners = new Vector2d[4];

  corners[0] = topLeft;
  corners[1] = topRight;
  corners[2] = bottomLeft;
  corners[3] = bottomRight;

  return corners;
}

Vector2d CollisionDetector::projectCornerOnAxis(Vector2d corner, Line axis, Body *targetRect) {


  // float dx = cos(axis.m_direction.angle() * (M_PI / 180));
  // float dy = sin(axis.m_direction.angle() * (M_PI / 180));
  // float dotValue = (dx * (corner.m_x - targetRect->getPosition().m_x)) + (dy * (corner.m_y - targetRect->getPosition().m_y));
  // return Vector2d(targetRect->getPosition().m_x + (dx * dotValue), targetRect->getPosition().m_y + (dy * dotValue));

  // a dot b = |a| * |b| * cos(angle)

  // cos(theta) = adjacent / hypothenuse
  // sin(theta) = opposite / hypothenuse

  // cos(angle) = |a| / |b|
  // |a| = cos(angle) * |b|
  // => a hat dot b = cos(angle) * |b|

  float angleInRadians = axis.m_direction.angle() * (M_PI / 180);
  float dotValue = axis.m_direction.normalize().dotProduct(corner.sub(axis.m_position));
  float x = cos(angleInRadians) * dotValue;
  float y = sin(angleInRadians) * dotValue;
  return axis.m_position.add(Vector2d(x, y));
}