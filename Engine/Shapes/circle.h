/* Circle (sphere, etc.) class */
#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "../../common.h"

class Circle: public Shape {
    public:
        Circle(Vector &position, Vector &rotation, double mass, Color &fillColor, Color &strokeColor, Vector &velocity, Vector &accel, Vector &jerk, double radius);
        Circle();
        ~Circle();
        
        double getRadius();
        void setRadius(double value);

        /* overrided functions from Shape */
        void draw2D() override;
        void update(double dT) override;
        Collision collideWith(Shape shape) override;

        // radius
        double r;
};

#include "circle.cpp"

#endif
