/* Shape Parent Class */
#ifndef _SHAPE_H
#define _SHAPE_H

#include "../../common.h"

class Shape {
    public:
        Shape();
        Shape(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, double elasticity);
        ~Shape();

        // name
        string name;

        // draw function can only be called within the gl graphics context as it calls gl related functions
        // draws the shape
        virtual void draw2D();

        // update function can only be called within the gl graphics context as it calls gl related functions
        // updates position, velocity, acceleration, net forces, etc.
        virtual void update(double dT);

        void naiveUpdate(double dT);
        void smartUpdate(double dT, vector<Shape*>* shapes);

        // checks for a collision with another object
        virtual Collision collideWith(Shape &shape);
        virtual Collision collideWith(Circle &shape);
        virtual Collision collideWith(Capsule &shape);
        virtual Collision collideWith(Rectangle &shape);
        virtual Collision collideWithFloor();

        void updateCollision(Collision collision, Shape *shape);

        void addF(Vector force);
        void addFD(Vector force, Vector pos);

        // cleared after each timestep
        Vector sumForces;

        // cleared after each tiemstep
        Vector sumTorque;
        
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

        // angular velocity
        Vector angvel;

        // angular acceleration
        Vector angacl;

        // moment of inertia (has to be stored as a matrix [vector of Vectors] which will have corresponding utility functions within the Vector class)
        vector<Vector> MoI;

        // inverse inertia for faster calculation down the line
        vector<Vector> invMoI;

        // mass of the object
        double mass;

        // inverse mass for faster calculation down the line
        double invMass;

        // dimension order
        int size;

        // elasticity
        double elasticity;

    protected:
        // fill color of object
        Color fillColor3f;

        // stroke color of object
        Color strokeColor3f;

};

#endif