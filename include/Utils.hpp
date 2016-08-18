/*!
* \file Utils.hpp
* \brief Utilities functions definitions
* \author smbct
* \date 08.17.2016
*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>

class Utils {

    public:
        static void randInit();
        static double randRange(double min, double max);
        static int randRange(int min, int max);
        static sf::Vector2f vectorFromLengthAngle(double length, double angle);
        static double vectorToAngle(sf::Vector2f vector);
        static double length(sf::Vector2f& vec);
        static double lengthSq(sf::Vector2f& vec);
        static double PI();
        static double toRadian(double angle);
        static double toDegree(double angle);
        static sf::Color HSVToColor(float h, float s, float v);
        static sf::Color colorLerp(sf::Color col1, sf::Color col2, double percent);
};

#endif /* UTILS_HPP */
