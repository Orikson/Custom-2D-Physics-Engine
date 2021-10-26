/* Constructors */

// Vector class constructor 
// accepts ints, doubles, and floats

/**
 * Vector class constructor that accepts ints, doubles, and floats
 * @param size an integer representing the size of the vector
 * @param contents... integers, doubles, and floats (anything that can be cast to double) that compromise the vector
 */
template <typename... Types> Vector::Vector(int size, Types... contents) {
    vectorSize = size;
    addvals(contents...);
    magnitude = mag();
}

// Default constructor
Vector::Vector() {}

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
void Vector::addvals() { vectorSize = vectorContents.size(); }


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
    vectorContents[index] = val;
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

// normalizes the vector, and redefines the vector as the normalized version
void Vector::mNorm() {}

// negates the vector, and redefines the vector as the negated version
void Vector::mNeg() {}

// adds the vector to the given vector in the form Ai = Ai + Bi
void Vector::mAdd(Vector vector) {}

// subtracts the given vector from the vector in the form Ai = Ai - Bi
void Vector::mSubtract(Vector vector) {}

// multiplies each component of the given vector with the matching component in the vector in the form Ai = Ai * Bi
void Vector::mPointwiseProduct(Vector vector) {}

// divides each component of the given vector with the matching component in the vector in the form Ai = Ai / Bi
void Vector::mPointwiseDivision(Vector vector) {}

// adds a scalar to each component of the vector in the from Ai = Ai + S
void Vector::mAddScalar(double scalar) {}

// multiplies each component of the vector by a scalar in the form Ai = Ai * S
void Vector::mMultScalar(double scalar) {}

// normalizes the given vector, and returns a new one
Vector Vector::norm(Vector vector) {}

// negates the given vector, and returns a new one
Vector Vector::neg(Vector vector) {}

// adds the two vectors of equivalent dimension together, and returns a new vector, in the form Ci = Ai + Bi
Vector Vector::add(Vector vector1, Vector vector2) {}

// subtracts the two vectors of equivalent dimension together, and returns a new vector, in the form Ci = Ai - Bi
Vector Vector::subtract(Vector vector1, Vector vector2) {}

// multiplies each component of each vector together, and returns a new vector, in the form Ci = Ai * Bi
Vector Vector::pointwiseProduct(Vector vector1, Vector vector2) {}

// divides each component of the second vector from the first, and returns a new vector, in the form Ci = Ai / Bi
Vector Vector::pointwiseDivision(Vector vector1, Vector vector2) {}

// adds a scalar to each component of the given vector, and returns a new one, in the form Bi = Ai + S
Vector Vector::addScalar(Vector vector, double scalar) {}

// multiplies a scalar to each component of the given vector, and returns a new one, in the form Bi = Ai * S
Vector Vector::multScalar(Vector vector, double scalar) {}