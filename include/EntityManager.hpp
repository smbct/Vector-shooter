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
#include "Particles.hpp"

/*!
 * \class EntityManager
 * \brief manage all entites of the game
 */
class EntityManager {

    public:
        EntityManager(const sf::Vector2f& worldSize);

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
         * \brief return the player
         */
        Entity& getPlayer();

        /*!
         * \brief return entities around a position
         */
        void getNearbyEntities(sf::Vector2f pos, double radius, std::list<Entity*>& entities);

        /*!
         * \brief return the world bounds
         */
        sf::FloatRect& getWorldBound();

        /*!
         * \brief destructor, erase all entities
         */
        ~EntityManager();

    private:

        void collisions();

        void entityUpdate(double elapsedTime);

        void removeDead();

        void checkBoundary(Entity* entity);

    private:
        sf::FloatRect _worldRect;
        ParticleManager _particleManager;
        std::list<Entity*> _entities;
        std::queue<Entity*> _added;
        Entity* _player;
        std::list<Entity*> _enemies;

};


#endif /* ENTITY_MANAGER_HPP */
