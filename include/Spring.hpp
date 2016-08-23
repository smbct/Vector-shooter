/*!
 * \file Spring.hpp
 * \brief Spring and point mass classes
 * \author smbct
 * \date 08.23.2016
 */

#ifndef SPRING_HPP
#define SPRING_HPP

#include <SFML/Graphics.hpp>

/*!
 * \class PointMass
 * \brief a point with attached mass
 */
class PointMass {

    /* public methods */
    public:

        /*!
         * \brief constructor
         * \param pos position of the point
         * \param invMass inverse of the mass
         */
        PointMass(sf::Vector3f ppos, double pinvMass);

        /*!
         * \brief apply a force to the point
         * \param force the force vector applied
         */
        void applyForce(sf::Vector3f force);

        /*!
         * \brief increase the damping of the point
         * \param factor increasing factor
         */
        void increaseDamping(double factor);

        /*!
         * \brief update the point mass
         * \param elapsedTime time elapsed since last simulated frame
         */
        void update(double elapsedTime);

    /* public attributes */
    public:

        sf::Vector3f pos;
        sf::Vector3f velocity;
        double invMass;

        sf::Vector3f acceleration;
        double damping;

};

/*!
 * \class Spring
 * \brief representation of a spring
 */
class Spring {

    /* public attributes */
    public:
        PointMass end1;
        PointMass end2;
        double targetLength;
        double stiffness;
        double damping;


    /* public methods */
    public:

        /*!
         * \brief constructor
         * \param pos1 position of the first end point
         * \param pos2 position of the second end point
         * \param stiffness stiffness of the spring
         * \param damping damping
         */
        Spring(PointMass pend1, PointMass pend2, double pstiffness, double pdamping);

        /*!
         * \brief update the spring
         * \param elapsedTime elapsed time since the last frame
         */
        void update(double elapsedTime);
};


#endif /* SPRING_HPP */
