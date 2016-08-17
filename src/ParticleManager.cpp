/*!
* \file ParticleManager.cpp
* \brief particle manager
* \author smbct
* \date 08.17.2016
*/

#include "ParticleManager.hpp"
#include "Utils.hpp"
#include "EntityManager.hpp"

#include <iostream>

using namespace sf;
using namespace std;

/******************************************************************************/
/*-----------------------class CircularParticleArray--------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
CircularParticleArray::CircularParticleArray(int capacity) :
_start(0),
_count(0),
_capacity(capacity)
{
    _list = new Particle*[_capacity];

    for(int ind = 0; ind < _capacity; ind++) {
        _list[ind] = new Particle;
    }

}

/*----------------------------------------------------------------------------*/
int& CircularParticleArray::start() {
    return _start;
}

/*----------------------------------------------------------------------------*/
int& CircularParticleArray::count() {
    return _count;
}

/*----------------------------------------------------------------------------*/
int CircularParticleArray::capacity() {
    return _capacity;
}

/*----------------------------------------------------------------------------*/
void CircularParticleArray::swap(int ind1, int ind2) {

    ind1 = (ind1+_start)%_capacity;
    ind2 = (ind2+_start)%_capacity;

    Particle* temp = _list[ind1];
    _list[ind1] = _list[ind2];
    _list[ind2] = temp;

}

/*----------------------------------------------------------------------------*/
Particle& CircularParticleArray::operator[](int i) {
    return *_list[(_start+i)%_capacity];
}

/*----------------------------------------------------------------------------*/
CircularParticleArray::~CircularParticleArray() {

    /* remove each particle */
    for(int ind = 0; ind < _capacity; ind ++) {
        delete _list[ind];
    }

    delete[] _list;
}



/******************************************************************************/
/*-----------------------------class ParticleManager--------------------------*/
/******************************************************************************/



/*----------------------------------------------------------------------------*/
ParticleManager::ParticleManager(int capacity, EntityManager& entityManager) :
_particleList(capacity),
_entityManager(entityManager)
{

}

/*----------------------------------------------------------------------------*/
void ParticleManager::createParticle(const sf::Texture& texture, sf::Vector2f pos, sf::Color tint, double duration, sf::Vector2f scale, ParticleState state, double theta) {

    Particle* particle;
    if(_particleList.count() == _particleList.capacity()) {
        particle = &_particleList[0];
        _particleList.start() ++;
    } else {
        particle = &_particleList[_particleList.count()];
        _particleList.count() ++;
    }

    /* particle creation */
    particle->texture = &texture;
    particle->pos = pos;
    particle->color = tint;

    particle->duration = duration;
    particle->percentLife = 1.;
    particle->scale = scale;
    particle->orientation = theta;
    particle->state = state;

}

/*----------------------------------------------------------------------------*/
void ParticleManager::update(double elapsedTime) {
    int removalCount = 0;

    for(int ind = 0; ind < _particleList.count(); ind ++) {
        Particle& particle = _particleList[ind];
        updateParticle(particle, elapsedTime);
        particle.percentLife -= elapsedTime / particle.duration;

        /* particle shift */
        _particleList.swap(ind - removalCount, ind);

        if(particle.percentLife < 0) {
            removalCount ++;
        }
    }
    _particleList.count() -= removalCount;
}

/*----------------------------------------------------------------------------*/
void ParticleManager::updateParticle(Particle& particle, double elapsedTime) {


    if(particle.pos.x < 0) {
        particle.state.velocity.x = abs(particle.state.velocity.x);
    } else if (particle.pos.x > _entityManager.getWorldBound().width) {
        particle.state.velocity.x = -abs(particle.state.velocity.x);
    }
    if (particle.pos.y < 0) {
        particle.state.velocity.y = abs(particle.state.velocity.y);
    } else if (particle.pos.y > _entityManager.getWorldBound().height) {
        particle.state.velocity.y = -abs(particle.state.velocity.y);
    }

    Vector2f delta = particle.state.velocity;
    delta.x *= elapsedTime;
    delta.y *= elapsedTime;

    particle.pos += delta;

    particle.orientation = Utils::toDegree(Utils::vectorToAngle(particle.state.velocity));

    float speed = sqrt(particle.state.velocity.x*particle.state.velocity.x + particle.state.velocity.y*particle.state.velocity.y);
    double alpha = min(particle.percentLife*2., speed*1.);
    alpha = min(1., alpha);
    alpha *= alpha;

    particle.color.a = /*static_cast<int>(255. * alpha)*/particle.percentLife*255;
    particle.scale.x = particle.state.lengthMultiplier * /*min(min(1., 0.2*speed+0.1), alpha)*/particle.percentLife;

    if(abs(particle.state.velocity.x) + abs(particle.state.velocity.y) < 1e-9) {
        particle.state.velocity = Vector2f(0., 0.);
    }

    particle.state.velocity.x *= 0.97;
    particle.state.velocity.y *= 0.97;

    /* particles affected by gravity */
    list<Entity*>& blackHoles = _entityManager.getBlackHoles();

    for(Entity* blackHole : blackHoles) {

        Vector2f delta = blackHole->getPosition() - particle.pos;
        double distance = Utils::length(delta);
        delta.x /= distance;
        delta.y /= distance;

        // particle.state.velocity += Vector2f(1000., 1000.)

    }

}

/*----------------------------------------------------------------------------*/
void ParticleManager::draw(sf::RenderWindow& renderer) {

    for(int ind = 0; ind < _particleList.count(); ind++) {

        Particle& particle = _particleList[ind];

        /* set the sprite properties from the particle */

        Sprite sprite(*(particle.texture));

        Vector2f origin(particle.texture->getSize().x/2., particle.texture->getSize().y/2.);
        sprite.setOrigin(origin);
        sprite.setPosition(particle.pos);
        sprite.setRotation(particle.orientation);
        sprite.setColor(particle.color);
        sprite.setScale(particle.scale);

        /* draw the sprite */
        renderer.draw(sprite);

    }

}
