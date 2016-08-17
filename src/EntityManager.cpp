/*!
 * \file EntityManager.cpp
 * \brief EntityManager class implementation
 * \author smbct
 * \date 08.10.2016
 */

#include "EntityManager.hpp"

#include <iostream>

using namespace std;
using namespace sf;

/*----------------------------------------------------------------------------*/
EntityManager::EntityManager(const sf::Vector2f& worldSize, TextureManager& textureManager) :
_worldRect(Vector2f(0., 0.), worldSize),
_textureManager(textureManager),
_particleManager(1024*20)
{

}

/******************************************************************************/
/*-----------------------------getter methods---------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
ParticleManager& EntityManager::getParticleManager() {
    return _particleManager;
}

/*----------------------------------------------------------------------------*/
TextureManager& EntityManager::getTextureManager() {
    return _textureManager;
}

/*----------------------------------------------------------------------------*/
Entity& EntityManager::getPlayer() {
    return *_player;
}

/*----------------------------------------------------------------------------*/
void EntityManager::getNearbyEntities(sf::Vector2f pos, double radius, list<Entity*>& entities) {

    Vector2f vec;
    for(Entity* entity : _entities) {
        vec = entity->getPosition() - pos;
        if(vec.x*vec.x + vec.y*vec.y < radius*radius) {
            entities.push_back(entity);
        }
    }
}

/*----------------------------------------------------------------------------*/
FloatRect& EntityManager::getWorldBound() {
    return _worldRect;
}

/*----------------------------------------------------------------------------*/
void EntityManager::drawEntities(sf::RenderWindow& window) {

    /* draw the particles */
    /* TODO change sort and blend mode */
    _particleManager.draw(window);

    /* draw the entities */
    for(auto entity : _entities) {
        window.draw(*entity);
    }
}

/******************************************************************************/
/*--------------------------------add method----------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
void EntityManager::addEntity(Entity* entity) {
    _added.push(entity);
}


/******************************************************************************/
/*---------------------------------updating-----------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
void EntityManager::update(double elapsedTime) {

    entityUpdate(elapsedTime);

    _particleManager.update(elapsedTime, _worldRect);

    collisions();
    removeDead();

    /* add created entities */
    while(!_added.empty()) {
        Entity* created = _added.front();
        _added.pop();
        _entities.push_back(created);
        if(created->type() == Entity::Player) {
            _player = created;
        }
    }

}

/*----------------------------------------------------------------------------*/
void EntityManager::collisions() {

    /* dirty test */
    /* TODO : better test, less comparisons */
    for(Entity* entity : _entities) {
        for(Entity* other : _entities) {
            if(entity != other) {
                if(entity->alive() && other->alive() && Entity::collision(*entity, *other)) {
                    entity->collideWith(*other);
                    other->collideWith(*entity);
                }
            }
        }
    }
}

/*----------------------------------------------------------------------------*/
void EntityManager::removeDead() {

    auto it = _entities.begin(), toRem = _entities.end();
    bool rem = false;

    while(it != _entities.end()) {
        if(!(*it)->alive()) {
            rem = true;
            toRem = it;
        }

        it ++;

        if(rem) {
            delete *toRem; /* delete the entity */
            _entities.erase(toRem); /* remove from the list */
            rem = false;
        }
    }
}

/*----------------------------------------------------------------------------*/
void EntityManager::entityUpdate(double elapsedTime) {
    for(auto entity : _entities) {
        entity->update(elapsedTime);
    }
}

/*----------------------------------------------------------------------------*/
EntityManager::~EntityManager() {
    for(auto entity : _entities) {
        delete entity;
    }
}
