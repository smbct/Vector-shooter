/*!
* \file ParticleManager.hpp
* \brief particle manager
* \author smbct
* \date 08.17.2016
*/

#ifndef PARTICLE_MANAGER_HPP
#define PARTICLE_MANAGER_HPP

#include "Particle.hpp"
#include "SFML/Graphics.hpp"

class CircularParticleArray {

    public:

        CircularParticleArray(int capacity);

        int& start();
        int& count();

        Particle& operator[](int i);

        ~CircularParticleArray();

    private:
        int _start;
        int _count;
        int _capacity;

        Particle* _list;

};

class ParticleManager {

    public:
        ParticleManager(int capacity);
        void update(double elapsedTime);
        void draw(sf::RenderWindow& window);

    private:
        CircularParticleArray _particleList;

};

#endif /* PARTICLE_MANAGER_HPP */
