/* Shape Parent Class */
#ifndef SHAPE_H
#define SHAPE_H

#include "../../common.h"

class Shape {
    public:
        // draw function can only be called within the gl graphics context as it calls gl related functions
        // draws the shape
        void draw();

        // update function can only be called within the gl graphics context as it calls gl related functions
        // updates position, velocity, acceleration, net forces, etc.
        void update();

    protected:
        

};

#endif