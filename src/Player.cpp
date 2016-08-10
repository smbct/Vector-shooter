/*!
* \file Player.cpp
* \brief Player class implementation
* \author smbct
* \date 08.10.2016
*/

#include "Player.hpp"
#include "EntityManager.hpp"

#include <iostream>

using namespace sf;
using namespace std;

/*----------------------------------------------------------------------------*/
Player::Player(TextureManager& textureManager, EntityManager& entityManager, sf::Window& input) :
Entity(entityManager, textureManager.getTexture("Art/Player.png"), 20),
_input(input),
_speed(600.),
_root2(sqrt(2))
{

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

}
