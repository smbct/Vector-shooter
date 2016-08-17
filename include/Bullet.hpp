/*!
* \file Bullet.hpp
* \brief Bullet class definition
* \author smbct
* \date 08.11.2016
*/

#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entity.hpp"
#include "TextureManager.hpp"

/*!
 * \class Bullet
 * \brief bullet, the player's weapon
 */
class Bullet : public Entity {

    public:
        Bullet(EntityManager& entityManager, sf::Vector2f pos, sf::Vector2f dir);

        void collideWith(const Entity& entity);

        void update(double elapsedTime);

    private:
        void createExplosion();

        const double _speed;


};

#endif /* BULLET_HPP */
