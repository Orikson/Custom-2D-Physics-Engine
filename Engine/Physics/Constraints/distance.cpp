/**
 * Constructs a distance constraint between two shapes
 * @param A first object between which there exists a distance constraint
 * @param B second object between which there exists a distance constraint
 * @param rA vector representing a point on shape A that is tethered
 * @param rB vector representing a point on shape B that is tethered
 */
DistanceConstraint::DistanceConstraint(Shape &A, Shape &B, Vector rA, Vector rB) : Constraint(A, B), rA(rA), rB(rB) {
    setup();
}

/**
 * Setup distance constraint
 */
void DistanceConstraint::setup() {
    Vector r1 = rA.rotate(A->rot.getAt(0));
    Vector r2 = rB.rotate(B->rot.getAt(0));

    target = (A->com.nadd(r1)).nminus(B->com.nadd(r2)).mag();
}

/**
 * Default constructor for a distance constraint
 */
DistanceConstraint::DistanceConstraint() {

}

/**
 * Update velocities of constrained shapes
 */
void DistanceConstraint::update(double dT) {
    Vector r1 = rA.rotate(A->rot.getAt(0));
    Vector r2 = rB.rotate(B->rot.getAt(0));

    Vector gOnA = A->com.nadd(r1);
    Vector gOnB = B->com.nadd(r2);

    Vector ab = gOnB.nminus(gOnA);
    Vector abn = ab.ntimes(1/ab.mag());

    Vector perp1 = Vector(2, -r1.getAt(1), r1.getAt(0));
    Vector perp2 = Vector(2, -r2.getAt(1), r2.getAt(0));

    Vector v0 = A->vel.nadd(perp1.ntimes(A->angvel.getAt(0)));
    Vector v1 = B->vel.nadd(perp2.ntimes(B->angvel.getAt(0)));
    double abnVel = Vector::dot(v0.nminus(v1), abn);

    double tempA = A->invMoI.at(0).getAt(0) * (Vector::cross2D(r1, abn));
    double tempB = B->invMoI.at(0).getAt(0) * (Vector::cross2D(r2, abn));
    Vector tempVA = Vector::cross(Vector(3, 0, 0, tempA), Vector(3, r1.getAt(0), r1.getAt(1), 0));
    Vector tempVB = Vector::cross(Vector(3, 0, 0, tempB), Vector(3, r2.getAt(0), r2.getAt(1), 0));
    double massLin = A->invMass + B->invMass;
    double massRot = Vector::dot(Vector(3, abn.getAt(0), abn.getAt(1), 0), tempVA.nadd(tempVB));
    double mass = massLin + abs(massRot);

    if (mass > 0) {
        double b = 0;

        double dist = ab.mag() - target;
        double baumgarte = 0.1;
        b = -(baumgarte / dT) * dist;

        double jn = -(abnVel + b) / mass;

        A->vel.mAdd(abn.ntimes(A->invMass*jn));
        B->vel.mSubtract(abn.ntimes(B->invMass*jn));

        A->angvel.mAddScalar(A->invMoI.at(0).getAt(0) * (Vector::cross2D(r1, abn.ntimes(jn))));
        B->angvel.mAddScalar(-1 * B->invMoI.at(0).getAt(0) * (Vector::cross2D(r2, abn.ntimes(jn))));
    }

    glBegin(GL_LINES);
        glColor3f(0, 0, 1); glVertex3f(gOnA.getAt(0), gOnA.getAt(1), 0);
        glColor3f(0, 0, 1); glVertex3f(gOnB.getAt(0), gOnB.getAt(1), 0);
    glEnd();
    
    
} 