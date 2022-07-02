/*!
 * \file Entity.cpp
 * \brief Implementation of Entity
 * \author smbct
 * \date 08.09.2016
 */

#include "Entity.hpp"
#include "EntityManager.hpp"

#include <iostream>

using namespace std;
using namespace sf;

/*----------------------------------------------------------------------------*/
Entity::Entity(EntityManager& entityManager, const sf::Texture& texture, double radius) :
Sprite(texture),
_entityManager(entityManager),
_velocity(0., 0.),
_radius(radius),
_alive(true),
_type(None)
{
    Vector2f orig;
    orig.x = getTextureRect().width/2.;
    orig.y = getTextureRect().height/2.;
    setOrigin(orig);

}

/******************************************************************************/
/*-----------------------------getter methods---------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
bool Entity::alive() const {
    return _alive;
}

/*----------------------------------------------------------------------------*/
Entity::Type Entity::type() const {
    return _type;
}

float Entity::getRadius() {
  return _radius;
}

/******************************************************************************/
/*----------------------------------modifiers---------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
void Entity::move(const Vector2f& dir) {
    setPosition(getPosition() + dir);
}


/*----------------------------------------------------------------------------*/
void Entity::accelerate(const Vector2f& acc) {
    _velocity += acc;
}

void Entity::kill() {
    _alive = false;
}

/*----------------------------------------------------------------------------*/
void Entity::update(double elapsedTime) {

    Vector2f delta(_velocity);
    delta.x *= elapsedTime;
    delta.y *= elapsedTime;

    move(delta);
}

/*----------------------------------------------------------------------------*/
void Entity::collideWith(const Entity& entity) {
    kill();
}

/******************************************************************************/
/*-----------------------------static methods---------------------------------*/
/******************************************************************************/

bool Entity::collision(const Entity& left, const Entity& right) {
    bool res = false;

    Vector2f vec = left.getPosition();
    vec -= right.getPosition();

    double distSq = vec.x*vec.x + vec.y*vec.y;
    double distMin = left._radius+right._radius;

    res = (distSq <= distMin*distMin);

    return res;
}


bool Entity::insideRect(Entity& entity, sf::Vector2i corner, sf::Vector2i dimensions) {

  auto pos = entity.getPosition();

  bool res = false;

  if( (pos.x-entity._radius >= corner.x) && (pos.x+entity._radius <= corner.x+dimensions.x)) {
    if( (pos.y-entity._radius >= corner.y) && (pos.y+entity._radius <= corner.y+dimensions.y)) {
      res = true;
    }
  }

  return res;
}
