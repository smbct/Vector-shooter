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
        static double length(sf::Vector3f& vec);
        static double lengthSq(sf::Vector2f& vec);
        static double lengthSq(sf::Vector3f& vec);
        static double PI();
        static double toRadian(double angle);
        static double toDegree(double angle);
        static sf::Color HSVToColor(float h, float s, float v);
        static sf::Color colorLerp(sf::Color col1, sf::Color col2, double percent);
        static sf::Vector2f catmull_rom(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4, float t);


};

sf::Vector2f operator*(sf::Vector2f left, sf::Vector2f right);
sf::Vector2f operator*(sf::Vector2f left, double right);
sf::Vector2f operator*(double left, sf::Vector2f right);
sf::Vector2f operator*(sf::Vector2f left, double right);
sf::Vector2f operator/(sf::Vector2f left, double right);

sf::Vector3f operator*(sf::Vector3f left, sf::Vector3f right);
sf::Vector3f operator*(sf::Vector3f left, double right);
sf::Vector3f operator*(double left, sf::Vector3f right);
sf::Vector3f operator/(sf::Vector3f left, double right);


#endif /* UTILS_HPP */
