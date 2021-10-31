/**
 * Circle constructor that initializes relevant properties of the n-dimensional spheroid.
 * @param position position of the n-dimensional spheroid, effectively the location of the center of mass
 * @param rotation rotation of the n-dimensional spheroid, which has no visible effect in 2 or 3 dimensions
 * @param massOf mass of the n-dimensional spheroid
 * @param fillColor 3D vector representing the fill color of the shape 
 * @param strokeColor 3D vector representing the stroke color of the shape (applicable only in 2D drawing)
 * @param radius radius of the n-dimensional spheroid
 */
Circle::Circle(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, Vector &accel, Vector &jerk, double radius) :
    Shape(position, rotation, massOf, fillColor, strokeColor, velocity, accel, jerk), r(radius) {
    
}   

/**
 * Draw a 2D cross-section of spheroid. Must be called within a gl context
 */
void Circle::draw2D() {
    // detail can be scaled by radius (larger radius = greater detail)
    int detail = (int)(r * 100 + 20);
    glBegin(GL_POLYGON);
    
    for (int i = 0; i < detail; i ++) {
        fillColor3f.fill(); glVertex3f(com.getAt(0) + r*cos(2*PI/detail*i), com.getAt(1) + r*sin(2*PI/detail*i), 0);
    }

    glEnd();
}

void Circle::update(double dT) {
    
}

bool Circle::collideWith(Shape shape) {

}