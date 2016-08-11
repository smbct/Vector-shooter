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
        Bullet(TextureManager& textureManager, EntityManager& entityManager, sf::Vector2f pos, sf::Vector2f dir);
        void update(double elapsedTime);

        void collideWidth(const Entity& entity);

    private:
        const double _speed;
        sf::Vector2f _dir;


};

#endif /* BULLET_HPP */
