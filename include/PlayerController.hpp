/*!
* \file PlayerController.hpp
* \brief PlayerController class definition, moving the player
* \author smbct
* \date 08.10.2016
*/

#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "Entity.hpp"

/*!
 * \class PlayerController
 * \brief control actions of the player
 */
class PlayerController {

    public:
        PlayerController(sf::Window& input);

        /*!
         * \brief set the entity controlled by the player
         */
        void setPlayerEntity(Entity* entity);

        /*!
         * \brief set the cursor to move
         */
        void setCursor(sf::Sprite& cursor);

        /*!
         * \brief update the player
         */
        void update(double elapsedTime);

    private:
        const double _speed;
        const double _root2;
        sf::Window& _input;
        Entity* _player;
        sf::Sprite* _cursor;

};

#endif /* PLAYER_CONTROLLER_HPP */
