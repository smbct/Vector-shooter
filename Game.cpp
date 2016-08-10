/*!
 * \file Game.cpp
 * \brief implementation of Game
 * \author Samuel Buchet
 * \date 08.09.2016
 */

#include "Game.hpp"

#include <iostream>

using namespace std;
using namespace sf;

/*----------------------------------------------------------------------------*/
Game::Game() :
_window(VideoMode(1024, 768), "shooter"),
_playerController(_window),
_timeStep((1./60.)*1e-3)
{
    Entity* player = new Entity(_textureManager.getTexture("Art/Player.png"), 18);
    _entityManager.addPlayer(player);
    _playerController.setPlayerEntity(player);
}

/*----------------------------------------------------------------------------*/
 void Game::run() {

    double remainingTime = 0.;
    unsigned int nbFrame = 0;

    while(_window.isOpen()) {

        /* manage fixed time step */
        double elapsedTime = _clock.getElapsedTime().asSeconds();
        _clock.restart();

        elapsedTime += remainingTime;
        nbFrame = static_cast<unsigned int>(elapsedTime/elapsedTime);
        remainingTime = elapsedTime - static_cast<double>(nbFrame)*_timeStep;

        /* simulate the game with a fixed time step */
        for(unsigned int done = 1; done <= nbFrame; done ++) {
            loop(_timeStep);
        }

        /* display the game */
        draw();

        _window.display();

    }

}

/*------------------------Private methods-------------------------------------*/

/*----------------------------------------------------------------------------*/
void Game::loop(double elapsedTime) {

    /* manage window events */

    Event event;

    while(_window.pollEvent(event)) {

        if(event.type == sf::Event::Closed) {
            _window.close();
        }

        if(event.type == sf::Event::KeyPressed && event.key.code == Keyboard::Escape) {
            _window.close();
        }

    }

    /* controller update */
    _playerController.update(elapsedTime);

    /* entities event */
    _entityManager.update();
}


/*----------------------------------------------------------------------------*/
void Game::draw() {

    _window.clear();

    /* draw all entities */
    _entityManager.drawEntities(_window);
}
