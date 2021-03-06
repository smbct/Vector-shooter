/*!
 * \file Enemy.cpp
 * \brief Implementation of Enemies
 * \author smbct
 * \date 08.10.2016
 */

#include "Enemy.hpp"
#include "EntityManager.hpp"
#include "Utils.hpp"

#include <iostream>

using namespace sf;
using namespace std;

/******************************************************************************/
/*-----------------------------Enemy class------------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
Enemy::Enemy(EntityManager& entityManager, const Texture& texture, double radius, ScoreManager& score) :
Entity(entityManager, texture, radius),
_score(score)
{
    _type = Entity::Enemy;
}

/*----------------------------------------------------------------------------*/
void Enemy::collideWith(const Entity& entity) {
    if(entity.type() == Entity::Bullet) {
        _score.increment();
        kill();
    } else if(entity.type() == Entity::Seeker || entity.type() == Entity::Wanderer || entity.type() == Entity::Enemy) {
        /*make a repulsive force */
        Vector2f vec(getPosition() - entity.getPosition());
        double lengthSq = vec.x*vec.x + vec.y*vec.y + 1.;
        lengthSq *= 0.008;
        vec.x *= lengthSq;
        vec.y *= lengthSq;
        _velocity += vec;
    } else {
        kill();
    }

    if(!alive()) {
        createExplosion();
    }
}

/*----------------------------------------------------------------------------*/
void Enemy::update(double elapsedTime) {

    Entity::update(elapsedTime);

    FloatRect worldRect(_entityManager.getWorldBound());
    FloatRect rect = getLocalBounds();

    /* FIXME : clamp position wanderer */

    /* clamp enemy position */
    // if(getPosition().x - rect.width/2. < 0.) {
    //     setPosition(rect.width/2., getPosition().y);
    // } else if(getPosition().x +rect.width/2. > worldRect.width) {
    //     setPosition(worldRect.width-rect.width/2., getPosition().y);
    // }
    // if(getPosition().y - rect.height/2. < 0.) {
    //     setPosition(getPosition().x, rect.height/2.);
    // } else if(getPosition().y + rect.height/2 > worldRect.height) {
    //     setPosition(getPosition().x, worldRect.height-rect.height/2.);
    // }

    /* damping, used to limit the max speed */
    _velocity.x *= 0.8;
    _velocity.y *= 0.8;
}

/*----------------------------------------------------------------------------*/
void Enemy::createExplosion() {

    float hue1 = Utils::randRange(0., 6.);
    float hue2 = int(hue1 + Utils::randRange(0., 2.)) % 6;
    Color color1 = Utils::HSVToColor(hue1, 0.5f, 1.);
    Color color2 = Utils::HSVToColor(hue2, 0.5f, 1.);

    for(int ind = 1; ind <= 120; ind ++) {

        float speed = 250. * (1. - 1. / Utils::randRange(1., 10.));
        ParticleState state;
        double angle = Utils::randRange(-Utils::PI(), Utils::PI());
        state.velocity = Utils::vectorFromLengthAngle(speed, angle);
        angle = Utils::toDegree(angle);
        state.type = ParticleState::Enemy;
        state.lengthMultiplier = 1.;

        const Texture& texture = _entityManager.getTextureManager().getTexture("Art/Laser.png");
        Vector2f scale(1.5, 1.5);

        Color color = Utils::colorLerp(color1, color2, Utils::randRange(0., 1.));

        _entityManager.getParticleManager().createParticle(texture, getPosition(), color, 1.2, scale, state, angle);

    }

}

/******************************************************************************/
/*------------------------------Seeeker class---------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
Seeker::Seeker(EntityManager& entityManager, ScoreManager& score) :
Enemy(entityManager, entityManager.getTextureManager().getTexture("Art/Seeker.png"), 20., score),
_acceleration(70.)
{
    _type = Entity::Seeker;
}

/*----------------------------------------------------------------------------*/
void Seeker::update(double elapsedTime) {

    Entity& player = _entityManager.getPlayer();

    Vector2f dir = player.getPosition() - getPosition();
    double length = sqrt(dir.x*dir.x + dir.y*dir.y);
    dir.x /= length;
    dir.y /= length;
    dir.x *= _acceleration;
    dir.y *= _acceleration;

    _velocity += dir;

    double angle = atan2(dir.y, dir.x) * 180. / 3.1415; /* TODO : make a pi const */

    setRotation(angle);

    Enemy::update(elapsedTime);

}


/******************************************************************************/
/*-----------------------------Wanderer class---------------------------------*/
/******************************************************************************/


/*----------------------------------------------------------------------------*/
Wanderer::Wanderer(EntityManager& entityManager, ScoreManager& score) :
Enemy(entityManager, entityManager.getTextureManager().getTexture("Art/Wanderer.png"), 20., score),
_acceleration(40.),
_frame(0)
{
    _type = Entity::Wanderer;
    _dirAngle = (static_cast<double>(rand())/RAND_MAX)*3.1415*2.; /* TODO : real PI const */

}

/*----------------------------------------------------------------------------*/
void Wanderer::update(double elapsedTime) {

    /* smooth move, not updated  each frame */
    if(_frame == 5) {

        /* update random angle */
        _dirAngle += static_cast<double>(rand())/RAND_MAX*0.2 - 0.1;

        /* TODO add a pi const ! */
        if(_dirAngle > 3.1415) {
            _dirAngle -= 3.1415;
        } else if(_dirAngle < -3.1415) {
            _dirAngle += 3.1415;
        }

        _frame = 0;

    } else {
        _frame ++;
    }

    /* compute vector from angle */
    Vector2f dir(cos(_dirAngle), sin(_dirAngle));
    dir.x *= _acceleration;
    dir.y *= _acceleration;

    _velocity += dir;

    rotate(-0.5);

    /* make sure it stays in the playground */
    FloatRect worldBound = _entityManager.getWorldBound();
    worldBound.left += getLocalBounds().width/2.;
    worldBound.width -= getLocalBounds().width/2.;
    worldBound.top += getLocalBounds().height/2.;
    worldBound.height -= getLocalBounds().height/2.;
    if(!worldBound.contains(getPosition())) {
        Vector2f center(worldBound.width/2., worldBound.height/2.);
        Vector2f vec = center - getPosition();
        _dirAngle = atan2(vec.y, vec.x)/* + static_cast<double>(rand())/RAND_MAX*3.1415 - 3.1415/2.*/;
    }

    Enemy::update(elapsedTime);
}
