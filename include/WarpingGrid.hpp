/*!
 * \file Warping.hpp
 * \brief Warping grid class definition
 * \author smbct
 * \date 08.24.2016
 */

#ifndef WARPING_GRID_HPP
#define WARPING_GRID_HPP

#include <vector>
#include "Spring.hpp"

/*!
 * \class grid
 * \brief defnition of the background grid that react to thes entities
 */
class Grid {

    public:
        Grid(sf::Vector2f size, sf::Vector2f space);
        void update(double elapsedTime);
        void applyDirectedForce(sf::Vector3f force, sf::Vector3f pos, double radius);
        void applyImplosiveForce(double force, sf::Vector3f position, double radius);
        void applyExplosiveForce(double force, sf::Vector3f position, double radius);
        void draw(sf::RenderTarget& renderer, sf::Vector2f size);
        ~Grid();
        void drawLine(sf::RenderTarget& renderer, sf::Vector2f pos, sf::Vector2f pos2, double thickness);

    private:
        PointMass** _points;
        PointMass** _fixedPoints;
        std::vector<Spring*> _springs;
        int _nbCols;
        int _nbRows;
};


#endif /* WARPING_GRID_HPP */
