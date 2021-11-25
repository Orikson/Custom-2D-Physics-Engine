/**
 * Constructs a generic (polygonic) shape at the given position, rotation, with the given mass, and fill/stroke colors
 * @param position n-dimensional position vector
 * @param rotation (n-1)-dimensional rotation vector
 * @param massOf mass of shape
 * @param fillColor 3D vector representing the fill color of the shape 
 * @param strokeColor 3D vector representing the stroke color of the shape (applicable only in 2D drawing)
 */
Shape::Shape(Vector &position, Vector &rotation, double massOf, Color &fillColor, Color &strokeColor, Vector &velocity, double elasticity) : 
    com(position), rot(rotation), fillColor3f(fillColor), strokeColor3f(strokeColor), vel(velocity), elasticity(elasticity) {
    mass = massOf;
    invMass = 1/mass;

    int s = com.getSize();
    if (s == 2) {
        sumForces = Vector(2, 0., 0.);
        sumTorque = Vector(1, 0.);
    } else if (s == 3) {
        sumForces = Vector(3, 0., 0., 0.);
        sumTorque = Vector(3, 0, 0, 0);
    }
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
 * @param dT happy compiler happy life
 */
void Shape::update(double dT) {}

/**
 * Naive update for every shape (apply forces, don't check collisions)
 * @param dT change in time
 */
void Shape::naiveUpdate(double dT) {
    // apply gravity
    int s = com.getSize();
    if (s == 2) {
        addF(Vector(2, 0, mass*G));
    } else if (s == 3) {
        addF(Vector(3, 0, mass*G, 0));
    }

    // integrate acceleration over time to get velocity
    vel.mAdd(sumForces.ntimes(invMass*dT));
    // dampen
    vel.mMultScalar(DAMPING);
    // resolve constraints

    // integrate velocity over time to get position
    com.mAdd(vel.ntimes(dT));
    
    // integrate angular acceleration and velocity to update rotation vector
    // hardcoded for 2D
    //angvel.mAdd(sumTorque.ntimes(invMoI.at(0).getAt(0)*dT));
    // dampen
    angvel.mMultScalar(DAMPING);
    // integrate for angular position
    // look into quaternions to update orientation
    rot.mAdd(angvel.ntimes(dT));
    // clear temporary variables

}

/**
 * Smart update collisions after naive update already called
 * @param dT change in time
 */
void Shape::smartUpdate(double dT, vector<Shape*>* shapes) {
    // check for collision with floor
    Collision floor = collideWithFloor();
    if (floor.collide) {
        com.mAdd(floor.dir.ntimes(floor.pen*2));
        vel.vectorContents.at(1) = vel.getAt(1)*-1;
        //cout << "\n" << vel.vectorContents.at(1);
    }

    if (vel.mag() < 0.01) {
        //vel.setAs(Vector(2, 0, 0));
    }

    naiveUpdate(dT);
    
    // check for collisions
    /*for (int i = 0; i < shapes->size(); i ++) {
        if (shapes->at(i) != this) {
            cout << "\n1";
            Collision obj = collideWith(*shapes->at(i));

            //Collision obj = Collisions::collide(((SCircle)(*this)), ((SCircle)(*shapes->at(i))));

            if (obj.collide) {
                Vector vab = vel.nminus((*shapes->at(i)).vel);
                double vn = Vector::dot(vab, obj.dir);
                
                double epsilon = (elasticity + (*shapes->at(i)).elasticity)/2;

                double impulse = -(1 + epsilon) * vn / (Vector::dot(obj.dir, obj.dir) * (invMass + (*shapes->at(i)).invMass));

                vel.mAdd(obj.dir.ntimes(impulse * invMass));
                (*shapes->at(i)).vel.mAdd(obj.dir.ntimes(impulse * (*shapes->at(i)).invMass));
            }
        }
    }*/

    // update position/angle to avoid clipping


    // apply force updates from collisions

    
    // integrate acceleration and velocity to update position vector


    // integrate angular accleration and velocity to update rotation vector


    // clear temporary variables
    sumForces = Vector(2, 0, 0);
}

/** 
 * Update object given collision object
 */
void Shape::updateCollision(Collision collision, Shape *shape) {
    Vector vab = vel.nminus(shape->vel);
    double vn = Vector::dot(vab, collision.dir);
                
    double epsilon = (elasticity + shape->elasticity)/2;
    
    double impulse = -(1 + epsilon) * vn / (Vector::dot(collision.dir, collision.dir) * (invMass + shape->invMass));

    //cout << "\nImpulse: " << impulse;
    //cout << "\nCurrent Velocity: " << vel.getAt(0) << " " << vel.getAt(1);
    vel.mAdd(collision.dir.ntimes(impulse * invMass));
    //cout << "\nSubsequent Velocity: " << vel.getAt(0) << " " << vel.getAt(1) << "\n";
    shape->vel.mSubtract(collision.dir.ntimes(impulse * shape->invMass));

    com.mAdd(collision.dir.ntimes(collision.pen*2));
    shape->com.mSubtract(collision.dir.ntimes(collision.pen*2));
    com.mAdd(vel.ntimes(0.001));
    shape->com.mAdd(shape->vel.ntimes(0.001));

}

/**
 * Empty function to be overrided by subclasses of Shape
 * @param shape a parameter to make the compiler happy
 * @return nothing
 */
Collision Shape::collideWith(Shape &shape) { }

Collision Shape::collideWith(Circle &shape) { }

Collision Shape::collideWith(Capsule &shape) { }

Collision Shape::collideWith(Rectangle &shape) { }

/**
 * Empty function to be overrided by subclasses of Shape
 * @return nothing
 */
Collision Shape::collideWithFloor() { }

/**
 * Add force to shape at center of mass
 * @param force a vector representing the magnitude and direction of the force applied to the object
 */
void Shape::addF(Vector force) {
    // affect linear acceleration/velocity (not position)
    sumForces.mAdd(force);
}

/**
 * Add force to shape at a given point in the shape (doesn't have to be in the shape, as calculated by the engine, but is generally more realistic if it is)
 * @param force a vector representing the magnitude and direction of the force applied to the object
 * @param pos a vector representing the position the vector is applied to (not relative to center of mass)
 */
void Shape::addFD(Vector force, Vector pos) {
    // construct force applied to center of mass, and apply it


    // affect angular acceleration/velocity (not angle)

}