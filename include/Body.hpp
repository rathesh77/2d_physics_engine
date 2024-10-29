
#ifndef BODY_H_
#define BODY_H_

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Vector2d.hpp"
#include "WorldParameters.hpp"

#include <iostream>

class Body
{
public:
  Vector2d getPosition();
  sf::Vector2f getPositionVector2f();

  Body(WorldParameters, float, float, float, float, std::string);

  Body();

  void loop(Body *);

  void moveX();
  void moveY();

  void updateHorizontalVelocity();
  void updateVerticalVelocity();
  void resetY();

  void updateAcc();
  void reduceAcc();

  void setDirectionX(int);

  int getDirection();
  float getVelocityX();
  float getWidth();
  float getAngle();
  float getHeight();

  float getX();
  float getY();

  void jump();

  bool isOverlaping();

  std::map<std::string, std::vector<Body *>>
  detectCollisions(Body *);
  void handleCollision(Body *);
  void rotate(float);
  bool collides(Body *, Body *);
  bool compare(Body *, Body *);

  float lerp(float, float, float);

  sf::RectangleShape m_body;

protected:
  float m_angle = 0; // degrees
  float m_theta;     // radians
  std::string m_type;

  int m_width;
  int m_height;
  int m_direction = 0;

  float m_acc = 0.0f;

  float m_velocityX = 0.0f;
  float m_maxVelocityX = 1.0f;

  float m_accOffset = 0.25f;

  float m_initialVelocityY = 9.45f;
  float m_velocityY = 0;

  float m_ground;
  WorldParameters m_WorldParameters;
};

#endif /* BODY_H_ */
