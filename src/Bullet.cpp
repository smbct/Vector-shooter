/*!
* \file Bullet.cpp
* \brief Bullet class implementation
* \author smbct
* \date 08.11.2016
*/

#include "Bullet.hpp"
#include "EntityManager.hpp"
#include "Utils.hpp"

#include <iostream>

using namespace std;

using namespace sf;

/*----------------------------------------------------------------------------*/
Bullet::Bullet(EntityManager& entityManager, Vector2f pos, Vector2f dir) :
Entity(entityManager, entityManager.getTextureManager().getTexture("Art/Bullet.png"), 8),
_speed(500.)
{
    _type = Entity::Bullet;
    setPosition(pos);

    /* compute the angle */

    double angle = atan2(dir.y, dir.x);
    angle *= 180. / 3.1415; /* TODO change with a define */
    setRotation(angle);

    _velocity = dir;
    _velocity.x *= _speed;
    _velocity.y *= _speed;
}

/*----------------------------------------------------------------------------*/
void Bullet::update(double elapsedTime) {

    double angle = Utils::vectorToAngle(_velocity);
    angle = Utils::toDegree(angle);
    setRotation(angle);
    Entity::update(elapsedTime);

    /* make sur the bullet is still on the screen */
    FloatRect& world = _entityManager.getWorldBound();
    if(!world.contains(getPosition())) {
        createExplosion();
        kill();
    }

}

/*----------------------------------------------------------------------------*/
void Bullet::createExplosion() {

    for(int ind = 0; ind < 30; ind ++) {
        ParticleState state;
        state.velocity = Utils::vectorFromLengthAngle(Utils::randRange(100., 300.), Utils::randRange(-Utils::PI(), Utils::PI()));
        state.type = ParticleState::Enemy;
        state.lengthMultiplier = 1.;

        const Texture& texture = _entityManager.getTextureManager().getTexture("Art/Laser.png");
        Vector2f scale(1, 1);
        Color color(66, 143, 168);
        _entityManager.getParticleManager().createParticle(texture, getPosition(), color, 1.5, scale, state);
    }
}

/*----------------------------------------------------------------------------*/
void Bullet::collideWith(const Entity& entity) {
    if(entity.type() != Entity::Player && entity.type() != Entity::Bullet) {
        _alive = false;
    }
}
