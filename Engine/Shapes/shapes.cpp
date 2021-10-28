/**
 * Constructs a generic (polygonic) shape at the given position, rotation, with the given mass, and fill/stroke colors
 * @param position n-dimensional position vector
 * @param rotation (n-1)-dimensional rotation vector
 * @param massOf mass of shape
 * @param fillColor 3D vector representing the fill color of the shape 
 * @param strokeColor 3D vector representing the stroke color of the shape (applicable only in 2D drawing)
 */
Shape::Shape(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, Vector &accel, Vector &jerk) : 
    com(position), rot(rotation), fillColor3f(fillColor), strokeColor3f(strokeColor), vel(velocity), acl(accel), jrk(jerk) {
    /*com = position;
    rot = rotation;
    mass = massOf;
    fillColor3f = fillColor;
    strokeColor3f = strokeColor;
    vel = velocity;
    acl = accel;
    jrk = jerk;*/
    mass = massOf;
}

/**
 * Default Constructor
 */
Shape::Shape() {
    Vector com;
    Vector rotation;
    double massOf = 0.;
    Color fillColor3f;
    Color strokeColor3f;
    Vector vel;
    Vector acl;
    Vector jrk;
}

/**
 * Shape deconstructor
 */
Shape::~Shape() {
    /*delete com;
    delete rot;
    delete vel;
    delete acl;
    delete jrk;
    delete size;
    delete fillColor3f;
    delete strokeColor3f;*/
}

/**
 * Empty function to be overrided by subclasses of Shape
 */
void Shape::draw2D() {}

/**
 * Empty function to be overrided by subclasses of Shape
 */
void Shape::update() {}

/**
 * Empty function to be overrided by subclasses of Shape
 * @param shape a parameter to make the compiler happy
 * @return false to make the compiler happy
 */
bool Shape::collideWith(Shape shape) { return false; }