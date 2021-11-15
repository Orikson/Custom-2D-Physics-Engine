/**
 * Smart Circle constructor that initializes relevant properties as defined by the Circle constructor. 
 * @param position position of the n-dimensional spheroid, effectively the location of the center of mass
 * @param rotation rotation of the n-dimensional spheroid, which has no visible effect in 2 or 3 dimensions
 * @param massOf mass of the n-dimensional spheroid
 * @param fillColor 3D vector representing the fill color of the shape 
 * @param strokeColor 3D vector representing the stroke color of the shape (applicable only in 2D drawing)
 * @param radius radius of the n-dimensional spheroid
 */
SCircle::SCircle(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, double radius) :
    Circle(position, rotation, massOf, fillColor, strokeColor, velocity, radius) {
    
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
    touching.push_back(com.nadd(normal.nplus(r-penetration/2)));

    // handle degenerate cases
    if (temp.mag() == 0) {
        // if centers coincide, set normal of collision to the up direction
        // probably would only happen if an object spawns directly on top of another one anyways
        normal = Vector::multScalar(com, 0);
        normal.setAt(1,1);
        
        touching.clear();
    }

    return Collision(true, normal, penetration, touching);
}

/**
 * Overload of generic shape collision, specifically for capsules
 * @param capsule capsule to check the collision with
 * @return object describing the collision (or lack thereof)
 */
Collision SCircle::collideWith(Capsule capsule) {
    bool collide;
    Vector normal;
    double penetration;
    vector<Vector> touching;
    
    // check collision
    // true when distance to closest point on the line <= this.r + capsule.r
    auto temp = capsule.distanceTo(com);
    collide = get<0>(temp) <= r + capsule.r;

    if (!collide) {
        return Collision(false);
    }

    // calculate normal
    normal = get<1>(temp).ntimes(1/(get<1>(temp).mag()));

    // calculate penetration distance
    penetration = abs(get<1>(temp).mag() - r - capsule.r);

    // calculate contact manifold
    touching.push_back(com.nadd(normal.nplus(r-penetration/2)));

    // handle degenerate cases
    if (get<0>(temp) == 0) {
        // if distance from center to the defining line of the capsule is 0, then set the normal to a vector perpendicular to 
        
        // hardcoded for 2d
        double theta = capsule.rot.getAt(0);
        normal = Vector(2, sin(theta), -cos(theta));
    }

    return Collision(true, normal, penetration, touching);
}

/**
 * Overload of generic shape collision, specifically for rectangles
 * @param rectangle rectangle to check the collision with
 * @return object describing the collision (or lack thereof)
 */
Collision SCircle::collideWith(Rectangle rectangle) {
    bool collide;
    Vector normal;
    double penetration;
    vector<Vector> touching;


}

/**
 * Collide with floor
 * @return object describing the collision (or lack thereof)
 */
Collision SCircle::collideWithFloor() {
    bool collide;
    Vector normal;
    double penetration;
    vector<Vector> touching;

    if (com.getAt(1) - r < -1) {
        collide = true;
    } else {
        return Collision(false);
    }

    // hardcoded for 2D
    normal = Vector(2, 0, 1);

    penetration = abs(com.getAt(1) - r + 1);

    touching.push_back(Vector(2, com.getAt(0), com.getAt(1) - r + 1));

    return Collision(collide, normal, penetration, touching);
}