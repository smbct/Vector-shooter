/*!
 * \file EntityManager.hpp
 * \brief EntityManager class definition
 * \author smbct
 * \date 08.10.2016
 */

#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <list>

#include "Entity.hpp"

/*!
 * \class EntityManager
 * \brief manage all entites of the game
 */
class EntityManager {

    public:
        EntityManager();

        /*!
         * \brief draw all entities
         * \param renderer the window to draw in
         */
        void drawEntities(sf::RenderWindow& renderer);

        /*!
         * \brief add a new entity
         * \param entity the new entity
         */
        void addEntity(Entity* entity);

        /*!
         * \brief add the entity which will be played
         * \param entity the player entity
         */
        void addPlayer(Entity* player);

        /*!
         * \brief update all entities
         */
        void update(double elapsedTime);

        /*!
         * \brief destructor, erase all entities
         */
        ~EntityManager();

    private:

        void collisions();

        void entityUpdate(double elapsedTime);

    private:
        std::list<Entity*> _entities;
        Entity* _player;
        std::list<Entity*> _enemies;

};


#endif /* ENTITY_MANAGER_HPP */
