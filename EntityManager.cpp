/*!
 * \file EntityManager.cpp
 * \brief EntityManager class implementation
 * \author Samuel Buchet
 * \date 08.10.2016
 */

#include "EntityManager.hpp"

/*----------------------------------------------------------------------------*/
EntityManager::EntityManager() {

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
    _entities.push_back(entity);
}

/*----------------------------------------------------------------------------*/
void EntityManager::addPlayer(Entity* player) {
    addEntity(player);
    _player = player;
}

/*----------------------------------------------------------------------------*/
void EntityManager::update() {

}

/*----------------------------------------------------------------------------*/
EntityManager::~EntityManager() {
    for(auto entity : _entities) {
        delete entity;
    }
}
