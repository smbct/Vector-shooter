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

    public:

        /*!
         * \brief detect a collision between two entities
         * \param left one of the entity
         * \param right the other entity
         * \return true if the two entities collide
         */
        static bool collision(const Entity& left, const Entity& right);

    protected:
        double _radius;
        bool _alive;

};


#endif /* ENTITY_HPP */
