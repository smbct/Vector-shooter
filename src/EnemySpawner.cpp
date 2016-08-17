/*!
* \file EnemySpawner.cpp
* \brief Enemy spawner class implementation
* \author smbct
* \date 08.16.2016
*/

#include "EnemySpawner.hpp"
#include "Enemy.hpp"
#include "BlackHole.hpp"

/*----------------------------------------------------------------------------*/
EnemySpawner::EnemySpawner(EntityManager& entityManager, ScoreManager& scoreManager) :
_entityManager(entityManager),
_scoreManager(scoreManager)
{

    Seeker* seeker = new Seeker(_entityManager, _scoreManager);
    seeker->setPosition(600., 600.);
    _entityManager.addEntity(seeker);

    Wanderer* wanderer = new Wanderer(_entityManager, _scoreManager);
    wanderer->setPosition(800., 600.);
    _entityManager.addEntity(wanderer);

    BlackHole* blackHole = new BlackHole(_entityManager);
    blackHole->setPosition(130., 450.);
    _entityManager.addEntity(blackHole);

}
