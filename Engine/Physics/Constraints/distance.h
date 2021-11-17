// Defines a distance constraint between two shapes
#ifndef _DISTANCE_H
#define _DISTANCE_H

#include "../../../common.h"

class DistanceConstraint: public Constraint {
    public:
        DistanceConstraint(Shape &A, Shape &B, Vector rA, Vector rB);
        DistanceConstraint();
        ~DistanceConstraint();

        void jacobian();

        void update() override;
        
        Vector rA;
        Vector rB;

        // hardcoded for 2D (hence double instead of vector)
        

};

#include "distance.cpp"

#endif