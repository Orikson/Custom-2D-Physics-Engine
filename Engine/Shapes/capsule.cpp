/**
 * Capsule constructor that initializes relevant properties of the n-dimensional capsule (a line segment with a radius).
 * @param position position of the n-dimensional capsule, effectively the location of the center of mass
 * @param rotation rotation of the n-dimensional capsule
 * @param massOf mass of the n-dimensional spheroid
 * @param fillColor 3D vector representing the fill color of the shape
 * @param strokeColor 3D vector representing the stroke color of the shape (applicable only in 2D drawing)
 * @param halfLine magnitude from center of mass of half the line defining the capsule
 * @param radius radius of the n-dimensional capsule
 */
Capsule::Capsule(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, Vector &accel, Vector &jerk, double halfLine, double radius) : 
    Shape(position, rotation, massOf, fillColor, strokeColor, velocity, accel, jerk), r(radius), halfLine(halfLine) {
    dim.push_back(halfLine);
    dim.push_back(r);
    grayIterate(com.getSize(), vertex);
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
    rot.vectorContents->at(0) += 0.001;

    verticies.clear();
    grayIterate(com.getSize(), vertex);
}

Collision Capsule::collideWith(Shape shape) {

}