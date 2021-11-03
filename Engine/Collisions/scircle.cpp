/**
 * Smart Circle constructor that initializes relevant properties as defined by the Circle constructor. 
 * @param position position of the n-dimensional spheroid, effectively the location of the center of mass
 * @param rotation rotation of the n-dimensional spheroid, which has no visible effect in 2 or 3 dimensions
 * @param massOf mass of the n-dimensional spheroid
 * @param fillColor 3D vector representing the fill color of the shape 
 * @param strokeColor 3D vector representing the stroke color of the shape (applicable only in 2D drawing)
 * @param radius radius of the n-dimensional spheroid
 */
SCircle::SCircle(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, Vector &accel, Vector &jerk, double radius) :
    Circle(position, rotation, massOf, fillColor, strokeColor, velocity, accel, jerk, radius) {
    
}

/**
 * Overload of generic shape collision, specifically for circles
 * @param circle circle to check the collision with
 * @return object describing the collision (or lack thereof)
 */
Collision SCircle::collideWith(Circle circle) {
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

/**
 * Overload of generic shape collision, specifically for capsules
 * @param capsule capsule to check the collision with
 * @return object describing the collision (or lack thereof)
 */
Collision SCircle::collideWith(Capsule capsule) {
    
}