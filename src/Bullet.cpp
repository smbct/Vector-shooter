/*!
* \file Bullet.cpp
* \brief Bullet class implementation
* \author smbct
* \date 08.11.2016
*/

#include "Bullet.hpp"

#include <iostream>

using namespace std;

using namespace sf;

/*----------------------------------------------------------------------------*/
Bullet::Bullet(TextureManager& textureManager, EntityManager& entityManager, Vector2f pos, Vector2f dir) :
Entity(entityManager, textureManager.getTexture("Art/Bullet.png"), 8),
_speed(500.),
_dir(dir)
{
    _type = Entity::Bullet;
    setPosition(pos);

    /* compute the angle */

    double angle = atan2(dir.y, dir.x);
    angle *= 180. / 3.1415; /* TODO change with a define */
    setRotation(angle);
}

/*----------------------------------------------------------------------------*/
void Bullet::update(double elapsedTime) {
    Vector2f delta = _dir;
    delta.x *= elapsedTime*_speed;
    delta.y *= elapsedTime*_speed;
    move(delta);
}

/*----------------------------------------------------------------------------*/
void Bullet::collideWith(const Entity& entity) {
    if(entity.type() != Entity::Player && entity.type() != Entity::Bullet) {
        _alive = false;
    }
}
