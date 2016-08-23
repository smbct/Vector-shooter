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

    /* off screen rendering */
    _blurHShader.loadFromFile("Shaders/blurH.frag", Shader::Fragment);
    _blurVShader.loadFromFile("Shaders/blurV.frag", Shader::Fragment);
    _texture1.create(_window.getSize().x, _window.getSize().y);
    _texture2.create(_window.getSize().x, _window.getSize().y);
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

    _texture1.clear();

    /* draw all entities */
    _entityManager.drawEntities(_texture1);

    /* update and draw the cursor */
    sf::Vector2i mouse = Mouse::getPosition(_window);
    _cursor.setPosition(static_cast<float>(mouse.x), static_cast<float>(mouse.y));

    _texture1.draw(_cursor);
    _texture1.display();

    /* copy the initial rendering into a texture */
    _screenTexture = Texture(_texture1.getTexture());

    /* horizontal blur */
    Sprite sprite(_texture1.getTexture());
    _blurHShader.setParameter("texture", _texture1.getTexture());
    _blurHShader.setParameter("width", static_cast<float>(_window.getSize().x));
    _texture2.clear();
    _texture2.draw(sprite, &_blurHShader);
    _texture2.display();

    /* vertical blur */
    _texture1.clear();
    sprite.setTexture(_texture2.getTexture());
    _blurVShader.setParameter("texture", _texture2.getTexture());
    _blurVShader.setParameter("height", static_cast<float>(_window.getSize().y));
    _texture1.draw(sprite, &_blurVShader);
    _texture1.display();

    /* final rendering */
    sprite.setTexture(_screenTexture);
    Sprite sprite2(_texture1.getTexture());
    _window.clear();
    BlendMode mode(BlendMode::One, BlendMode::One);
    _window.draw(sprite, RenderStates(mode));
    _window.draw(sprite2, RenderStates(mode));
}
