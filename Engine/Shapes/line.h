// Line class
#ifndef _LINE_H
#define _LINE_H

#include "../../common.h"

class Line {
    public:
        Line(Vector p1, Vector p2);
        Line();
        ~Line();

        Vector p1;
        Vector p2;
        
};

#endif