/*!
* \file BlackHole.cpp
* \brief Black hole class Implementation
* \author smbct
* \date 08.16.2016
*/

#include "BlackHole.hpp"
#include "EntityManager.hpp"
#include "Utils.hpp"

#include <iostream>

using namespace std;
using namespace sf;

/*----------------------------------------------------------------------------*/
BlackHole::BlackHole(EntityManager& entityManager) :
Entity(entityManager, entityManager.getTextureManager().getTexture("Art/Black Hole.png"), 20.),
_life(10),
_sprayAngle(0)
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

    /* create a spray every quarter second */
    if(_clock.getElapsedTime().asSeconds() > 0.25) {
        createSpray();
        _clock.restart();
    }

}

/*----------------------------------------------------------------------------*/
void BlackHole::collideWith(const Entity& entity) {

    if(_life > 0) {
        _life --;
    } else {
        kill();
        createExplosion();
    }

}

/*----------------------------------------------------------------------------*/
void BlackHole::createExplosion() {

    float hue = static_cast<int>(3*_clock.getElapsedTime().asSeconds()) % 6;
    Color color = Utils::HSVToColor(hue, 0.25, 1.);
    const int numParticle = 150;
    float startOffset = Utils::randRange(0., Utils::PI()*2. / static_cast<double>(numParticle));

    for(int ind = 1; ind <= numParticle; ind ++) {

        Vector2f sprayVel = Utils::vectorFromLengthAngle(Utils::randRange(200., 600.), Utils::PI()*2. * static_cast<double>(ind) / numParticle + startOffset);
        Vector2f pos = getPosition() + Vector2f(0.1*sprayVel.x, 0.1*sprayVel.y);

        ParticleState state;
        state.velocity = sprayVel;
        state.lengthMultiplier = 1.;
        state.type = ParticleState::IgnoreGravity;
        const Texture& texture = _entityManager.getTextureManager().getTexture("Art/Laser.png");

        _entityManager.getParticleManager().createParticle(texture, pos, color, 4, Vector2f(1.5, 1.5), state);
    }

}

/*----------------------------------------------------------------------------*/
void BlackHole::createSpray() {

    Vector2f sprayVel = Utils::vectorFromLengthAngle(Utils::randRange(300., 350.), _sprayAngle);
    Color color = Utils::HSVToColor(5., 0.5, 0.8);
    Vector2f pos = getPosition();
    pos.x += 0.1 * sprayVel.y + Utils::randRange(4., 8.);
    pos.y += 0.1 * (-sprayVel.x) + Utils::randRange(4., 8.);
    ParticleState state;
    state.velocity = sprayVel;
    state.lengthMultiplier = 1.;
    state.type = ParticleState::Enemy;
    const Texture& texture = _entityManager.getTextureManager().getTexture("Art/Laser.png");

    _entityManager.getParticleManager().createParticle(texture, pos, color, 5., Vector2f(1.5, 1.5), state);

    _sprayAngle -= Utils::PI() / 50.;

}
