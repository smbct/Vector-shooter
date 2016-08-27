/*!
 * \file Spring.cpp
 * \brief Spring and point mass classes
 * \author smbct
 * \date 08.23.2016
 */

#include "Spring.hpp"
#include "Utils.hpp"

#include <iostream>

using namespace sf;
using namespace std;


/******************************************************************************/
/*------------------------------class PointMass-------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
PointMass::PointMass(Vector3f ppos, double pinvMass) :
pos(ppos),
velocity(0., 0., 0.),
invMass(pinvMass),
acceleration(0., 0., 0.),
damping(0.98)
{

}

/*----------------------------------------------------------------------------*/
void PointMass::applyForce(Vector3f force) {
    acceleration.x += force.x * invMass;
    acceleration.y += force.y * invMass;
    acceleration.z += force.z * invMass;
}

/*----------------------------------------------------------------------------*/
void PointMass::increaseDamping(double factor) {
    damping *= factor;
}

/*----------------------------------------------------------------------------*/
void PointMass::update(double elapsedTime) {

    velocity += acceleration;

    pos += velocity;

    if(Utils::lengthSq(velocity) < 1e-6) {
        velocity = Vector3f(0., 0., 0.);
    }

    velocity.x *= damping;
    velocity.y *= damping;
    velocity.z *= damping;

    damping = 0.98;
}

/*----------------------------------------------------------------------------*/
sf::Vector2f PointMass::project(sf::Vector2f size) {
    double factor = (pos.z+2000.)/2000.;
    Vector2f res;
    res.x = (pos.x - size.x/2.)*factor + size.x/2.;
    res.y = (pos.y - size.y/2.)*factor + size.y/2.;
    return res;
}



/******************************************************************************/
/*------------------------------class Spring----------------------------------*/
/******************************************************************************/


/*----------------------------------------------------------------------------*/
Spring::Spring(PointMass& pend1, PointMass& pend2, double pstiffness, double pdamping) :
end1(pend1),
end2(pend2),
stiffness(pstiffness),
damping(pdamping)
{
    Vector3f delta = end1.pos-end2.pos;
    targetLength = Utils::length(delta)*0.95;

}


/*----------------------------------------------------------------------------*/
void Spring::update() {

    Vector3f delta = end1.pos - end2.pos;

    double length = Utils::length(delta);

    if(length > targetLength) {
        delta.x = (delta.x/length)*(length-targetLength);
        delta.y = (delta.y/length)*(length-targetLength);
        delta.z = (delta.z/length)*(length-targetLength);

        Vector3f deltaVel = end2.velocity - end1.velocity;
        Vector3f force(stiffness*delta.x-deltaVel.x*damping, stiffness*delta.y-deltaVel.y*damping, stiffness*delta.z-deltaVel.z*damping);

        end1.applyForce(-force);
        end2.applyForce(force);
    }

}
