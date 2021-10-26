/* color storage class */
#ifndef _COLOR_H
#define _COLOR_H

#include "../../common.h"

class Color {
    public:
        Color();
        Color(double r, double g, double b);

        // gl context functions for fill
        void fill();

        // set fill without a color object
        static void setFill(double r, double g, double b);

        double setR(double r);
        double setG(double g);
        double setB(double b);

        double red;
        double green;
        double blue;
};

#include "color.cpp"

#endif