/**
 * Capsule constructor that initializes relevant properties of the n-dimensional capsule (a line segment with a radius).
 * @param position position of the n-dimensional capsule, effectively the location of the center of mass
 * @param rotation rotation of the n-dimensional capsule
 * @param massOf mass of the n-dimensional capsule
 * @param fillColor 3D vector representing the fill color of the shape
 * @param strokeColor 3D vector representing the stroke color of the shape (applicable only in 2D drawing)
 * @param halfLine magnitude from center of mass of half the line defining the capsule
 * @param radius radius of the n-dimensional capsule
 */
Capsule::Capsule(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, double elasticity, double halfLine, double radius) : 
    Shape(position, rotation, massOf, fillColor, strokeColor, velocity, elasticity), r(radius), halfLine(halfLine) {
    dim.push_back(halfLine);
    dim.push_back(r);
    grayIterate(com.getSize(), vertex);
}

/**
 * Capsule destructor
 */
Capsule::~Capsule() {
    
}

/**
 * n-dimensional loop to assist in the generation of verticies/edges. Uses gray codes to preserve order of vertices. 
 * Accepts a function that constructs a vector (returns void) and accepts a vector reference
 * @param depth limiter on grayIterate, marks the number of characters in the iterated gray code
 * @param func function that grayIterate calls on generated gray codes
 */
void Capsule::grayIterate(int depth, void (Capsule::*f)(vector<int> &)) {
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

void Capsule::vertex(vector<int> &iv) {
    Vector nVertex = Vector(3); 
    for (int i=0; i < (int)iv.size(); i ++) {
        int adj = iv.at(i)*2-1;
        double res = dim.at(i) * adj;
        nVertex.addvals(res); // vertex at Vi = Xi + W/2*(+-1)
    }
    // rotate it (hard coded for 2D)
    Vector nnVertex(2, 
        com.getAt(0) + nVertex.getAt(0) * cos(rot.getAt(0)) + nVertex.getAt(1) * sin(rot.getAt(0)), 
        com.getAt(1) + nVertex.getAt(1) * cos(rot.getAt(0)) - nVertex.getAt(0) * sin(rot.getAt(0))
    );
    
    verticies.push_back(nnVertex);
}

/**
 * Find the shortest distance from the line defining the capsule to the given point
 * @param point the n-dimensional point to find the shortest distance to
 * @return tuple where the first element is the distance, and the second is the vector direction whose magnitude is reflected in the first element
 */
tuple<double,Vector> Capsule::distanceTo(Vector point) {
    if (point.getSize() != com.getSize()) { runtime_error("Vector dimension mismatch in Capsule::distanceTo"); }
    
    // hard coded for 2D
    Vector v = point.nminus(com);
    Vector up = Vector(2, halfLine*cos(rot.getAt(0)), halfLine*sin(rot.getAt(0)));
    if (abs(v.nproj(up).mag()) < up.mag()) {
        double d = v.nminus(v.nproj(up)).mag();
        Vector res = point.nminus(v.nminus(v.nproj(up)));
        tuple<double,Vector> temp (d, Vector(2, res.getAt(0), res.getAt(1)));
        return temp;
    }

    // v1 represents the first vertex of the line
    Vector v1 = com.nadd(up);

    // v2 represents the second vertex of the line
    Vector v2 = com.nminus(up);

    if (point.nminus(v1).mag() < point.nminus(v2).mag()) {
        tuple<double,Vector> temp (point.nminus(v1).mag(), v1);
        return temp;
    }
    tuple<double,Vector> temp (point.nminus(v2).mag(), v2);
    return temp;
}

/*Algorithm from
    Vladimir J. LUMELSKY,
        "ON FAST COMPUTATION OF DISTANCE BETWEEN LINE SEGMENTS",
        Information Processing Letters 21 (1985) 55-61
*/
/**
 * Find the shortest distance from the line defining the capsule to the given line segment
 * @param point1 the first n-dimensional point defining the given line segment
 * @param point2 the second n-dimensional point defining the given line segment
 * @return tuple where the first element is the distance, and the second is the vector direction whose magnitude is reflected in the first element
 */


/**
 * Draw a 2D cross-section of capsule. Must be called within a gl context
 */
void Capsule::draw2D() {
    int detail = (int)(r * 100 + 20);
    
    
    for (int i = -1; i <= 1; i += 2) {
        glBegin(GL_POLYGON);

        for (int j = 0; j < detail; j ++) {
            fillColor3f.fill(); glVertex3f(com.getAt(0) + i * halfLine * sin(rot.getAt(0)+PI/2) + r * cos(2*PI/detail*j), com.getAt(1) + i * halfLine * cos(rot.getAt(0)+PI/2) + r * sin(2*PI/detail*j), 0);
        }

        glEnd();
    }

    glBegin(GL_POLYGON);

    for (int i = 0; i < (int)verticies.size(); i ++) {
        fillColor3f.fill(); glVertex3f(verticies.at(i).getAt(0), verticies.at(i).getAt(1), 0);
    }

    glEnd();
}

void Capsule::update(double dT) {
    rot.vectorContents.at(0) += 0.001;

    verticies.clear();
    grayIterate(com.getSize(), vertex);
}

Collision Capsule::collideWith(Shape &shape) {

}

Collision Capsule::collideWithFloor() {

}