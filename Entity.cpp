/*!
 * \file Entity.cpp
 * \brief Implementation of Entity
 * \author Samuel Buchet
 * \date 08.09.2016
 */

#include "Entity.hpp"

using namespace std;
using namespace sf;

/*----------------------------------------------------------------------------*/
Entity::Entity(const sf::Texture& texture, double radius) :
Sprite(texture),
_radius(radius),
_alive(true)
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
bool Entity::alive() {
    return _alive;
}

/******************************************************************************/
/*----------------------------------modifiers---------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
void Entity::move(const Vector2f& dir) {
    setPosition(getPosition() + dir);
}
