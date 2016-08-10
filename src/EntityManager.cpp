/*!
 * \file EntityManager.cpp
 * \brief EntityManager class implementation
 * \author smbct
 * \date 08.10.2016
 */

#include "EntityManager.hpp"

#include <iostream>

using namespace std;

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

/******************************************************************************/
/*---------------------------------updating-----------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
void EntityManager::update() {

    collisions();

}

/*----------------------------------------------------------------------------*/
void EntityManager::collisions() {

    /* dirty test */
    /* TODO : more beautifull test */
    for(auto entity : _entities) {
        for(auto other : _entities) {

            if(entity != other && Entity::collision(*entity, *other)) {
                cout << "send collision event" << endl;
            }

        }
    }
}

/*----------------------------------------------------------------------------*/
EntityManager::~EntityManager() {
    for(auto entity : _entities) {
        delete entity;
    }
}
