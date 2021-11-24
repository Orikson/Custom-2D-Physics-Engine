/**
 * Circle constructor that initializes relevant properties of the n-dimensional spheroid.
 * @param position position of the n-dimensional spheroid, effectively the location of the center of mass
 * @param rotation rotation of the n-dimensional spheroid, which has no visible effect in 2 or 3 dimensions
 * @param massOf mass of the n-dimensional spheroid
 * @param fillColor 3D vector representing the fill color of the shape 
 * @param strokeColor 3D vector representing the stroke color of the shape (applicable only in 2D drawing)
 * @param radius radius of the n-dimensional spheroid
 */
Circle::Circle(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, double elasticity, double radius) :
    Shape(position, rotation, massOf, fillColor, strokeColor, velocity, elasticity), r(radius) {
    // Moment of Inertia is constructed from 3 column vectors representing rotation about the X, Y, and Z axes
    // 2mr^2/5
    double I = 2*massOf*radius*radius/5;

    // MoI matrix appears visually here as its transpose
    double cs = com.getSize();

    if (cs == 3) { // 3D matrix
        MoI.push_back(Vector(3, I, 0, 0));
        MoI.push_back(Vector(3, 0, I, 0));
        MoI.push_back(Vector(3, 0, 0, I));
    } else if (cs == 2) { // 2D MoI ((1/2)mr^2)
        MoI.push_back(Vector(1, (1.0/2.0)*massOf*radius*radius));
        invMoI.push_back(Vector(1, 1.0 / ((1.0/2.0)*massOf*radius*radius)));
    }

    angvel.setAs(Vector(1, 0));
    angacl.setAs(Vector(1, 0));
}

Circle::~Circle() {
    
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

/**
 * Update circle position, velocity, acceleration, and jerk, as well as other physical properties related to angular momentum
 * 
 */
void Circle::update(double dT) {
    
}

/**
 * Checks for collisions with polygons using Separating Axis Theorem
 * @param shape shape to check the collision with
 * @return object describing the collision (or lack thereof)
 */
Collision Circle::collideWith(Shape &shape) {
    
}

Collision Circle::collideWith(Circle &shape) {
    
}

Collision Circle::collideWith(Capsule &shape) {
    
}

Collision Circle::collideWith(Rectangle &shape) {
    
}

Collision Circle::collideWithFloor() {

}