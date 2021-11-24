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
            iv.at(depth-1) = i;
            Rectangle::binIterate(depth-1, iv, f);
        }
    } else {
        // iv contains the binary for all numbers until 2^(iv.size())
        (this->*f)(iv);
    }
}

/**
 * n-dimensional loop to assist in the generation of verticies/edges. Uses gray codes to preserve order of vertices. 
 * Accepts a function that constructs a vector (returns void) and accepts a vector reference
 * @param depth limiter on grayIterate, marks the number of characters in the iterated gray code
 * @param func function that grayIterate calls on generated gray codes
 */
void Rectangle::grayIterate(int depth, void (Rectangle::*f)(vector<int> &)) {
    vector<string> arr; 
    
    arr.push_back("0");
    arr.push_back("1");
    
    int i, j; 
    for (i = 2; i < (1 << depth); i = i << 1) { 
        for (j=i-1; j >= 0; j--)
            arr.push_back(arr.at(j)); 
  
        for (j=0; j < i; j++)
            arr.at(j) = "0" + arr.at(j);

        for (j=i; j < 2*i; j++) 
            arr.at(j) = "1" + arr.at(j);
    }
    for (i = 0; i < (int)arr.size(); i ++) { 
        vector<int> iv;
        for (char const &c: arr.at(i)) {
            if (c == '0') {
                iv.push_back(0);
            } else if (c == '1') {
                iv.push_back(1);
            }
        }
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
Rectangle::Rectangle(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, double elasticity, Vector &dimensions) : 
    Shape(position, rotation, massOf, fillColor, strokeColor, velocity, elasticity), dim(dimensions) {
    // 2d has 4 points, 3d has 8, 4d has 16 (2^n points for dimensions n)
    
    vector<Vector*> verticies;
    verticies.reserve(dim.getSize());

    vector<Vector*> edges;
    edges.reserve(dim.getSize());

    grayIterate(dim.getSize(), vertex);

    // Moment of Inertia is constructed from 3 column vectors representing rotation about the X, Y, and Z axes
    // (1/12)m(d_n^2+d_m^2)
    // MoI matrix appears visually here as its transpose
    double cs = com.getSize();
    double I1 = (1/12)*massOf*(dim.getAt(2)*dim.getAt(2)+dim.getAt(1)*dim.getAt(1));
    double I2 = (1/12)*massOf*(dim.getAt(1)*dim.getAt(1)+dim.getAt(0)*dim.getAt(0));
    double I3 = (1/12)*massOf*(dim.getAt(0)*dim.getAt(0)+dim.getAt(2)*dim.getAt(2));

    if (cs == 3) { // 3D matrix
        MoI.push_back(Vector(3, I1, 0, 0));
        MoI.push_back(Vector(3, 0, I2, 0));
        MoI.push_back(Vector(3, 0, 0, I3));
    } else if (cs == 2) { // 2D MoI ((1/12)m(a^2+b^2))
        MoI.push_back(Vector(1, I2));
        invMoI.push_back(Vector(1, 1.0 / I2));
    }
}

/**
 * Default Rectangle constructor
 */
Rectangle::Rectangle() {

}

/**
 * Default Rectangle destructor
 */
Rectangle::~Rectangle() {
    //delete edges;
    //delete verticies;
    //delete dim;
}

/**
 * Accepts a reference to a vector that is used to construct the vertex vectors
 * @param iv binary vector representing which summations to modify each vector component by
 */
void Rectangle::vertex(vector<int> &iv) {
    Vector nVertex = Vector(3); 
    for (int i=0; i < (int)iv.size(); i ++) {
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
 * Draw a 2D cross-section of rectoid. Must be called within a gl context
 * 
 */
void Rectangle::draw2D() {
    glBegin(GL_POLYGON);
    
    for (int i = 0; i < (int)verticies.size(); i ++) {//(Vector v : verticies) {
        fillColor3f.fill(); glVertex3f(verticies.at(i).getAt(0), verticies.at(i).getAt(1), 0);
    }

    glEnd();
}


/**
 * Update rectangle position, velocity, acceleration, and jerk, as well as other physical properties related to angular momentum
 * 
 */
void Rectangle::update(double dT) {
    acl.mAdd(jrk);
    vel.mAdd(acl);
    com.mAdd(vel);
    //if (com.vectorContents->at(1) < -0.5) { vel.vectorContents->at(1) *= -1; }
    // collision with floor
    if (com.vectorContents.at(1) - dim.vectorContents.at(1) / 2 < -1.0) {
        com.vectorContents.at(1) = -1. + dim.vectorContents.at(1);
        vel.vectorContents.at(1) *= -0.95;
    }

    updateVertices();
}

/**
 * Update vertex positions based on updates to com and rot
 */
void Rectangle::updateVertices() {
    verticies.clear();

    grayIterate(dim.getSize(), vertex);
}


/**
 * Check for a collision using separating axis theorem on a polygonic shape
 * @param shape object of Shape with similar polygonic structure to Rectangle, to check collision with
 * @return object describing the collision (or lack thereof)
 */
Collision Rectangle::collideWith(Shape &shape) {
    
}

Collision Rectangle::collideWithFloor() {
    
}