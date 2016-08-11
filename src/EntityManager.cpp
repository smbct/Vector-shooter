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
EntityManager::EntityManager(const sf::Vector2f& worldSize) :
_worldRect(Vector2f(0., 0.), worldSize)
{

}

/*----------------------------------------------------------------------------*/
void EntityManager::drawEntities(sf::RenderWindow& window) {
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

            if(entity != other && Entity::collision(*entity, *other)) {
                entity->collideWith(*other);
                other->collideWith(*entity);
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
void EntityManager::checkBoundary(Entity* entity) {
    if(!_worldRect.intersects(entity->getGlobalBounds()) && entity->type() != Entity::Player) {
        entity->kill();
    }

}

/*----------------------------------------------------------------------------*/
void EntityManager::entityUpdate(double elapsedTime) {
    for(auto entity : _entities) {
        entity->update(elapsedTime);
        /* make sure the entity is still inside the playground */
        checkBoundary(entity);
    }
}

/*----------------------------------------------------------------------------*/
EntityManager::~EntityManager() {
    for(auto entity : _entities) {
        delete entity;
    }
}
