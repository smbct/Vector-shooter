/*!
* \file Entity.hpp
* \brief Entity class definition, managing interacting elements
* \author Samuel Buchet
* \date 08.09.2016
*/
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

/*!
 * \class Entity
 * \brief interacting element of the game, base class
 */
class Entity : public sf::Sprite {

    public:

        /*!
         * \brief constructor
         */
        Entity(const sf::Texture& texture, double radius);

        /*!
         * \brief entity alive or not, if dead, should be removed
         * \return true if the entity is alive
         */
        bool alive();

        /*!
         * \brief translate the entity
         * \param dir the translation vector
         */
        void move(const sf::Vector2f& dir);


    protected:
        double _radius;
        bool _alive;

};


#endif /* ENTITY_HPP */
