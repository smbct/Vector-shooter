/*!
* \file Player.cpp
* \brief Player class implementation
* \author smbct
* \date 08.10.2016
*/

#include "Player.hpp"
#include "EntityManager.hpp"
#include "Bullet.hpp"

#include <iostream>

using namespace sf;
using namespace std;

/*----------------------------------------------------------------------------*/
Player::Player(TextureManager& textureManager, EntityManager& entityManager, sf::Window& input) :
Entity(entityManager, textureManager.getTexture("Art/Player.png"), 20),
_input(input),
_textureManager(textureManager),
_speed(600.),
_root2(sqrt(2)),
_fire(false)
{
    _type = Entity::Player;
}

/*----------------------------------------------------------------------------*/
void Player::update(double elapsedTime) {

    sf::Vector2f dir(0., 0.);

    double angle = getRotation();

    if(Keyboard::isKeyPressed(Keyboard::Z)) {
        dir.y = -1.;
    } else if(Keyboard::isKeyPressed(Keyboard::S)) {
        dir.y = 1.;
    }

    if(Keyboard::isKeyPressed(Keyboard::Q)) {
        dir.x = -1.;
    } else if(Keyboard::isKeyPressed(Keyboard::D)) {
        dir.x = 1.;
    }

    /* set the right angle */
    if(dir.x > 0.5 && dir.y > 0.5) {
        angle = 45.;
    } else if(dir.x > 0.5 && dir.y < -0.5) {
        angle = -45.;
    } else if(dir.x < -0.5 && dir.y < -0.5) {
        angle = 225.;
    } else if(dir.x < -0.5 && dir.y > 0.5) {
        angle = 180.-45.;
    } else if(dir.x > 0.5) {
        angle = 0.;
    } else if(dir.x < -0.5) {
        angle = 180.;
    } else if(dir.y > 0.5) {
        angle = 90.;
    } else if(dir.y < -0.5) {
        angle = -90.;
    }

    /* move at a constant speed */
    if(abs(dir.x) > 0.5 && abs(dir.y) > 0.5) {
        dir.x /= _root2;
        dir.y /= _root2;
    }

    dir.x *= _speed*elapsedTime;
    dir.y *= _speed*elapsedTime;

    /* update position and angle */
    move(dir);
    setRotation(angle);

    /* manager firing */
    if(Mouse::isButtonPressed(Mouse::Left)) {
        if(!_fire) {
            _fire = true;
            createBullets();
            _clock.restart();
        } else {
            if(_clock.getElapsedTime().asSeconds() > 0.05) {
                createBullets();
                _clock.restart();
            }
        }
    } else if(_fire) {
        _fire = false;
    }

}

/*----------------------------------------------------------------------------*/
void Player::collideWidth(const Entity& entity) {
    if(entity.type() != Entity::Bullet) {
        _alive = false;
    }

    cout << "test Player" << endl;
}

/*----------------------------------------------------------------------------*/
void Player::createBullets() {

    Vector2f pos = getPosition();
    Vector2f dir = static_cast<Vector2f>(Mouse::getPosition(_input));
    dir -= pos;

    /* normalize the vector */
    double len = sqrt(dir.x*dir.x + dir.y*dir.y);
    dir.x /= len;
    dir.y /= len;

    Vector2f center(pos);
    center.x += dir.x * 100.;
    center.y += dir.y * 100.;

    /* orthogonal vector, used to create a gap between the bullets */
    Vector2f ortho(dir.y, -dir.x);
    ortho.x *= 10.;
    ortho.y *= 10.;

    Vector2f posA(center - ortho);
    Vector2f posB(center + ortho);

    /* bullets creation */

    class Bullet* bulletA = new class Bullet(_textureManager, _entityManager, posA, dir);
    class Bullet* bulletB = new class Bullet(_textureManager, _entityManager, posB, dir);

    _entityManager.addEntity(bulletA);
    _entityManager.addEntity(bulletB);
}
