/**
 * Smart Capsule constructor that initializes relevant properties as defined by the Capsule constructor. 
 * @param position position of the n-dimensional capsule, effectively the location of the center of mass
 * @param rotation rotation of the n-dimensional capsule
 * @param massOf mass of the n-dimensional capsule
 * @param fillColor 3D vector representing the fill color of the shape
 * @param strokeColor 3D vector representing the stroke color of the shape (applicable only in 2D drawing)
 * @param halfLine magnitude from center of mass of half the line defining the capsule
 * @param radius radius of the n-dimensional capsule
 */
SCapsule::SCapsule(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, double halfLine, double radius) :
    Capsule(position, rotation, massOf, fillColor, strokeColor, velocity, halfLine, radius) {
    
}

/**
 * Overload of generic shape collision, specifically for circles. 
 * NOTE: This should only be called on a smart circle (smart capsule is defined with inheritance after smart circle is defined, and calls functions that it has made)
 * @param circle smart circle to check the collision with
 * @return object describing the collision (or lack thereof)
 */
Collision SCapsule::collideWith(SCircle circle) {
    /* everything is the same as our circle -> capsule collision except inverted
        however, inversions about a point exist as the same point,
        thus we can call the same function representing the collision between circle -> capsule
        and only negate the normal */
    
    return circle.collideWith(*this).neg();
}

/**
 * Overload of generic shape collision, specifically for capsules
 * @param capsule capsule to check the collision with
 * @return object describing the collision (or lack thereof)
 */
Collision SCapsule::collideWith(Capsule capsule) {
    bool collide;
    Vector normal;
    double penetration;
    vector<Vector> touching;

    
}

/**
 * Overload of generic shape collision, specifically for rectangles
 * @param rectangle rectangle to check the collision with
 * @return object describing the collision (or lack thereof)
 */
Collision SCapsule::collideWith(Rectangle rectangle) {

}


Collision SCapsule::collideWithFloor() {
    
}