/* Circle (sphere, etc.) class */
#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "../../common.h"

class Circle: public Shape {
    public:
        Circle(Vector &position, Vector &rotation, double mass, Color &fillColor, Color &strokeColor, Vector &velocity, double elasticity, double radius);
        Circle();
        ~Circle();
        
        double getRadius();
        void setRadius(double value);

        /* overrided functions from Shape */
        void draw2D() override;
        void update(double dT) override;
        virtual Collision collideWith(Shape &shape) override;
        virtual Collision collideWith(Circle &circle) override;
        virtual Collision collideWith(Capsule &capsule) override;
        virtual Collision collideWith(Rectangle &rectangle) override;
        virtual Collision collideWithFloor() override;

        // radius
        double r;
};

//#include "circle.cpp"

#endif
