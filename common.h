#ifndef _COMMON_H
#define _COMMON_H

/*=======USEFUL MATH CONSTANTS=======*/
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816
#define G -9.8
#define DAMPING 0.98


/*=======STANDARD TEMPLATE LIBRARY=======*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <ctime>
#include <vector>
#include <math.h>
#include <sstream>
#include <time.h>
#include <tuple>
#include <limits>
#include <iomanip>
extern "C" {
    #include <unistd.h>
}

using namespace std;
namespace patch {
    template <typename T> string to_string(const T& n) {
        ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

template<typename Base, typename T> inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}


/*=======GLU/GLEW=======*/
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>


/*=======SDL2=======*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


/*=======CLASS DEFINITIONS=======*/
#include "classes.h"

#include "Engine/Graphics/graphics.h"

#include "Engine/Vectors/vector.h"
#include "Engine/Vectors/collision.h"

#include "Engine/Shapes/color.h"
#include "Engine/Shapes/shapes.h"
#include "Engine/Shapes/circle.h"
#include "Engine/Shapes/capsule.h"
#include "Engine/Shapes/rectangle.h"

#include "Engine/Collisions/scircle.h"
#include "Engine/Collisions/scapsule.h"
#include "Engine/Collisions/srectangle.h"
#include "Engine/Collisions/collisions.h"

#include "Engine/Physics/Constraints/constraint.h"
#include "Engine/Physics/Constraints/distance.h"
#include "Engine/Physics/Constraints/spring.h"

#include "Engine/Shapes/circle.cpp"
#include "Engine/Shapes/shapes.cpp"

#endif