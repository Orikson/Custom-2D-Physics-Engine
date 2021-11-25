/**
 * Constructs a distance constraint between two shapes
 * @param A first object between which there exists a distance constraint
 * @param B second object between which there exists a distance constraint
 * @param K spring constant
 * @param C velocity dampening factor
 */
SpringConstraint::SpringConstraint(Shape &A, Shape &B, double K, double C) : Constraint(A, B), k(K), c(C) {
    setup();
}

/**
 * Setup distance constraint
 */
void SpringConstraint::setup() {
    d = (A->com.nminus(B->com)).mag();
}

/**
 * Default constructor for a distance constraint
 */
SpringConstraint::SpringConstraint() {

}

/**
 * Update velocities of constrained shapes
 */
void SpringConstraint::update(double dT) {
    Vector x = A->com.nminus(B->com);
    double D = x.mag();
    Vector xn = Vector::multScalar(x, 1/D);
    D -= d;

    Vector res = xn.ntimes(-k*D);

    double mass = A->mass + B->mass;
    double invMass = 1/mass;

    A->vel.setAs(res.nadd(A->vel.ntimes(c)));
    B->vel.setAs((res.ntimes(-1).nadd(B->vel.ntimes(c))));

    glBegin(GL_LINES);
        glColor3f(0, 0, 1); glVertex3f(A->com.getAt(0), A->com.getAt(1), 0);
        glColor3f(0, 0, 1); glVertex3f(B->com.getAt(0), B->com.getAt(1), 0);
    glEnd();
    
} 