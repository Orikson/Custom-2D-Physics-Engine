/* Rectangle (rectangular prism, etc.) class */
#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "../../common.h"

class Rectangle: public Shape {
    public:
        Vector getDim();
        void setDim();

        /* overrided functions from Shape */
        void draw();
        void update();
        void collideWith();
    
    protected:
        // dimension of rectangle
        Vector dim;


};

#include "rectangle.cpp"

#endif
