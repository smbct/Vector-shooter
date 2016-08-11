/*!
 * \file EntityManager.hpp
 * \brief EntityManager class definition
 * \author smbct
 * \date 08.10.2016
 */

#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <list>
#include <queue>

#include "Entity.hpp"
#include "Player.hpp"

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

        void removeDead();

    private:
        std::list<Entity*> _entities;
        std::queue<Entity*> _added;
        Entity* _player;
        std::list<Entity*> _enemies;

};


#endif /* ENTITY_MANAGER_HPP */
