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
#include "ScoreManager.hpp"

class Enemy : public Entity {

    public:
        Enemy(EntityManager& entityManager, const sf::Texture& texture, double radius, ScoreManager& score);

        virtual void collideWith(const Entity& entity);

        virtual void update(double elapsedTime);

    protected:
        ScoreManager& _score;

};

class Seeker : public Enemy {

    public:
        Seeker(TextureManager& textureManager, EntityManager& entityManager, ScoreManager& score);

        virtual void update(double elapsedTime);

    private:
        double _acceleration;

};

class Wanderer : public Enemy {

    public:
        Wanderer(TextureManager& textureManager, EntityManager& entityManager, ScoreManager& score);

        virtual void update(double elapsedTime);

    private:
        const double _acceleration;
        double _dirAngle;
        unsigned int _frame;

};

#endif /* ENEMY_HPP */
