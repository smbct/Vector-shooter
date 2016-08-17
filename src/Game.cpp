/*!
 * \file Game.cpp
 * \brief implementation of Game
 * \author smbct
 * \date 08.09.2016
 */

#include "Game.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "BlackHole.hpp"

#include <iostream>

using namespace std;
using namespace sf;

/*----------------------------------------------------------------------------*/
Game::Game() :
_window(VideoMode(1024, 768), "shooter"),
_entityManager(static_cast<Vector2f>(_window.getSize()), _textureManager),
_enemySpawner(_entityManager, _score),
_timeStep(1./60.),
_remainingTime(0.),
_cursor(_textureManager.getTexture("Art/Pointer.png"))
{

    /* init random generator */
    srand(time(0));

    /* create the player */
    Player* player = new Player(_entityManager, _window);
    player->setPosition(150., 150.);
    _entityManager.addEntity(player);

    /* make the default cursor invisible */
    _window.setMouseCursorVisible(false);
    _window.setVerticalSyncEnabled(true);
}

/*----------------------------------------------------------------------------*/
 void Game::run() {

    while(_window.isOpen()) {

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

        /* exec game loop */
        loop();

        /* display the game */
        draw();

        _window.display();

    }

}

/******************************************************************************/
/*------------------------Private methods-------------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
void Game::loop() {

    /* manage fixed time step */
    double elapsedTime = _clock.getElapsedTime().asSeconds();
    _clock.restart();

    elapsedTime += _remainingTime;
    unsigned int nbFrame = static_cast<unsigned int>(elapsedTime/_timeStep);
    _remainingTime = elapsedTime - static_cast<double>(nbFrame)*_timeStep;

    /* simulate the game with a fixed time step */
    for(unsigned int done = 1; done <= nbFrame; done ++) {

        /* entities event */
        _entityManager.update(_timeStep);
    }

    /* display the score */
    // cout << "score : " << _score.score() << endl;

}


/*----------------------------------------------------------------------------*/
void Game::draw() {

    _window.clear();

    /* draw all entities */
    _entityManager.drawEntities(_window);

    /* update and draw the cursor */
    sf::Vector2i mouse = Mouse::getPosition(_window);
    _cursor.setPosition(static_cast<float>(mouse.x), static_cast<float>(mouse.y));
    _window.draw(_cursor);
}
