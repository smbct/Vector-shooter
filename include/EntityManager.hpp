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
#include "ParticleManager.hpp"
#include "WarpingGrid.hpp"

#include "QuadTree.hpp"

/*!
 * \class EntityManager
 * \brief manage all entites of the game
 */
class EntityManager {

    public:
        EntityManager(const sf::Vector2f& worldSize, TextureManager& textureManager);

        /*!
         * \brief draw all entities
         * \param renderer the window to draw in
         */
        void drawEntities(sf::RenderTarget& renderer);

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
         * \brief return the texture manager
         */
        TextureManager& getTextureManager();

        /*!
         * \brief return the particle manager
         */
        ParticleManager& getParticleManager();

        /*!
         * \brief return the player
         */
        Entity& getPlayer();

        /*!
         * \brief return entities around a position
         */
        void getNearbyEntities(sf::Vector2f pos, double radius, std::list<Entity*>& entities);

        std::list<Entity*>& getBlackHoles();

        Grid& getGrid();

        /*!
         * \brief return the world bounds
         */
        sf::FloatRect& getWorldBound();

        /*!
         * \brief destructor, erase all entities
         */
        ~EntityManager();

        int count();

    private:

        void collisions();

        void entityUpdate(double elapsedTime);

        void removeDead();

    private:
        sf::FloatRect _worldRect;
        TextureManager& _textureManager;
        std::list<Entity*> _entities;
        std::queue<Entity*> _added;
        Entity* _player;
        std::list<Entity*> _blackHoles;
        ParticleManager _particleManager;
        Grid _grid;
        int _count;

        QuadTree _qtree;

};


#endif /* ENTITY_MANAGER_HPP */
