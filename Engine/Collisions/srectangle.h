/* Circle (sphere, etc.) class */
#ifndef _SRECTANGLE_H
#define _SRECTANGLE_H

#include "../../common.h"

class SRectangle: public Rectangle {
    public:
        SRectangle(Vector &position, Vector &rotation, double mass, Color &fillColor, Color &strokeColor, Vector &velocity, double radius);
        SRectangle();
        ~SRectangle();
        
        Collision collideWith(Circle circle);
        Collision collideWith(Capsule capsule);
        Collision collideWith(Rectangle rectangle);

        Collision collideWithFloor() override;
};

#include "srectangle.cpp"

#endif
