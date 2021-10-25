#ifndef _COMMON_H
#define _COMMON_H

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

using namespace std;
namespace patch
{
    template <typename T> string to_string( const T& n )
    {
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
#include "Engine/Graphics/graphics.h"
#include "Engine/Vectors/vector.h"
#include "Engine/Shapes/shapes.h"
#include "Engine/Shapes/ellipse.h"
#include "Engine/Shapes/rectangle.h"

#endif