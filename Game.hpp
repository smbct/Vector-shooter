/*!
 * \file Game.hpp
 * \brief Game class definition
 * \author Samuel Buchet
 * \date 08.09.2016
 */

 #ifndef GAME_HPP
 #define GAME_HPP

#include <SFML/Graphics.hpp>

#include "TextureManager.hpp"
#include "EntityManager.hpp"
#include "PlayerController.hpp"

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
         * \brief manage game loop : event, game logic, drawing
         */
        void loop(double elapsedTime);

        /*!
         * \brief draw the game
         */
        void draw();

    private:
        sf::RenderWindow _window;
        TextureManager _textureManager;
        EntityManager _entityManager;
        PlayerController _playerController;


        sf::Clock _clock;
        const double _timeStep;

};

 #endif /* GAME_HPP */