/* Capsule class */
#ifndef _CAPSULE_H
#define _CAPSULE_H

#include "../../common.h"

class Capsule: public Shape {
    public:
        Capsule(Vector &position, Vector &rotation, double mass, Color &fillColor, Color &strokeColor, Vector &velocity, Vector &accel, Vector &jerk, double halfLine, double radius);
        Capsule();
        ~Capsule();
        
        double getRadius();
        void setRadius(double value);

        void grayIterate(int depth, void (Capsule::*f)(vector<int> &));

        void vertex(vector<int> &iv);

        /* overrided functions from Shape */
        void draw2D() override;
        void update(double dT) override;
        Collision collideWith(Shape shape) override;
        
        Collision collideWith(Circle circle);
        //Collision collideWith(Capsule capsule);

        // radius
        double r;

        // half line (from COM)
        double halfLine;

        // dimension of the capsule (defined by r and halfLine)
        // only used in a 2d context (represents [halfLine, r])
        vector<double> dim;

        // verticies only used in a 2d context
        vector<Vector> verticies;
};

#include "capsule.cpp"

#endif
