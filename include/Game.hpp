/*!
 * \file Game.hpp
 * \brief Game class definition
 * \author smbct
 * \date 08.09.2016
 */

 #ifndef GAME_HPP
 #define GAME_HPP

#include <SFML/Graphics.hpp>

#include "TextureManager.hpp"
#include "EntityManager.hpp"
#include "ScoreManager.hpp"
#include "EnemySpawner.hpp"

class Game {

    public:
        /*!
         * \brief constructor
         */
        Game();

        /*!
         * \brief run the game
        */
        void run();

    private:

        /*!
         * \brief manage game loop : event, game logic
         */
        void loop();

        /*!
         * \brief draw the game
         */
        void draw();

    private:
        sf::RenderWindow _window;
        TextureManager _textureManager;
        EntityManager _entityManager;
        ScoreManager _score;
        EnemySpawner _enemySpawner;

        sf::Clock _clock;
        const double _timeStep;
        double _remainingTime;

        sf::Sprite _cursor;

        sf::Shader _blurHShader;
        sf::Shader _blurVShader;
        sf::RenderTexture _texture1;
        sf::RenderTexture _texture2;
        sf::Texture _screenTexture;

};

 #endif /* GAME_HPP */
