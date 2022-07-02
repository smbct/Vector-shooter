/*!
* \file EnemySpawner.cpp
* \brief Enemy spawner class implementation
* \author smbct
* \date 08.16.2016
*/

#include "EnemySpawner.hpp"
#include "Enemy.hpp"
#include "BlackHole.hpp"

#include "Utils.hpp"

#include <iostream>

using namespace std;

/*----------------------------------------------------------------------------*/
EnemySpawner::EnemySpawner(EntityManager& entityManager, ScoreManager& scoreManager) :
_entityManager(entityManager),
_scoreManager(scoreManager),
_inverseSpawnChance(60/*5*/)
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

/*----------------------------------------------------------------------------*/
void EnemySpawner::update() {

  if (_entityManager.getPlayer().alive() && _entityManager.count() < 200/*1000*/)
  {
    if (rand() % int(_inverseSpawnChance) == 0) {
      Seeker* seeker = new Seeker(_entityManager, _scoreManager);
      seeker->setPosition(getSpawnPosition());
      _entityManager.addEntity(seeker);
    }

    if (rand() % int(_inverseSpawnChance) == 0) {
      Wanderer* wanderer = new Wanderer(_entityManager, _scoreManager);
      wanderer->setPosition(getSpawnPosition());
      _entityManager.addEntity(wanderer);
    }
  }

  // slowly increase the spawn rate as time progresses
  if (_inverseSpawnChance > 20/*5*/) {
    _inverseSpawnChance -= 0.005f;
  }

}

/*----------------------------------------------------------------------------*/
sf::Vector2f EnemySpawner::getSpawnPosition() {

  sf::Vector2f pos, delta;

  do
  {

    sf::FloatRect bound = _entityManager.getWorldBound();

    pos = sf::Vector2f(rand()%(int)(bound.width), rand()%(int)(bound.height));

    delta = pos - _entityManager.getPlayer().getPosition();

  } while (Utils::lengthSq(delta) < 250 * 250);

  return pos;
}

/*----------------------------------------------------------------------------*/
void EnemySpawner::reset()
{
  _inverseSpawnChance = 60;
}
