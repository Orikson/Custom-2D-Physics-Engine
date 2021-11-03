/* Circle (sphere, etc.) class */
#ifndef _SCIRCLE_H
#define _SCIRCLE_H

#include "../../common.h"

class SCircle: public Circle {
    public:
        SCircle(Vector &position, Vector &rotation, double mass, Color &fillColor, Color &strokeColor, Vector &velocity, Vector &accel, Vector &jerk, double radius);
        SCircle();
        ~SCircle();
        
        Collision collideWith(Circle circle);
        Collision collideWith(Capsule capsule);
};

#include "scircle.cpp"

#endif
