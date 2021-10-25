/**
 * Rectangle constructor that initializes edge and vertex vectors and relevant properties of the n-dimensional rectoid. 
 * Rotation is defined as angles away from previously defined angles (e.g. theta -> angle away from x towards y, phi -> angle away from z towards the plane xy, etc.) 
 * Rotation is thus one order less than that of dimensions and position
 * @param position position of the n-dimensional rectoid, of the same order as dimensions, effectively the location of the center of mass
 * @param rotation rotation of the n-dimensional rectoid, of the order one less than dimensions 
 * @param mass mass of the n-dimensional rectoid
 * @param dimensions dimensions of the n-dimensional rectoid
 */
Rectangle::Rectangle(Vector position, Vector rotation, double mass, Vector dimensions)  : Shape(position, rotation, mass) {
    dim = dimensions;


}

// draw 2d crossection of rectangle object
// all rectangles have an equal distribution of mass, so the center of mass is at the point (w/2, h/2)
// width, height, and rotation determined by the 3D vector components of protected variable dim
/**
 * Draw a 2D cross-section of rectoid. Must be called within a gl context, 
 * 
 */
void Rectangle::draw2D() {
    
}