/* Circle (sphere, etc.) class */
#ifndef _SCIRCLE_H
#define _SCIRCLE_H

#include "../../common.h"

class SCircle: public Circle {
    public:
        SCircle(Vector &position, Vector &rotation, double mass, Color &fillColor, Color &strokeColor, Vector &velocity, double elasticity, double radius);
        SCircle();
        ~SCircle();
        
        Collision collideWith(Shape &shape) override;
        Collision collideWith(Circle &circle) override;
        Collision collideWith(Capsule &capsule) override;
        Collision collideWith(Rectangle &rectangle) override;

        Collision collideWithFloor() override;
};

#include "scircle.cpp"

#endif
