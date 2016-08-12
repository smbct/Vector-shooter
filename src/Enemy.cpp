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
_score(score)
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

/******************************************************************************/
/*-----------------------------Seeeker class---------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
Seeker::Seeker(TextureManager& textureManager, EntityManager& entityManager, ScoreManager& score) :
Enemy(entityManager, textureManager.getTexture("Art/Seeker.png"), 20., score),
_speed(0.)
{
    _type = Entity::Seeker;
}

/*----------------------------------------------------------------------------*/
void Seeker::update(double elapsedTime) {

    /* the seeker accelerate */
    if(_speed < 1000.) {
        _speed ++;
    }

    Entity& player = _entityManager.getPlayer();

    Vector2f dir = player.getPosition() - getPosition();
    double length = sqrt(dir.x*dir.x + dir.y*dir.y);
    dir.x /= length;
    dir.y /= length;
    dir.x *= _speed * elapsedTime;
    dir.y *= _speed * elapsedTime;

    double angle = atan2(dir.y, dir.x) * 180. / 3.1415; /* TODO : make a pi const */

    move(dir);
    setRotation(angle);

}


/******************************************************************************/
/*-----------------------------Wanderer class---------------------------------*/
/******************************************************************************/


/*----------------------------------------------------------------------------*/
Wanderer::Wanderer(TextureManager& textureManager, EntityManager& entityManager, ScoreManager& score) :
Enemy(entityManager, textureManager.getTexture("Art/Wanderer.png"), 20., score),
_speed(70.)
{
    _type = Entity::Wanderer;
    _dirAngle = (static_cast<double>(rand())/RAND_MAX)*3.1415*2.; /* TODO : real PI const */

}

/*----------------------------------------------------------------------------*/
void Wanderer::update(double elapsedTime) {


    /* update random angle */
    _dirAngle += static_cast<double>(rand())/RAND_MAX*0.04 - 0.02;

    /* TODO add a pi const ! */
    if(_dirAngle > 3.1415) {
        _dirAngle -= 3.1415;
    } else if(_dirAngle < -3.1415) {
        _dirAngle += 3.1415;
    }

    /* smooth move */
    for(int i = 1; i < 5; i++) {

        /* compute vector from angle */
        Vector2f dir(cos(_dirAngle), sin(_dirAngle));
        dir.x *= _speed*elapsedTime;
        dir.y *= _speed*elapsedTime;

        move(dir);
        rotate(-0.5);

        /* make sure it stays in the playground */
        FloatRect worldBound = _entityManager.getWorldBound();
        if(!getGlobalBounds().intersects(worldBound)) {
            Vector2f center(worldBound.width/2., worldBound.height/2.);
            Vector2f vec = center - getPosition();
            _dirAngle = atan2(vec.y, vec.x) + static_cast<double>(rand())/RAND_MAX*3.1415 - 3.1415;
        }
    }

}
