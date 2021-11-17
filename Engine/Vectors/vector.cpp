/* Constructors */

// Vector class constructor 
// accepts ints, doubles, and floats

/**
 * Vector class constructor that accepts ints, doubles, and floats
 * @param size an integer representing the size of the vector
 * @param contents... integers, doubles, and floats (anything that can be cast to double) that compromise the vector
 */
template <typename... Types> Vector::Vector(int size, Types... contents) {
    //init pointers
    vectorSize = size;

    vector<double> vectorContents;
    vectorContents.reserve(vectorSize);

    addvals(contents...);
    magnitude = mag();
}

// Default constructor
Vector::Vector() {
    vectorSize = 1;

    vector<double> vectorContents;
    vectorContents.reserve(vectorSize);

    magnitude = 0;
    vectorContents.push_back(0);
}

/**
 * Copy Constructor
 * @param vector a vector to make a copy of
 */
Vector::Vector(const Vector &vectorDef) {
    vectorSize = vectorDef.vectorSize;
    
    vector<double> vectorContents;
    vectorContents.reserve(vectorSize);

    for (double n : vectorDef.vectorContents) {
        addvals(n);
    }
    magnitude = vectorDef.magnitude;
}

/**
 * Vector destructor
 */
Vector::~Vector() {
    //delete vectorContents;
    //delete vectorSize;
    //delete magnitude;
}

/* Vector class functions */

/** 
 * Adds values to the vector (increases dimension of the vector). 
 * Accepts ints, doubles, and floats (anything that can be cast to double)
 * @param item required item to add to the vector
 * @param contents... additional items to add to the vector
 */
template <typename Type, typename... Types> void Vector::addvals(Type item, Types... contents) {
    try {
        vectorContents.push_back((double)item);
        addvals(contents...);
    } catch(...) {
        throw runtime_error("item not of type int, double, or float");
    }
}
// placeholder to terminate variadic function recursively
void Vector::addvals() {
    vectorSize = (int)vectorContents.size(); 
}


/* Getter functions */

// gets non-mutable vector value at given index
double Vector::getAt(int index) {
    return vectorContents.at(index);
}

// gets size of vector
int Vector::getSize() {
    return vectorSize;
}

// gets magnitude of vector
double Vector::getMag() {
    return magnitude;
}


/* Setter functions */

// sets vector value at given index
void Vector::setAt(int index, double val) {
    vectorContents.at(index) = val;
}


/* Vector functions */

// returns magnitude of vector
double Vector::mag() {
    double mag = 0.0;
    for (double n : vectorContents) {
        mag += n*n;
    }
    return sqrt(mag);
}

// returns dot product of two equally sized vectors
double Vector::dot(Vector vector1, Vector vector2) {
    double result = 0.0;

    if (vector1.getSize() != vector2.getSize()) {
        throw runtime_error("vectors are not of the same dimension");
    } else {
        int size = vector1.getSize();
        for (int i = 0; i < size; i ++) {
            result += vector1.getAt(i) * vector2.getAt(i);
        }
    }

    return result;
}

// returns cross product of two 3D vectors
Vector Vector::cross(Vector vector3D1, Vector vector3D2) {
    if (vector3D1.getSize() == 3 && vector3D2.getSize() == 3) {
        double iComp, jComp, kComp;
        iComp = vector3D1.getAt(1) * vector3D2.getAt(2) - vector3D1.getAt(2) * vector3D2.getAt(1);
        jComp = vector3D1.getAt(0) * vector3D2.getAt(2) - vector3D1.getAt(2) * vector3D2.getAt(0);
        kComp = vector3D1.getAt(0) * vector3D2.getAt(1) - vector3D1.getAt(1) * vector3D2.getAt(0);
        return Vector(3, iComp, jComp, kComp);
    } else {
        throw runtime_error("vectors are not 3-dimensional");
    }
}

/** 
 * returns 2D cross product of two 2D vectors (considers them as 3D vectors with 3D vector component 0). Also the determinant of a matrix constructed using these two vectors
 * @param vector1 First 2D vector
 * @param vector2 Second 2D vector
 * @return Double representing the result
 */
double Vector::cross2D(Vector vector1, Vector vector2) {
    if (vector1.getSize() == 2 && vector2.getSize() == 2) {
        return vector1.getAt(0) * vector2.getAt(1) - vector1.getAt(1) * vector2.getAt(0);
    } else {
        throw runtime_error("vectors are not 3-dimensional");
    }
}

// normalizes the vector, and redefines the vector as the normalized version
void Vector::mNorm() {}

// negates the vector, and redefines the vector as the negated version
void Vector::mNeg() {}

// adds the vector to the given vector in the form Ai = Ai + Bi
void Vector::mAdd(Vector vector) {
    for (int i = 0; i < vectorContents.size(); i ++) {
        vectorContents.at(i) += vector.vectorContents.at(i);
    }
}

// subtracts the given vector from the vector in the form Ai = Ai - Bi
void Vector::mSubtract(Vector vector) {
    for (int i = 0; i < vectorContents.size(); i ++) {
        vectorContents.at(i) -= vector.vectorContents.at(i);
    }
}

// multiplies each component of the given vector with the matching component in the vector in the form Ai = Ai * Bi
void Vector::mPointwiseProduct(Vector vector) {}

// divides each component of the given vector with the matching component in the vector in the form Ai = Ai / Bi
void Vector::mPointwiseDivision(Vector vector) {}

// adds a scalar to each component of the vector in the from Ai = Ai + S
void Vector::mAddScalar(double scalar) {}

// multiplies each component of the vector by a scalar in the form Ai = Ai * S
void Vector::mMultScalar(double scalar) {}


// projects the current vector onto the given vector
Vector Vector::nproj(Vector vector) {
    if (vector.getSize() != vectorContents.size()) { runtime_error("Vector dimension mismatch at non mutable vector subtraction Vector::nminus"); }
    double temp = Vector::dot(*this, vector) / pow(vector.getMag(), 2);
    return Vector::multScalar(vector, temp);
}

// rejects the current vector from the given vector


// adds the current vector to the given vector
Vector Vector::nadd(Vector vector) {
    if (vector.getSize() != vectorContents.size()) { runtime_error("Vector dimension mismatch at non mutable vector subtraction Vector::nminus"); }
    Vector nVector = Vector();
    for (int i = 0; i < vector.vectorContents.size(); i ++) {
        nVector.addvals(vectorContents.at(i) + vector.getAt(i));
    }
    return nVector;
}

// subtracts the current vector from the given vector
Vector Vector::nminus(Vector vector) {
    if (vector.getSize() != vectorContents.size()) { runtime_error("Vector dimension mismatch at non mutable vector subtraction Vector::nminus"); }
    Vector nVector = Vector();
    for (int i = 0; i < vector.vectorContents.size(); i ++) {
        nVector.addvals(vectorContents.at(i) - vector.getAt(i));
    }
    return nVector;
}

 // add scalar to vector
Vector Vector::nplus(double scalar) {
    Vector nVector = Vector();
    for (int i = 0; i < vectorContents.size(); i ++) {
        nVector.addvals(vectorContents.at(i) + scalar);
    }
    return nVector;
}

// multiply scalar to vector
Vector Vector::ntimes(double scalar) {
    Vector nVector = Vector();
    for (int i = 0; i < vectorContents.size(); i ++) {
        nVector.addvals(vectorContents.at(i) * scalar);
    }
    return nVector;
}




// normalizes the given vector, and returns a new one
Vector Vector::norm(Vector vector) {}

// negates the given vector, and returns a new one
Vector Vector::neg(Vector vector) {}

// adds the two vectors of equivalent dimension together, and returns a new vector, in the form Ci = Ai + Bi
Vector Vector::add(Vector vector1, Vector vector2) {
    if (vector1.getSize() != vector2.getSize()) { runtime_error("Vectors not same size for vector addition"); }
    Vector nVector = Vector();
    for (int i = 0; i < vector1.vectorContents.size(); i ++) {
        nVector.addvals(vector1.getAt(i) + vector2.getAt(i));
    }
    return nVector;
}

// subtracts the two vectors of equivalent dimension together, and returns a new vector, in the form Ci = Ai - Bi
Vector Vector::subtract(Vector vector1, Vector vector2) {
    if (vector1.getSize() != vector2.getSize()) { runtime_error("Vectors not same size for vector subtraction"); }
    Vector nVector = Vector();
    for (int i = 0; i < vector1.vectorContents.size(); i ++) {
        nVector.addvals(vector1.getAt(i) - vector2.getAt(i));
    }
    return nVector;
}

// multiplies each component of each vector together, and returns a new vector, in the form Ci = Ai * Bi
Vector Vector::pointwiseProduct(Vector vector1, Vector vector2) {
    if (vector1.getSize() != vector2.getSize()) { runtime_error("Vectors not same size for vector pointwise product"); }
    Vector nVector = Vector();
    for (int i = 0; i < vector1.vectorContents.size(); i ++) {
        nVector.addvals(vector1.getAt(i) * vector2.getAt(i));
    }
    return nVector;
}

// divides each component of the second vector from the first, and returns a new vector, in the form Ci = Ai / Bi
Vector Vector::pointwiseDivision(Vector vector1, Vector vector2) {
    if (vector1.getSize() != vector2.getSize()) { runtime_error("Vectors not same size for vector pointwise division"); }
    Vector nVector = Vector();
    for (int i = 0; i < vector1.vectorContents.size(); i ++) {
        if (vector2.getAt(i) == 0) { runtime_error("Vector divisor contains 0"); }
        nVector.addvals(vector1.getAt(i) / vector2.getAt(i));
    }
    return nVector;
}

// adds a scalar to each component of the given vector, and returns a new one, in the form Bi = Ai + S
Vector Vector::addScalar(Vector vector, double scalar) {}

// multiplies a scalar to each component of the given vector, and returns a new one, in the form Bi = Ai * S
Vector Vector::multScalar(Vector vector, double scalar) {
    Vector nVector = Vector();
    for (int i = 0; i < vector.vectorContents.size(); i ++) {
        nVector.addvals(vector.getAt(i) * scalar);
    }
    return nVector;
}

// projects the first given vector onto the second given vector
Vector Vector::proj(Vector vector1, Vector vector2) {
    double temp = Vector::dot(vector1, vector2) / pow(vector2.getMag(), 2);
    return Vector::multScalar(vector2, temp);
}

// rejects the first given vector from the second given vector (orthonormal component of the vector projection)
Vector Vector::rej(Vector vector1, Vector vector2) {
    Vector temp = Vector::proj(vector1, vector2);
    return Vector::subtract(vector1, temp);
}

/**
 * Rotate 2D vector by theta degrees
 * @param theta angle to rotate vector by
 * @return returns resultant vector
 */
Vector Vector::rotate(double theta) {
    double xC = vectorContents.at(0)*cos(theta)-vectorContents.at(1)*sin(theta);
    double yC = vectorContents.at(0)*sin(theta)+vectorContents.at(1)*cos(theta);
    return Vector(2, xC, yC);
}

/**
 * Set vector contents as given vector contents
 * @param vector vector to duplicate
 */
void Vector::setAs(Vector vector) {
    vectorContents.clear();
    for (int i = 0; i < vector.vectorContents.size(); i ++) {
        vectorContents.push_back(vector.vectorContents.at(i));
    }
    vectorSize = vector.vectorSize;
}