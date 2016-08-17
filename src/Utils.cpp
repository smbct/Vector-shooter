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
        return Color(v, v, v);
    }

    float c = s * v;
    float x = c * (1 - abs((int)h % 2 - 1));
    float m = v - c;

    if (h < 1) return Color(c + m, x + m, m);
    else if (h < 2) return Color(x + m, c + m, m);
    else if (h < 3) return Color(m, c + m, x + m);
    else if (h < 4) return Color(m, x + m, c + m);
    else if (h < 5) return Color(x + m, m, c + m);
    else return Color(c + m, m, x + m);

}
