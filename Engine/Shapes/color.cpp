/**
 * Default Color constructor, initializes to the color black
 */
Color::Color() {
    red = 0.;
    green = 0.;
    blue = 0.;
}

/**
 * GL Context function that sets the fill color to the specified RGB values of the color object
 */
void Color::fill() {
    glColor3f(red, green, blue);
}
