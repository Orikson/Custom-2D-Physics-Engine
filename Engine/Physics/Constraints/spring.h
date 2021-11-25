// Defines a distance constraint between two shapes
#ifndef _SPRING_H
#define _SPRING_H

#include "../../../common.h"

class SpringConstraint: public Constraint {
    public:
        SpringConstraint(Shape &A, Shape &B, double k, double c);
        SpringConstraint();
        ~SpringConstraint();

        void setup();

        void update(double dT) override;
        
        double k;
        double c;

        double d;

};

#include "spring.cpp"

#endif