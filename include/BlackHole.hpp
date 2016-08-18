/*!
* \file BlackHole.hpp
* \brief Black hole class definition
* \author smbct
* \date 08.16.2016
*/

#ifndef BLACK_HOLE_HPP
#define BLACK_HOLE_HPP

#include "Entity.hpp"
#include "TextureManager.hpp"

/*!
 * \class BlackHole
 */
class BlackHole : public Entity {

    public:
        BlackHole(EntityManager& entityManager);

        virtual void update(double elapsedTime);

        virtual void collideWith(const Entity& entity);

    private:
        void createExplosion();

        void createSpray();

        unsigned int _life;

        sf::Clock _clock;

        double _sprayAngle;

};

#endif /* BLACK_HOLE_HPP */
