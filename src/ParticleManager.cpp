/*!
* \file ParticleManager.cpp
* \brief particle manager
* \author smbct
* \date 08.17.2016
*/

#include "ParticleManager.hpp"

/******************************************************************************/
/*-----------------------class CircularParticleArray--------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
CircularParticleArray::CircularParticleArray(int capacity) :
_capacity(capacity)
{
    _list = new Particle[capacity];
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
Particle& CircularParticleArray::operator[](int i) {
    return _list[(_start+i)%_capacity];
}

/*----------------------------------------------------------------------------*/
CircularParticleArray::~CircularParticleArray() {
    delete[] _list;
}



/******************************************************************************/
/*-----------------------------class ParticleManager--------------------------*/
/******************************************************************************/



/*----------------------------------------------------------------------------*/
ParticleManager::ParticleManager(int capacity) :
_particleList(capacity)
{

}

/*----------------------------------------------------------------------------*/
void ParticleManager::update(double elapsedTime) {

}

/*----------------------------------------------------------------------------*/
void ParticleManager::draw(sf::RenderWindow& window) {

    for(int i = 0; i < _particleList.count(); i++) {

        
    }

}
