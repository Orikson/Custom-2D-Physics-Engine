/* Circle (sphere, etc.) class */
#ifndef _SRECTANGLE_H
#define _SRECTANGLE_H

#include "../../common.h"

class SRectangle: public Rectangle {
    public:
        SRectangle(Vector &position, Vector &rotation, double mass, Color &fillColor, Color &strokeColor, Vector &velocity, double elasticity, Vector &dimensions);
        SRectangle();
        ~SRectangle();
        
        Collision collideWith(Shape &shape) override;
        Collision collideWith(Circle &circle) override;
        Collision collideWith(Capsule &capsule) override;
        Collision collideWith(Rectangle &rectangle) override;

        Collision collideWithFloor() override;
};

#include "srectangle.cpp"

#endif
