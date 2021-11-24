/* Capsule class */
#ifndef _SCAPSULE_H
#define _SCAPSULE_H

#include "../../common.h"

class SCapsule: public Capsule {
    public:
        SCapsule(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, double elasticity, double halfLine, double radius);
        SCapsule();
        ~SCapsule();
        
        Collision collideWith(Shape &shape) override;
        Collision collideWith(Circle &circle) override;
        Collision collideWith(Capsule &capsule) override;
        Collision collideWith(Rectangle &rectangle) override;

        Collision collideWithFloor() override;
};

#include "scapsule.cpp"

#endif
