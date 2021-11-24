// Defines a distance constraint between two shapes
#ifndef _DISTANCE_H
#define _DISTANCE_H

#include "../../../common.h"

class DistanceConstraint: public Constraint {
    public:
        DistanceConstraint(Shape &A, Shape &B, Vector rA, Vector rB);
        DistanceConstraint();
        ~DistanceConstraint();

        void setup();

        void update(double dT) override;
        
        Vector rA;
        Vector rB;

        double target;
        double mass;

};

#include "distance.cpp"

#endif