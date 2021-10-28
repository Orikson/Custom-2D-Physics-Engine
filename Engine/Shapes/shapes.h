/* Shape Parent Class */
#ifndef _SHAPE_H
#define _SHAPE_H

#include "../../common.h"

class Shape {
    public:
        Shape();
        Shape(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, Vector &accel, Vector &jerk);
        ~Shape();

        // draw function can only be called within the gl graphics context as it calls gl related functions
        // draws the shape
        virtual void draw2D();

        // update function can only be called within the gl graphics context as it calls gl related functions
        // updates position, velocity, acceleration, net forces, etc.
        virtual void update();

        // checks for a collision with another object
        virtual bool collideWith(Shape shape);

    protected:
        // center of mass of shape (determined by the object)
        Vector com;

        // velocity vector of shape
        Vector vel;

        // acceleration vector of shape
        Vector acl;

        // jerk vector of shape
        Vector jrk;

        // rotation of the object (relative as determined by the object)
        Vector rot;

        // mass of the object
        double mass;

        // dimension order
        int size;

        // fill color of object
        Color fillColor3f;

        // stroke color of object
        Color strokeColor3f;

};

# include "shapes.cpp"

#endif