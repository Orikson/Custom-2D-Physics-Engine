#ifndef _COLLISION_H
#define _COLLISION_H

#include "../../common.h"

class Collision {
    public:
        Collision(bool collision, Vector direction, double penetration, vector<Vector> touching);
        Collision(bool collision);
        Collision();

        bool collide;
        
        Vector dir;
        
        double pen;
        
        vector<Vector> touched;
};

#include "collision.cpp"

#endif