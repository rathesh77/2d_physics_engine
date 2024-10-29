#include "CollisionDetector.hpp"

CollisionDetector::CollisionDetector()
{
}

bool CollisionDetector::detectCollisionBetweenSquaredShapes(Body *source, Body *target)
{

  Line *axis = CollisionDetector::findAxis(source);
  Line *targetAxis = CollisionDetector::findAxis(target);

  Vector2d *sourceCorners = CollisionDetector::findCorners(source);
  Vector2d *targetCorners = CollisionDetector::findCorners(target);

  ProjectionCorner *p = CollisionDetector::findProjectionsForSourceOnTarget(source, target);
  ProjectionCorner *p2 = CollisionDetector::findProjectionsForSourceOnTarget(target, source);

  bool result =
      CollisionDetector::checkIfPairOfProjectionsOverlapsRectangle(p[0], p[2]) &&
      CollisionDetector::checkIfPairOfProjectionsOverlapsRectangle(p[1], p[3]) &&
      CollisionDetector::checkIfPairOfProjectionsOverlapsRectangle(p2[0], p2[2]) &&
      CollisionDetector::checkIfPairOfProjectionsOverlapsRectangle(p2[1], p2[3]);

  std::cout << result << std::endl;

  delete[] axis;
  delete[] targetAxis;
  delete[] sourceCorners;
  delete[] targetCorners;
  delete[] p;
  delete[] p2;

  return result;
}

bool CollisionDetector::checkIfPairOfProjectionsOverlapsRectangle(ProjectionCorner a, ProjectionCorner b)
{
  Vector2d minPoint = a.projection;
  Vector2d maxPoint = b.projection;
  Vector2d minAxisPoint;
  Vector2d maxAxisPoint;

  if (a.axis.m_position.add(a.axis.m_direction).m_x <= a.axis.m_position.add(a.axis.m_direction.mult(-1)).m_x)
  {
    minAxisPoint = a.axis.m_position.add(a.axis.m_direction);
    maxAxisPoint = a.axis.m_position.add(a.axis.m_direction.mult(-1));
  }
  else
  {
    maxAxisPoint = a.axis.m_position.add(a.axis.m_direction);
    minAxisPoint = a.axis.m_position.add(a.axis.m_direction.mult(-1));
  }

  if ((minPoint.m_x >= minAxisPoint.m_x && maxPoint.m_x <= maxAxisPoint.m_x) ||
      (minPoint.m_x <= minAxisPoint.m_x && maxPoint.m_x >= maxAxisPoint.m_x) ||
      (minPoint.m_x <= maxAxisPoint.m_x && maxPoint.m_x >= minAxisPoint.m_x) ||
      (minPoint.m_x >= maxAxisPoint.m_x && maxPoint.m_x <= minAxisPoint.m_x))
    return true;
  return false;
}

Line *CollisionDetector::findAxis(Body *a)
{

  float angle = a->getAngle();

  Vector2d position = a->getPosition();
  Vector2d center = position;

  Vector2d direction = Vector2d(1, 0);
  Line axisX = Line(center, direction.mult(a->getWidth() / 2).rotate(angle));
  Line axisY = Line(center, direction.mult(a->getHeight() / 2).rotate(angle + 90));

  Line *axis = new Line[2];
  axis[0] = axisX;
  axis[1] = axisY;

  return axis;
}

ProjectionCorner *CollisionDetector::findProjectionsForSourceOnTarget(Body *source, Body *target)
{
  Vector2d *corners = CollisionDetector::findCorners(source);
  Line *targetAxis = CollisionDetector::findAxis(target);

  ProjectionCorner projection1_1 = CollisionDetector::projectCornerOnAxis(corners[0], targetAxis[0], target);
  ProjectionCorner projection1_2 = CollisionDetector::projectCornerOnAxis(corners[0], targetAxis[1], target);

  ProjectionCorner projection2_1 = CollisionDetector::projectCornerOnAxis(corners[1], targetAxis[0], target);
  ProjectionCorner projection2_2 = CollisionDetector::projectCornerOnAxis(corners[1], targetAxis[1], target);

  ProjectionCorner projection3_1 = CollisionDetector::projectCornerOnAxis(corners[2], targetAxis[0], target);
  ProjectionCorner projection3_2 = CollisionDetector::projectCornerOnAxis(corners[2], targetAxis[1], target);

  ProjectionCorner projection4_1 = CollisionDetector::projectCornerOnAxis(corners[3], targetAxis[0], target);
  ProjectionCorner projection4_2 = CollisionDetector::projectCornerOnAxis(corners[3], targetAxis[1], target);

  ProjectionCorner projectionsOnAxis1[4] = {projection1_1, projection2_1, projection3_1, projection4_1};
  ProjectionCorner projectionsOnAxis2[4] = {projection1_2, projection2_2, projection3_2, projection4_2};

  ProjectionCorner minProjections[2] = {projection1_1, projection1_2};
  ProjectionCorner maxProjections[2] = {projection1_1, projection1_2};

  for (int i = 0; i < 4; i++)
  {
    float dotValue = projectionsOnAxis1[i].projection.sub(targetAxis[0].m_position).dotProduct(targetAxis[0].m_direction);
    float minDotValue = minProjections[0].projection.sub(targetAxis[0].m_position).dotProduct(targetAxis[0].m_direction);
    if (minDotValue > dotValue)
    {
      minProjections[0] = projectionsOnAxis1[i];
    }
  }

  for (int i = 0; i < 4; i++)
  {
    float dotValue = projectionsOnAxis1[i].projection.sub(targetAxis[0].m_position).dotProduct(targetAxis[0].m_direction);
    float maxDotValue = maxProjections[0].projection.sub(targetAxis[0].m_position).dotProduct(targetAxis[0].m_direction);
    if (maxDotValue < dotValue)
    {
      maxProjections[0] = projectionsOnAxis1[i];
    }
  }

  for (int i = 0; i < 4; i++)
  {
    float dotValue = projectionsOnAxis2[i].projection.sub(targetAxis[1].m_position).dotProduct(targetAxis[1].m_direction);
    float minDotValue = minProjections[1].projection.sub(targetAxis[1].m_position).dotProduct(targetAxis[1].m_direction);
    if (minDotValue > dotValue)
    {
      minProjections[1] = projectionsOnAxis2[i];
    }
  }

  for (int i = 0; i < 4; i++)
  {
    float dotValue = projectionsOnAxis2[i].projection.sub(targetAxis[1].m_position).dotProduct(targetAxis[1].m_direction);
    float maxDotValue = maxProjections[1].projection.sub(targetAxis[1].m_position).dotProduct(targetAxis[1].m_direction);
    if (maxDotValue < dotValue)
    {
      maxProjections[1] = projectionsOnAxis2[i];
    }
  }
  ProjectionCorner *projections = new ProjectionCorner[4];

  projections[0] = minProjections[0];
  projections[1] = minProjections[1];
  projections[2] = maxProjections[0];
  projections[3] = maxProjections[1];

  delete[] targetAxis;
  delete[] corners;

  return projections;
}

Vector2d *CollisionDetector::findCorners(Body *a)
{

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

ProjectionCorner CollisionDetector::projectCornerOnAxis(Vector2d corner, Line axis, Body *targetRect)
{

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
  return ProjectionCorner{.corner = corner, .projection = axis.m_position.add(Vector2d(x, y)), .axis = axis};
}