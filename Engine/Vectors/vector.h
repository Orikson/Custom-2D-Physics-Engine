/* n-Dimensional Vectors Class */
#ifndef VECTOR_H
#define VECTOR_H

#include "../../common.h"

class Vector {
    public:
        // initialize vector (a variadic function)
        void setvals(double contents...);

        // add dimensions to vector (a variadic function)
        void addvals(double contents...);


        // getter functions
        // gets vector value at given index
        double getAt(int index);

        // setter functions
        // sets vector value at given index
        double setAt(int index, double val);
        
        // returns magnitude of vector
        double magnitude();


        /* -- general static functions -- */
        // dot product
        static double dot(Vector vector1, Vector vector2);

        // cross product (returns a new Vector object)
        static Vector cross(Vector vector1, Vector vector2);


        /* -- mutator vector functions -- */  
        // (mutator) normalize vector
        void mNorm();

        // (mutator) negate vector
        void mNeg();

        // (mutator) add; Ai = Ai + Bi
        void mAdd(Vector vector);

        // (mutator) subtract; Ai = Ai - Bi
        void mSubtract(Vector vector);

        // (mutator) pointwise product; Ai = Ai * Bi
        void mPointwiseProduct(Vector vector);

        // (mutator) pointwise division; Ai = Ai / Bi
        void mPointwiseDivision(Vector vector);

        // (mutator) add scalar
        void mAddScalar(double scalar);

        // (mutator) multiply by scalar
        void mMultScalar(double scalar);


        /* -- static vector functions -- */
        // normalize vector
        static Vector norm(Vector vector);

        // negate vector
        static Vector neg(Vector vector);

        // add; Ci = Ai + Bi
        static Vector add(Vector vector1, Vector vector2);
        
        // subtract; Ci = Ai - Bi
        static Vector subtract(Vector vector1, Vector vector2);
        
        // pointwise product; Ci = Ai * Bi
        static Vector pointwiseProduct(Vector vector1, Vector vector2);
        
        // pointwise division; Ci = Ai / Bi, Bi != 0 (throws arithmetic exception)
        static Vector pointwiseDivision(Vector vector1, Vector vector2);

        // add scalar; Bi = Ai + S
        static Vector addScalar(Vector vector, double scalar);

        // multiply by scalar; Bi = Ai * S
        static Vector multScalar(Vector vector, double scalar);


    protected:
        double* contents;

        

};

#endif