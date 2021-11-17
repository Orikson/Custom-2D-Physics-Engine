#ifndef _CONSTRAINT_H
#define _CONSTRAINT_H

#include "../../../common.h"

class Constraint {
    public:
        Constraint(Shape &A, Shape &B);
        Constraint();

        virtual void update();

        Shape *A;
        Shape *B;
};

#include "constraint.cpp"

#endif