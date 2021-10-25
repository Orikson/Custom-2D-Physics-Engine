/* Shape Parent Class */
#ifndef _SHAPE_H
#define _SHAPE_H

#include "../../common.h"

class Shape {
    public:
        // draw function can only be called within the gl graphics context as it calls gl related functions
        // draws the shape
        virtual void draw();

        // update function can only be called within the gl graphics context as it calls gl related functions
        // updates position, velocity, acceleration, net forces, etc.
        virtual void update();

        // checks for a collision with another object
        virtual bool collideWith(Shape shape);

    protected:
        // center of mass of shape
        Vector com;

};

# include "shapes.cpp"

#endif