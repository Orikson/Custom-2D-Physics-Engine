/* Capsule class */
#ifndef _SCAPSULE_H
#define _SCAPSULE_H

#include "../../common.h"

class SCapsule: public Capsule {
    public:
        SCapsule(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, Vector &accel, Vector &jerk, double halfLine, double radius);
        SCapsule();
        ~SCapsule();
        
        Collision collideWith(SCircle circle);
        Collision collideWith(Capsule capsule);
        Collision collideWith(Rectangle rectangle);
};

#include "scapsule.cpp"

#endif
