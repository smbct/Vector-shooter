/*!
* \file EnemySpawner.hpp
* \brief Enemy spawner class definition
* \author smbct
* \date 08.16.2016
*/

#ifndef ENEMY_SPAWNER_HPP
#define ENEMY_SPAWNER_HPP

#include "EntityManager.hpp"
#include "TextureManager.hpp"
#include "ScoreManager.hpp"

/*!
 * \class EnemySpawner
 * \brief manage enemy spwaning
 */
class EnemySpawner {

    public:
        EnemySpawner(EntityManager& entityManager, TextureManager& textureManager, ScoreManager& scoreManager);

    private:
        EntityManager& _entityManager;
        TextureManager& _textureManager;
        ScoreManager& _scoreManager;

};


#endif /* ENEMY_SPAWNER_HPP */
