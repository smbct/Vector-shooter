/*!
 * \file Warping.cpp
 * \brief Warping grid class implementation
 * \author smbct
 * \date 08.24.2016
 */

#include "WarpingGrid.hpp"

#include "Utils.hpp"

#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

/*---------------------------------------------------------------------------*/
Grid::Grid(sf::Vector2f size, sf::Vector2f space)
{
    _nbCols = static_cast<int>(size.x / space.x) + 2;
    _nbRows = static_cast<int>(size.y / space.y) + 2;

    _points = new PointMass*[_nbRows*_nbCols];
    _fixedPoints = new PointMass*[_nbRows*_nbCols];


    /* points mass creation */
    for(int col = 0; col < _nbCols; col ++) {
        for(int row = 0; row < _nbRows; row ++) {
            _points[row*_nbCols + col] = new PointMass(Vector3f(col*space.x, row*space.y, 0), 1);
            _fixedPoints[row*_nbCols + col] = new PointMass(Vector3f(col*space.x, row*space.y, 0), 0);
        }
    }

    /* springs creation */
    for(int y = 0; y < _nbRows; y++) { // row
        for(int x = 0; x < _nbCols; x++) { // col
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
            _points[i]->applyForce(force*10 / (10+length));
        }

    }
}

/*----------------------------------------------------------------------------*/
void Grid::applyImplosiveForce(double force, Vector3f position, double radius) {
    for(int i = 0; i < _nbCols*_nbRows; i++) {
        Vector3f delta = position-_points[i]->pos;
        double length = Utils::lengthSq(delta);
        if(length < radius*radius) {

            Vector3f vec = force*10*(position- _points[i]->pos) / (100+length);

            _points[i]->applyForce(vec);
            _points[i]->increaseDamping(0.6);
        }


    }
}

/*----------------------------------------------------------------------------*/
void Grid::applyExplosiveForce(double force, Vector3f position, double radius) {

  for(int i = 0; i < _nbCols*_nbRows; i++) {

    Vector3f delta = position-_points[i]->pos;
    float dist2 = Utils::lengthSq(delta);

    if (dist2 < radius * radius)
    {

        Vector3f vec(100 * force * (_points[i]->pos - position) / (10000 + dist2));

        _points[i]->applyForce(vec);
        _points[i]->increaseDamping(0.6f);
    }

  }

}

/*----------------------------------------------------------------------------*/
void Grid::draw(RenderTarget& renderer, sf::Vector2f size) {

    for(int y = 0; y < _nbRows; y++) {
        for(int x = 0; x < _nbCols; x++) {

            Vector2f pos = _points[y*_nbCols + x]->project(size);
            Vector2f left, up;

            if(y > 0) {
                double thickness = (x % 3 == 0 ? 3 : 1);
                up = _points[(y-1)*_nbCols + x]->project(size);
                // drawLine(renderer, pos, up, thickness);

                int y1 = max(0, y-2), y4 = min(y + 1, _nbRows - 1);
                sf::Vector2f mid = Utils::catmull_rom(_points[y1*_nbCols +x]->project(size), up, pos, _points[y4*_nbCols+x]->project(size), 0.5f);

                sf::Vector2f delta = mid - (left + pos)/2;
                if (Utils::lengthSq(delta) > 1)
                {
                    drawLine(renderer, up, mid, thickness);
                    drawLine(renderer, mid, pos, thickness);
                }
                else {
                  drawLine(renderer, up, pos, thickness);
                }

            }

            if(x > 0) {
                double thickness = (y % 3 == 0 ? 3 : 1);
                left = _points[y*_nbCols + x-1]->project(size);
                // drawLine(renderer, pos, left, thickness);

                int x1 = max(0, x-2), x4 = min(x + 1, _nbCols - 1);
                sf::Vector2f mid = Utils::catmull_rom(_points[y*_nbCols +x1]->project(size), left, pos, _points[y*_nbCols+x4]->project(size), 0.5f);

                sf::Vector2f delta = mid - (left + pos)/2;
                if (Utils::lengthSq(delta) > 1)
                {
                    drawLine(renderer, left, mid, thickness);
                    drawLine(renderer, mid, pos, thickness);
                }
                else {
                  drawLine(renderer, left, pos, thickness);
                }

            }

            // if (x > 1 && y >= 1) {
            //
            //     double thickness = 1.;
            //
            //     // vertical
            //     int y1 = max(0, y-2), y4 = min(y + 1, _nbRows - 1);
            //     sf::Vector2f p1 = 0.5*(_points[y1*_nbCols + x-1]->project(size)+_points[y1*_nbCols + x]->project(size));
            //     sf::Vector2f p2 = 0.5*(_points[(y-1)*_nbCols + x-1]->project(size)+_points[(y-1)*_nbCols + x]->project(size));
            //     sf::Vector2f p3 = 0.5*(_points[y*_nbCols + x-1]->project(size)+_points[y*_nbCols + x]->project(size));
            //     sf::Vector2f p4 = 0.5*(_points[y4*_nbCols + x-1]->project(size)+_points[y4*_nbCols + x]->project(size));
            //
            //     sf::Vector2f mid = Utils::catmull_rom(p1, p2, p3, p4, 0.5f);
            //     sf::Vector2f delta = mid - (p2 + p3)/2;
            //
            //     if (Utils::lengthSq(delta) > 1)
            //     {
            //       drawLine(renderer, p2, mid, thickness);
            //       drawLine(renderer, mid, p3, thickness);
            //     }
            //     else {
            //       drawLine(renderer, p2, p3, thickness);
            //     }
            // }
            //
            // if(x >= 1 && y > 1) {
            //
            //     // horizontal
            //     int x1 = max(0, x-2), x4 = min(x + 1, _nbCols - 1);
            //     double thickness = 1.;
            //
            //     sf::Vector2f p1 = 0.5*(_points[(y-1)*_nbCols + x1]->project(size)+_points[y*_nbCols + x1]->project(size));
            //     sf::Vector2f p2 = 0.5*(_points[(y-1)*_nbCols + x-1]->project(size)+_points[y*_nbCols + x-1]->project(size));
            //     sf::Vector2f p3 = 0.5*(_points[(y-1)*_nbCols + x]->project(size)+_points[y*_nbCols + x]->project(size));
            //     sf::Vector2f p4 = 0.5*(_points[(y-1)*_nbCols + x4]->project(size)+_points[y*_nbCols + x4]->project(size));
            //
            //     sf::Vector2f mid = Utils::catmull_rom(p1, p2, p3, p4, 0.5f);
            //     sf::Vector2f delta = mid - (p2 + p3)/2;
            //     if (Utils::lengthSq(delta) > 1)
            //     {
            //       drawLine(renderer, p2, mid, thickness);
            //       drawLine(renderer, mid, p3, thickness);
            //     }
            //     else {
            //       drawLine(renderer, p2, p3, thickness);
            //     }
            //
            // }

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
