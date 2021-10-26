/**
 * n-dimensional nested for loop to assist in the generation of verticies/edges. 
 * Accepts a function that constructs a vector (returns void) and accepts a vector reference
 * @param depth recursion limiter on binIterate, marks the number of characters in the iterated binary value
 * @param iv vector of size depth used to yield the binary values within the iterator 
 * @param func function that binIterate calls on generated binary
 */
void Rectangle::binIterate(int depth, vector<int> &iv, void (Rectangle::*f)(vector<int> &)){
    if (depth > 0) {
        for (int i = 0; i < 2; i ++) {
            iv[depth-1] = i;
            Rectangle::binIterate(depth-1, iv, f);
        }
    } else {
        // iv contains the binary for all numbers until 2^(iv.size())
        (this->*f)(iv);
    }
}

/**
 * Rectangle constructor that initializes edge and vertex vectors and relevant properties of the n-dimensional rectoid. 
 * Rotation is defined as angles away from previously defined angles (e.g. theta -> angle away from x towards y, phi -> angle away from z towards the plane xy, etc.) 
 * Rotation is thus one order less than that of dimensions and position
 * @param position position of the n-dimensional rectoid, of the same order as dimensions, effectively the location of the center of mass
 * @param rotation rotation of the n-dimensional rectoid, of the order one less than dimensions 
 * @param massOf mass of the n-dimensional rectoid
 * @param fillColor 3D vector representing the fill color of the shape 
 * @param strokeColor 3D vector representing the stroke color of the shape (applicable only in 2D drawing)
 * @param dimensions dimensions of the n-dimensional rectoid
 */
Rectangle::Rectangle(Vector position, Vector rotation, double massOf, Color fillColor, Color strokeColor, Vector dimensions) : Shape(position, rotation, massOf, fillColor, strokeColor) {
    dim = dimensions;

    // 2d has 4 points, 3d has 8, 4d has 16 (2^n points for dimensions n)

    vector<int> mod;
    mod.resize(dim.getSize());
    binIterate(dim.getSize(), mod, vertex);


}

/**
 * Accepts a reference to a vector that is used to construct the vertex vectors
 * @param iv binary vector representing which summations to modify each vector component by
 */
void Rectangle::vertex(vector<int> &iv) {
    Vector nVertex = Vector(3); 
    for (int i=0; i < iv.size(); i ++) {
        int adj = iv.at(i)*2-1;
        double res = com.getAt(i) + dim.getAt(i) / 2 * adj;
        nVertex.addvals(res); // vertex at Vi = Xi + W/2*(+-1)
    }
    verticies.push_back(nVertex);
}

/**
 * Get the dimensions of the rectoid (a mutatable object)
 */
Vector Rectangle::getDim() {
    return dim;
}

/**
 * Set the dimension of the rectoid at a given index. 
 * Equivalent to .getDim().setAt(index, value)
 * @param index index of the dimension edited
 * @param value new value of the dimension edited
 */
void Rectangle::setDim(int index, double value) {
    dim.setAt(index, value);
}


/**
 * Draw a 2D cross-section of rectoid. Must be called within a gl context, 
 * 
 */
void Rectangle::draw2D() {
    glBegin(GL_POLYGON);
    
    //for ()
    //fillColor3f.fill(); glVertex3f(com, 0.5);

    glEnd();
}


/**
 * Update rectangle position, velocity, acceleration, and jerk, as well as other physical properties related to angular momentum
 * 
 */
void Rectangle::update() {

}


/**
 * Check for a collision using separating axis theorem on a polygonic shape
 * @param shape object of Shape with similar polygonic structure to Rectangle, to check collision with
 * @return a boolean indicating whether or not a collision has occured
 */
bool Rectangle::collideWith(Shape shape) {
    return false;
}