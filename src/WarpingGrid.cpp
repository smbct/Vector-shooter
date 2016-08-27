/*!
 * \file Warping.cpp
 * \brief Warping grid class implementation
 * \author smbct
 * \date 08.24.2016
 */

#include "WarpingGrid.hpp"

#include "Utils.hpp"

using namespace std;
using namespace sf;

/*---------------------------------------------------------------------------*/
Grid::Grid(sf::Vector2f size, sf::Vector2f space)
{
    _nbCols = static_cast<int>(size.x / space.x) + 1;
    _nbRows = static_cast<int>(size.y / space.y) + 1;

    _points = new PointMass*[_nbRows*_nbCols];
    _fixedPoints = new PointMass*[_nbRows*_nbCols];

    /* points mass creation */
    int col = 0, row = 0;
    for(float y = size.y; y >= 0.; y-= space.y) {

        for(float x = 0; x < size.x; x+= space.x) {

            _points[row*_nbCols + col] = new PointMass(Vector3f(x, y, 0), 1);
            _fixedPoints[row*_nbCols + col] = new PointMass(Vector3f(x, y, 0), 0);

            col ++;
        }
        row ++;
        col = 0;
    }

    /* springs creation */
    for(int y = 0; y < _nbRows; y++) {
        for(int x = 0; x < _nbCols; x++) {

            if(x == 0 || y == 0 || x == _nbCols-1 || y == _nbRows-1) {
                _springs.push_back(new Spring(*_fixedPoints[y*_nbCols+x], *_points[y*_nbCols+x], 0.1, 0.1));
            } else if(x % 3 == 0 && y % 3 == 0) {
                _springs.push_back(new Spring(*_fixedPoints[y*_nbCols+x], *_points[y*_nbCols+x], 0.002, 0.02));
            }
            const float stiffness = 0.28;
            const float damping = 0.06;
            if(x > 0) {
                _springs.push_back(new Spring(*_points[y*_nbCols+x-1], *_points[y*_nbCols+x], stiffness, damping));
            }
            if(y > 0) {
                _springs.push_back(new Spring(*_points[(y-1)*_nbCols+x], *_points[y*_nbCols+x], stiffness, damping));
            }
        }
    }

}

/*----------------------------------------------------------------------------*/
void Grid::update(double elapsedTime) {

    for(Spring* spring : _springs) {
        spring->update();
    }

    for(int i = 0; i < _nbCols*_nbRows; i++) {
        _points[i]->update(elapsedTime);
    }

}

/*----------------------------------------------------------------------------*/
void Grid::applyDirectedForce(Vector3f force, Vector3f pos, double radius) {
    for(int i = 0; i < _nbCols*_nbRows; i++) {
        Vector3f delta = pos-_points[i]->pos;
        if(Utils::lengthSq(delta) < radius*radius) {
            double length = Utils::length(delta);
            Vector3f vec(force.x*10 / (10+length), force.y*10 / (10+length), force.z*10 / (10+length));
            _points[i]->applyForce(vec);
        }

    }
}

/*----------------------------------------------------------------------------*/
void Grid::applyImplosiveForce(double force, Vector3f position, double radius) {
    for(int i = 0; i < _nbCols*_nbRows; i++) {
        Vector3f delta = position-_points[i]->pos;
        double length = Utils::lengthSq(delta);
        if(length < radius*radius) {
            Vector3f vec(force*10 * (position.x - _points[i]->pos.x) / (100+length),
                        force*10 * (position.y - _points[i]->pos.y) / (100+length),
                        force*10 * (position.z - _points[i]->pos.z) / (100+length));
            _points[i]->applyForce(vec);
            _points[i]->increaseDamping(0.6);
        }


    }
}

/*----------------------------------------------------------------------------*/
void Grid::applyExplosiveForce(double force, Vector3f position, double radius) {

}

/*----------------------------------------------------------------------------*/
void Grid::draw(RenderTarget& renderer, sf::Vector2f size) {

    for(int y = 0; y < _nbRows; y++) {
        for(int x = 0; x < _nbCols; x++) {

            Vector2f pos = _points[y*_nbCols + x]->project(size);
            Vector2f pos2;

            if(y > 0) {
                double thickness = (x % 3 == 1 ? 3 : 1);
                pos2 = _points[(y-1)*_nbCols + x]->project(size);
                drawLine(renderer, pos, pos2, thickness);
            }

            if(x > 0) {
                double thickness = (y % 3 == 1 ? 3 : 1);
                pos2 = _points[y*_nbCols + x-1]->project(size);
                drawLine(renderer, pos, pos2, thickness);
            }

        }
    }

}

/*----------------------------------------------------------------------------*/
void Grid::drawLine(RenderTarget& renderer, Vector2f pos, Vector2f pos2, double thickness) {

    Vector2f delta = pos2-pos;
    double angle = Utils::toDegree(Utils::vectorToAngle(delta));

    RectangleShape rectangle(Vector2f(Utils::length(delta), thickness));
    rectangle.setPosition(pos);
    rectangle.setRotation(angle);
    rectangle.setFillColor(sf::Color(30, 30, 139, 85));
    renderer.draw(rectangle);
}

/*----------------------------------------------------------------------------*/
Grid::~Grid() {

    for(Spring* spring : _springs) {
        delete spring;
    }

    for(int i = 0; i < _nbRows*_nbCols; i++) {
        delete _points[i];
        delete _fixedPoints[i];
    }

    delete[] _points;
    delete[] _fixedPoints;

}
