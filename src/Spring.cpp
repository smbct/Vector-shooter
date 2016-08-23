/*!
 * \file Spring.cpp
 * \brief Spring and point mass classes
 * \author smbct
 * \date 08.23.2016
 */

#include "Spring.hpp"
#include "Utils.hpp"

using namespace sf;


/******************************************************************************/
/*------------------------------class PointMass-------------------------------*/
/******************************************************************************/

/*----------------------------------------------------------------------------*/
PointMass::PointMass(Vector3f ppos, double pinvMass) :
pos(ppos),
invMass(pinvMass),
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
    Vector3f deltaAcc = acceleration;
    deltaAcc.x *= elapsedTime*elapsedTime;
    deltaAcc.y *= elapsedTime*elapsedTime;
    deltaAcc.z *= elapsedTime*elapsedTime;

    velocity += deltaAcc;

    Vector3f delta = velocity;
    delta.x *= elapsedTime;
    delta.y *= elapsedTime;
    delta.z *= elapsedTime;
    pos += delta;

    if(Utils::lengthSq(velocity) < 1e-6) {
        velocity = Vector3f(0., 0., 0.);
    }

    velocity.x *= damping*elapsedTime;
    velocity.y *= damping*elapsedTime;

    damping = 0.98;
}



/******************************************************************************/
/*------------------------------class Spring----------------------------------*/
/******************************************************************************/


/*----------------------------------------------------------------------------*/
Spring::Spring(PointMass pend1, PointMass pend2, double pstiffness, double pdamping) :
end1(pend1),
end2(pend2),
stiffness(pstiffness),
damping(pdamping)
{
    Vector3f delta = end1.pos-end2.pos;
    targetLength = Utils::length(delta);

}


/*----------------------------------------------------------------------------*/
void Spring::update(double elapsedTime) {

    Vector3f delta = end1.pos - end2.pos;

    double length = Utils::length(delta);

    if(length > targetLength) {
        delta.x /= length*(length-targetLength);
        delta.y /= length*(length-targetLength);
        delta.z /= length*(length-targetLength);

        Vector3f deltaVel = end2.velocity - end1.velocity;

    }

}
