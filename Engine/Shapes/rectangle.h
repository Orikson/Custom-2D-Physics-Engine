/* Rectangle (rectangular prism, etc.) class */
#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "../../common.h"

class Rectangle: public Shape {
    public:
        Rectangle(Vector position, Vector rotation, double mass, Color fillColor, Color strokeColor, Vector dimensions);
        Vector getDim();
        void setDim(int index, double value);

        // function to load verticies
        void vertex(vector<int> &iv);

        // helper vertex loader
        void binIterate(int depth, vector<int> &iv, void (Rectangle::*f)(vector<int> &));
        void grayIterate(int depth, void (Rectangle::*f)(vector<int> &));

        /* overrided functions from Shape */
        
        void draw2D() override;
        void update() override;
        bool collideWith(Shape shape) override;
    
    protected:
        // dimension of rectangle
        Vector dim;


};

#include "rectangle.cpp"

#endif
