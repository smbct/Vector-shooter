/*!
* \file PlayerController.cpp
* \brief PlayerController class implementation
* \author smbct
* \date 08.10.2016
*/

#include "PlayerController.hpp"
#include <cmath>

#include <iostream>

using namespace std;
using namespace sf;

/*----------------------------------------------------------------------------*/
PlayerController::PlayerController(sf::Window& input) :
_speed(600.),
_root2(sqrt(2.)),
_input(input),
_player(nullptr),
_cursor(nullptr)
{

}

/*----------------------------------------------------------------------------*/
void PlayerController::setPlayerEntity(Entity* entity) {
    _player = entity;
}

/*----------------------------------------------------------------------------*/
void PlayerController::setCursor(sf::Sprite& cursor) {
    _cursor = &cursor;
}

/*----------------------------------------------------------------------------*/
void PlayerController::update(double elapsedTime) {

    sf::Vector2f dir(0., 0.);

    double angle = _player->getRotation();

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

    /* update player position */
    _player->move(dir);
    _player->setRotation(angle);

    /* update cursor position */
    sf::Vector2i mouse = Mouse::getPosition(_input);
    _cursor->setPosition(static_cast<float>(mouse.x), static_cast<float>(mouse.y));

}
