/**
 * Default Color constructor, initializes to the color black
 */
Color::Color() {
    red = 0.;
    green = 0.;
    blue = 0.;
}

/**
 * RGB Color constructor
 * @param r red color component (out of 1)
 * @param g green color component (out of 1)
 * @param b blue color component (out of 1)
 */
Color::Color(double r, double g, double b) {
    red = r;
    green = g;
    blue = b;
}

/**
 * GL Context function that sets the fill color to the specified RGB values of the color object
 */
void Color::fill() {
    glColor3f(red, green, blue);
}
