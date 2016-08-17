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
        int capacity();

        void swap(int ind1, int ind2);

        Particle& operator[](int i);

        ~CircularParticleArray();

    private:
        int _start;
        int _count;
        int _capacity;

        Particle** _list;

};

class ParticleManager {

    public:
        ParticleManager(int capacity);
        void createParticle(const sf::Texture& texture, sf::Vector2f pos, sf::Color tint, double duration, sf::Vector2f scale, ParticleState state, double theta = 0);
        void update(double elapsedTime, const sf::FloatRect& bound);
        void updateParticle(Particle& particle, double elapsedTime, const sf::FloatRect& world);
        void draw(sf::RenderWindow& renderer);


    private:
        CircularParticleArray _particleList;

};

#endif /* PARTICLE_MANAGER_HPP */
