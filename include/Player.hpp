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

    private:
        sf::Window& _input;
        const double _speed;
        const double _root2;

};

#endif