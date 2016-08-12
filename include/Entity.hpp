/*!
* \file Entity.hpp
* \brief Entity class definition, managing interacting elements
* \author smbct
* \date 08.09.2016
*/
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

/* forward declaration */
class EntityManager;

/*!
 * \class Entity
 * \brief interacting element of the game, base class
 */
class Entity : public sf::Sprite {

    public:

        enum Type {None, Player, Bullet, Enemy, Seeker, Wanderer, BlackHole};

        /*!
         * \brief constructor
         */
        Entity(EntityManager& entityManager, const sf::Texture& texture, double radius);

        virtual void update(double elapsedTime);

        virtual void collideWith(const Entity& entity);

        /*!
         * \brief entity alive or not, if dead, should be removed
         * \return true if the entity is alive
         */
        bool alive() const;

        /*!
         * \brief translate the entity
         * \param dir the translation vector
         */
        void move(const sf::Vector2f& dir);

        /*!
         * \brief kimm the entities
         */
        void kill();

        /*!
         * \brief get the type of the entity
         * \return the type of the entity
         */
        Type type() const;

    public:

        /*!
         * \brief detect a collision between two entities
         * \param left one of the entity
         * \param right the other entity
         * \return true if the two entities collide
         */
        static bool collision(const Entity& left, const Entity& right);

    protected:
        EntityManager& _entityManager;
        double _radius;
        bool _alive;
        Type _type;

};


#endif /* ENTITY_HPP */
