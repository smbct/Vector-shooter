/*!
* \file Particle.hpp
* \brief class definitions for particles
* \author smbct
* \date 08.17.2016
*/

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class ParticleState {

    public:

        enum Type {None, Enemy, Bullet, IgnoreGravity};

        sf::Vector2f velocity;
        Type type;
        float lengthMultiplier;

};

class Particle {

    public:
        Particle();

    public:
        sf::Texture const * texture;
        sf::Vector2f pos;
        float orientation;

        sf::Vector2f scale;

        sf::Color color;
        float duration;
        float percentLife;
        ParticleState state;

};



#endif /* PARTICLE_HPP */
