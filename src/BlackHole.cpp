/*!
* \file BlackHole.cpp
* \brief Black hole class Implementation
* \author smbct
* \date 08.16.2016
*/

#include "BlackHole.hpp"
#include "EntityManager.hpp"

#include <iostream>

using namespace std;
using namespace sf;

/*----------------------------------------------------------------------------*/
BlackHole::BlackHole(EntityManager& entityManager) :
Entity(entityManager, entityManager.getTextureManager().getTexture("Art/Black Hole.png"), 20.),
_life(10)
{
    _type = Entity::BlackHole;
}

/*----------------------------------------------------------------------------*/
void BlackHole::update(double elapsedTime) {

    list<Entity*> entities;
    _entityManager.getNearbyEntities(getPosition(), 250., entities);

    for(Entity* entity : entities) {

        Vector2f delta;
        double length;

        if(entity->type() == Entity::Bullet) {
            delta = entity->getPosition() - getPosition();
            double length = sqrt(delta.x*delta.x + delta.y*delta.y);
            delta.x *= 10./length;
            delta.y *= 10./length;
            entity->accelerate(delta);
        } else {
            delta = getPosition() - entity->getPosition();
            length = sqrt(delta.x*delta.x+delta.y*delta.y);
            length *= 2.0*length / 250.0; /* linear interpolation */

            entity->accelerate(delta);
        }
    }

}

/*----------------------------------------------------------------------------*/
void BlackHole::collideWith(const Entity& entity) {

    if(_life > 0) {
        _life --;
    } else {
        kill();
    }
}
