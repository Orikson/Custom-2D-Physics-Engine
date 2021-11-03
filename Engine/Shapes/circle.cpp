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
Collision Circle::collideWith(Shape shape) {

}

/**
 * Overload of generic shape collision, specifically for circles
 * @param circle circle to check the collision with
 * @return object describing the collision (or lack thereof)
 */
Collision Circle::collideWith(Circle circle) {
    bool collide;
    Vector normal;
    double penetration;
    vector<Vector> touching;

    // check collision
    Vector temp = Vector::subtract(com, circle.com);
    collide = temp.mag() - r - circle.r <= 0;

    if (!collide) {
        return Collision(false);
    }

    // calculate normal
    normal = Vector::norm(Vector::subtract(com, circle.com));

    // calculate penetration distance
    penetration = abs(temp.mag() - r - circle.r);

    // calculate contact manifold
    touching.push_back(Vector::add(com,Vector::multScalar(normal, r-penetration/2)));

    // handle degenerate cases
    if (temp.mag() == 0) {
        // if centers coincide, set normal of collision to the up direction
        // probably would only happen if an object spawns directly on top of another one anyways
        normal = Vector::multScalar(com, 0);
        normal.setAt(1,1);
        
        touching.clear();
    }

}