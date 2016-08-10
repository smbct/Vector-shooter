/*!
 * \file Enemy.cpp
 * \brief Implementation of Enemies
 * \author smbct
 * \date 08.10.2016
 */

#include "Enemy.hpp"



/******************************************************************************/
/*-----------------------------Seeeker class---------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
Seeker::Seeker(TextureManager& textureManager, EntityManager& entityManager) :
Entity(entityManager, textureManager.getTexture("Art/Seeker.png"), 20.)
{
    _type = Entity::Seeker;
}

/*----------------------------------------------------------------------------*/
void Seeker::update(double elapsedTime) {

}


/******************************************************************************/
/*-----------------------------Wanderer class---------------------------------*/
/******************************************************************************/


/*----------------------------------------------------------------------------*/
Wanderer::Wanderer(TextureManager& textureManager, EntityManager& entityManager) :
Entity(entityManager, textureManager.getTexture("Art/Wanderer.png"), 20.)
{
    _type= Entity::Wanderer;
}

/*----------------------------------------------------------------------------*/
void Wanderer::update(double elapsedTime) {

}
