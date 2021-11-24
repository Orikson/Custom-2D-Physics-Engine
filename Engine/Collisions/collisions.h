#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include "../../common.h"

class Collisions {
    public:
        Collisions();

        static Collision collide(SCircle &s1, SCircle &s2);
        static Collision collide(SCircle &s1, SCapsule &s2);
        static Collision collide(SCircle &s1, SRectangle &s2);
        static Collision collide(SCapsule &s1, SCapsule &s2);
        static Collision collide(SCapsule &s1, SRectangle &s2);
        static Collision collide(SRectangle &s1, SRectangle &s2);
        
};

#include "collisions.cpp"

#endif