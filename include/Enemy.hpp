/*!
 * \file Enemy.hpp
 * \brief Enemies classes
 * \author smbct
 * \date 08.10.2016
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "TextureManager.hpp"

class Seeker : public Entity {

    public:
        Seeker(TextureManager& textureManager, EntityManager& entityManager);

        virtual void update(double elapsedTime);

    private:

};

class Wanderer : public Entity {

    public:
        Wanderer(TextureManager& textureManager, EntityManager& entityManager);

        virtual void update(double elapsedTime);

    private:

};

#endif /* ENEMY_HPP */
