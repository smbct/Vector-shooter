/*!
* \file Player.hpp
* \brief Player class definition
* \author smbct
* \date 08.10.2016
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "TextureManager.hpp"

/* forward declaration */
class EntityManager;

/*!
 * \class Player
 * \brief player entity
 */
class Player : public Entity {

    public:
        Player(TextureManager& textureManager, EntityManager& entityManager, sf::Window& input);

        void update(double elapsedTime);

        virtual void collideWidth(const Entity& entity);

    private:
        void createBullets();

    private:
        sf::Window& _input;
        TextureManager& _textureManager;
        const double _speed;
        const double _root2;
        sf::Clock _clock;
        bool _fire;

};

#endif
