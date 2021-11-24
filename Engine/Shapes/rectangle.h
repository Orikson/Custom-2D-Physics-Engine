/* Rectangle (rectangular prism, etc.) class */
#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "../../common.h"

class Rectangle: public Shape {
    public:
        Rectangle(Vector &position, Vector &rotation, double mass, Color &fillColor, Color &strokeColor, Vector &velocity, double elasticity, Vector &dimensions);//, vector<Vector> &edge, vector<Vector> &vert);
        Rectangle();
        ~Rectangle();
        
        Vector getDim();
        void setDim(int index, double value);

        // function to load verticies
        void vertex(vector<int> &iv);

        // helper vertex loader
        void binIterate(int depth, vector<int> &iv, void (Rectangle::*f)(vector<int> &));
        void grayIterate(int depth, void (Rectangle::*f)(vector<int> &));

        void updateVertices();

        /* overrided functions from Shape */
        
        void draw2D() override;
        void update(double dT) override;
        Collision collideWith(Shape &shape) override;
        virtual Collision collideWithFloor() override;

        
        // array containing vectors indicating the direction of edges originating from the vertex of the same index
        vector<Vector> edges;

        // array containing vectors indicating the positions of verticies
        vector<Vector> verticies;
    
        // dimension of rectangle
        Vector dim;


};

#include "rectangle.cpp"

#endif
