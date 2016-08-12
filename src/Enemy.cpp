/*!
 * \file Enemy.cpp
 * \brief Implementation of Enemies
 * \author smbct
 * \date 08.10.2016
 */

#include "Enemy.hpp"
#include "EntityManager.hpp"

#include <iostream>

using namespace sf;
using namespace std;

/******************************************************************************/
/*-----------------------------Enemy class------------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
Enemy::Enemy(EntityManager& entityManager, const Texture& texture, double radius, ScoreManager& score) :
Entity(entityManager, texture, radius),
_score(score),
_velocity(0., 0.)
{
    _type = Entity::Enemy;
}

/*----------------------------------------------------------------------------*/
void Enemy::collideWith(const Entity& entity) {
    Entity::collideWith(entity);
    if(entity.type() == Entity::Bullet) {
        _score.increment();
    }
}

/*----------------------------------------------------------------------------*/
void Enemy::update(double elapsedTime) {

    Vector2f delta = _velocity;
    delta.x *= elapsedTime;
    delta.y *= elapsedTime;

    move(delta);

    FloatRect worldRect(_entityManager.getWorldBound());
    FloatRect rect = getLocalBounds();

    /* clamp enemy position */
    if(getPosition().x - rect.width/2. < 0.) {
        setPosition(rect.width/2., getPosition().y);
    } else if(getPosition().x +rect.width/2. > worldRect.width) {
        setPosition(worldRect.width-rect.width/2., getPosition().y);
    }
    if(getPosition().y - rect.height/2. < 0.) {
        setPosition(getPosition().x, rect.height/2.);
    } else if(getPosition().y + rect.height/2 > worldRect.height) {
        setPosition(getPosition().x, worldRect.height-rect.height/2.);
    }

    /* damping, used to limit the max speed */
    _velocity.x *= 0.8;
    _velocity.y *= 0.8;
}

/******************************************************************************/
/*------------------------------Seeeker class---------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
Seeker::Seeker(TextureManager& textureManager, EntityManager& entityManager, ScoreManager& score) :
Enemy(entityManager, textureManager.getTexture("Art/Seeker.png"), 20., score),
_acceleration(80.)
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
Wanderer::Wanderer(TextureManager& textureManager, EntityManager& entityManager, ScoreManager& score) :
Enemy(entityManager, textureManager.getTexture("Art/Wanderer.png"), 20., score),
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
        cout << "test" << endl;
        Vector2f center(worldBound.width/2., worldBound.height/2.);
        Vector2f vec = center - getPosition();
        _dirAngle = atan2(vec.y, vec.x)/* + static_cast<double>(rand())/RAND_MAX*3.1415 - 3.1415/2.*/;
    }

    Enemy::update(elapsedTime);
}
