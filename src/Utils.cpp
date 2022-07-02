/*!
* \file Utils.cpp
* \brief Utilities functions implementations
* \author smbct
* \date 08.17.2016
*/

#include "Utils.hpp"

#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace sf;

/*----------------------------------------------------------------------------*/
void Utils::randInit() {
    srand(time(0));
}

/*----------------------------------------------------------------------------*/
double Utils::randRange(double min, double max) {
    return min + (static_cast<double>(rand())/RAND_MAX)*(max-min);
}

/*----------------------------------------------------------------------------*/
int Utils::randRange(int min, int max) {
    return static_cast<int>(randRange(static_cast<double>(min), static_cast<double>(max)));
}

/*----------------------------------------------------------------------------*/
Vector2f Utils::vectorFromLengthAngle(double length, double angle) {

    Vector2f res(cos(angle), sin(angle));
    res.x *= length;
    res.y *= length;

    return res;
}

/*----------------------------------------------------------------------------*/
double Utils::vectorToAngle(Vector2f vector) {
    return atan2(vector.y, vector.x);
}

/*----------------------------------------------------------------------------*/
double Utils::length(Vector2f& vec) {
    return sqrt(lengthSq(vec));
}

/*----------------------------------------------------------------------------*/
double Utils::length(sf::Vector3f& vec) {
    return sqrt(lengthSq(vec));
}

/*----------------------------------------------------------------------------*/
double Utils::lengthSq(Vector2f& vec) {
    return vec.x*vec.x + vec.y*vec.y;
}

/*----------------------------------------------------------------------------*/
double Utils::lengthSq(Vector3f& vec) {
    return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;
}

/*----------------------------------------------------------------------------*/
double Utils::PI() {
    return 3.1415926;
}

/*----------------------------------------------------------------------------*/
double Utils::toRadian(double angle) {
    return angle*Utils::PI()/180.;
}

/*----------------------------------------------------------------------------*/
double Utils::toDegree(double angle) {
    return angle*180./Utils::PI();
}

/*----------------------------------------------------------------------------*/
Color Utils::HSVToColor(float h, float s, float v) {

    if (h == 0 && s == 0) {
        return Color(v*255, v*255, v*255);
    }

    float c = s * v;
    float x = c * (1 - abs((int)h % 2 - 1));
    float m = v - c;

    if (h < 1) return Color((c + m)*255, (x + m)*255, m*255.);
    else if (h < 2) return Color((x + m)*255, (c + m)*255, m*255);
    else if (h < 3) return Color(m*255, (c + m)*255, (x + m)*255);
    else if (h < 4) return Color(m*255, (x + m)*255, (c + m)*255);
    else if (h < 5) return Color((x + m)*255, m*255, (c + m)*255);
    else return Color((c + m)*255, m*255, (x + m)*255);

}

/*----------------------------------------------------------------------------*/
Color Utils::colorLerp(Color col1, Color col2, double percent) {
    Color res;
    res.r = col1.r + (col2.r-col1.r)*percent;
    res.g = col1.g + (col2.g-col1.g)*percent;
    res.b = col1.b + (col2.b-col1.b)*percent;
    res.a = /*col1.a + (col2.a-col1.a)*percent*/255;

    return res;
}

/*----------------------------------------------------------------------------*/
sf::Vector2f Utils::catmull_rom(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4, float t) {

  return 0.5 * ( (2*p2) + (-1*p1+p3)*t + (2*p1-5*p2+4*p3-p4)*t*t + (-1*p1+3*p2-3*p3+p4)*t*t*t );

}


/*----------------------------------------------------------------------------*/
sf::Vector2f operator*(sf::Vector2f left, sf::Vector2f right) {
  return sf::Vector2f(left.x*right.x, left.y*right.y);
}

/*----------------------------------------------------------------------------*/
sf::Vector2f operator*(sf::Vector2f left, double right) {
  return sf::Vector2f(left.x*right, left.y*right);
}

/*----------------------------------------------------------------------------*/
sf::Vector2f operator*(double left, sf::Vector2f right) {
  return right*left;
}

/*----------------------------------------------------------------------------*/
sf::Vector2f operator/(sf::Vector2f left, double right) {
  return sf::Vector2f(left.x/right, left.y/right);
}

sf::Vector3f operator*(sf::Vector3f left, sf::Vector3f right) {
  return sf::Vector3f(left.x*right.x, left.y*right.y, left.z*right.z);
}

/*----------------------------------------------------------------------------*/
sf::Vector3f operator*(sf::Vector3f left, double right) {
  return sf::Vector3f(left.x*right, left.y*right, left.z*right);
}

/*----------------------------------------------------------------------------*/
sf::Vector3f operator*(double left, sf::Vector3f right) {
  return right*left;
}

/*----------------------------------------------------------------------------*/
sf::Vector3f operator/(sf::Vector3f left, double right) {
  return sf::Vector3f(left.x/right, left.y/right, left.z/right);
}
