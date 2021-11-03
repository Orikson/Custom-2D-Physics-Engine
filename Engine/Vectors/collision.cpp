/**
 * Collision constructor that accepts whether or not a collision occurs, and if it does, indicates direction (normal), penetration distance, as well as a vector representing the touching features
 * @param collision boolean representing whether a collision occured or not
 * @param direction Vector representing the direction in which a collision occured (normal vector)
 * @param penetration penetration distance of the collision
 * @param touching touching features of the collision
 */
Collision::Collision(bool collision, Vector direction, double penetration, vector<Vector> touching) {
    collide = collision;
    dir = direction;
    pen = penetration;
    touched = touching;
}

/**
 * Collision constructor that accepts whether or not a collision occurs (usually used for false collisions)
 * @param collision
 */
Collision::Collision(bool collision) {
    collide = collision;
}

/**
 * Default colllision constructor
 */
Collision::Collision() {
    
}