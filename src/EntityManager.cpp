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
_particleManager(1024*20, *this),
_grid(worldSize, sf::Vector2f(25, 25))
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
list<Entity*>& EntityManager::getBlackHoles() {
    return _blackHoles;
}

/*----------------------------------------------------------------------------*/
FloatRect& EntityManager::getWorldBound() {
    return _worldRect;
}

/*----------------------------------------------------------------------------*/
void EntityManager::drawEntities(RenderTarget& renderer) {

    /* draw the warping grid */
    _grid.draw(renderer, Vector2f(_worldRect.width, _worldRect.height));

    /* draw particles */
    _particleManager.draw(renderer);

    /* draw entities */
    for(auto entity : _entities) {
        renderer.draw(*entity);
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

    _particleManager.update(elapsedTime);

    _grid.update(elapsedTime);

    collisions();
    removeDead();

    /* add created entities */
    while(!_added.empty()) {
        Entity* created = _added.front();
        _added.pop();
        _entities.push_back(created);
        if(created->type() == Entity::Player) {
            _player = created;
        } else if(created->type() == Entity::BlackHole) {
            _blackHoles.push_back(created);
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

    /* remove in black hole list */
    auto it = _blackHoles.begin(), toRem = _blackHoles.end();
    bool rem = false;
    while(it != _blackHoles.end()) {
        if(!(*it)->alive()) {
            rem = true;
            toRem = it;
        }

        it ++;

        if(rem) {
            _entities.erase(toRem); /* remove from the list */
            rem = false;
        }
    }

    it = _entities.begin();
    toRem = _entities.end();
    rem = false;

    /* remove in entity list */
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
