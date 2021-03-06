/* n-Dimensional Vectors Class */
#ifndef _VECTOR_H
#define _VECTOR_H

#include "../../common.h"

class Vector {
    public:
        // construct vector (a variadic function)
        // accepts ints, floats, and doubles
        /* params:
            * size: dimension of vector
            * contents: contents of vector
        */
        template <typename... Types> Vector(int size, Types... contents);

        // default constructor
        Vector();

        // copy constructor
        Vector(const Vector &vector);

        // destructor
        ~Vector();

        // add dimensions to vector (a variadic function)
        // accepts ints, floats, and doubles
        template <typename Type, typename... Types> void addvals(Type item, Types... contents);
        void addvals();

        // set contents as given vector's contents
        void setAs(Vector vector);

        // getter functions
        // gets vector value at given index
        // kind of useless because vectorContents is public anyways
        // .getAt(i) is equivalent to .vectorContents.at(i)
        double getAt(int index);

        // gets size of vector
        int getSize();

        // gets magnitude of vector
        double getMag();


        // setter functions
        // sets vector value at given index
        // kind of useless because vectorContents is public anyways
        // .setAt(i, val) is equivalent to .vectorContents.at(i) = val
        void setAt(int index, double val);
        
        // calculates magnitude of vector
        double mag();


        /* -- general static functions -- */
        // dot product
        static double dot(Vector vector1, Vector vector2);

        // cross product (returns a new Vector object)
        static Vector cross(Vector vector3D1, Vector vector3D2);

        // 2D temp cross (returns double)
        static double cross2D(Vector vector1, Vector vector2);


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


        /* -- non mutator vector functions -- */
        // project current vector object onto given vector
        Vector nproj(Vector vector);

        // reject curent vector object from given vector
        Vector nrej(Vector vector);

        // add given vector to current vector
        Vector nadd(Vector vector);

        // subtract given vector from current vector
        Vector nminus(Vector vector);

        // add scalar to vector
        Vector nplus(double scalar);

        // multiply scalar to vector
        Vector ntimes(double scalar);


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

        // projection of vector A on vector B
        static Vector proj(Vector vector1, Vector vector2);

        // rejection of vector A on vector B
        static Vector rej(Vector vector1, Vector vector2);

        // rotate this vector by theta degrees (only for 2D)
        Vector rotate(double theta);



        // used to store contents of the vector
        vector<double> vectorContents;

        // size of vector
        int vectorSize;

        // magnitude of vector
        double magnitude;


        

};

#include "vector.cpp"

#endif