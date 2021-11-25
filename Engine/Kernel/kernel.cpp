/**
 * Initialize and run the lifecycle of the open gl context
 * @return an int indicating the exit status of the program
 */
int Kernel::start() {
    // Check SDL configuration
    initSDL();

    // Create window instance
    SDL_Window* window = createWindow("Test", 600, 600);

    // Generate opengl context in window
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // Graphics manager
    Graphics* graphicsManager;
    graphicsManager = new Graphics(window);

    // Frame count
    int iFrame = 0;
    double iTime = 0.0;
    double dT = 0.0;
    clock_t t1;
    t1 = clock();
    
    cout << "Setup Complete" << "\n";

    // Define shapes
    vector<Shape*> shapes;
    shapes.reserve(3);

    // Define constraints
    vector<Constraint*> constraints;
    constraints.reserve(3);
    
    int iterator = 0;
    // straight line of 3 circles (increasing velocities)
    /*while (iterator < 0) {
        Vector pos(2,-0.5+iterator*0.4,0);          //position (2,x,y)
        Vector rot(1,0.1);            //rotation (1,theta)
        double mass = 1;            //mass (kg)
        Color fill(0.,0.3*iterator,1.);       //fillcolor
        Color stroke(0.,0.5,1.);     //strokecolor
        Vector dim(2,0.25,0.25);    //dimensions (2,w,h)
        Vector velocity(2,0,iterator*2);
        double halfLine = 0.1;
        double elasticity = 1;
        //vector<Vector> edge;
        //vector<Vector> vert;

        //Rectangle* rect = new SRectangle(pos, rot, mass, fill, stroke, velocity, dim);
        Shape* circle = new SCircle(pos, rot, mass, fill, stroke, velocity, elasticity, 0.1);
        //Capsule* capsule = new SCapsule(pos, rot, mass, fill, stroke, velocity, halfLine, 0.1);

        shapes.push_back(circle);
        
        iterator += 1;
    }*/
    // triangle
    /*while (iterator < 3) {
        //Vector pos(2,-0.5+iterator*0.4,0);          //position (2,x,y)
        Vector pos;
        if (iterator == 0) {
            pos.setAs(Vector(2, -0.2, -0.2));
        } else if (iterator == 1) {
            pos.setAs(Vector(2, 0.2, -0.2));
        } else {
            pos.setAs(Vector(2, 0, 0.2));
        }
        Vector rot(1,0);            //rotation (1,theta)
        double mass = 0.001;            //mass (kg)
        Color fill(0.,0.3*iterator,1.);       //fillcolor
        Color stroke(0.,0.5,1.);     //strokecolor
        Vector dim(2,0.25,0.25);    //dimensions (2,w,h)
        Vector velocity(2,0,0);
        double halfLine = 0.1;
        double elasticity = 1;
        //vector<Vector> edge;
        //vector<Vector> vert;

        //Rectangle* rect = new SRectangle(pos, rot, mass, fill, stroke, velocity, dim);
        Shape* circle = new SCircle(pos, rot, mass, fill, stroke, velocity, elasticity, 0.1);
        //Capsule* capsule = new SCapsule(pos, rot, mass, fill, stroke, velocity, halfLine, 0.1);

        shapes.push_back(circle);
        
        iterator += 1;
    }*/
    // rectangle
    /*while (iterator < 4) {
        //Vector pos(2,-0.5+iterator*0.4,0);          //position (2,x,y)
        Vector pos;
        if (iterator == 0) {
            pos.setAs(Vector(2, -0.2, -0.2));
        } else if (iterator == 1) {
            pos.setAs(Vector(2, 0.2, -0.2));
        } else if (iterator == 2) {
            pos.setAs(Vector(2, 0.2, 0.2));
        } else {
            pos.setAs(Vector(2, -0.2, 0.2));
        }
        Vector rot(1,0);            //rotation (1,theta)
        double mass = 0.001;            //mass (kg)
        Color fill(0.,0.3*iterator,1.);       //fillcolor
        Color stroke(0.,0.5,1.);     //strokecolor
        Vector dim(2,0.25,0.25);    //dimensions (2,w,h)
        Vector velocity(2,0,0);
        double halfLine = 0.1;
        double elasticity = 1;
        //vector<Vector> edge;
        //vector<Vector> vert;

        //Rectangle* rect = new SRectangle(pos, rot, mass, fill, stroke, velocity, dim);
        Shape* circle = new SCircle(pos, rot, mass, fill, stroke, velocity, elasticity, 0.001);
        //Capsule* capsule = new SCapsule(pos, rot, mass, fill, stroke, velocity, halfLine, 0.1);

        shapes.push_back(circle);
        
        iterator += 1;
    }*/
    // basic circle
    int n = 3;
    while (iterator < n) {
        //Vector pos(2,-0.5+iterator*0.4,0);          //position (2,x,y)
        Vector pos(2, 0.5*cos(2*PI/n*iterator), 0.5*sin(2*PI/n*iterator));
        Vector rot(1,0);            //rotation (1,theta)
        double mass = 0.001;            //mass (kg)
        Color fill(0.,0.3*iterator,1.);       //fillcolor
        Color stroke(0.,0.5,1.);     //strokecolor
        Vector dim(2,0.25,0.25);    //dimensions (2,w,h)
        Vector velocity(2,0,0);
        double halfLine = 0.1;
        double elasticity = 1;
        //vector<Vector> edge;
        //vector<Vector> vert;

        //Rectangle* rect = new SRectangle(pos, rot, mass, fill, stroke, velocity, dim);
        Shape* circle = new SCircle(pos, rot, mass, fill, stroke, velocity, elasticity, 0.001);
        //Capsule* capsule = new SCapsule(pos, rot, mass, fill, stroke, velocity, halfLine, 0.1);

        shapes.push_back(circle);
        
        iterator += 1;
    }

    //constraints.push_back(new DistanceConstraint(*shapes.at(0), *shapes.at(1), Vector(2, 0, 0), Vector(2, 0, 0)));
    //constraints.push_back(new DistanceConstraint(*shapes.at(1), *shapes.at(2), Vector(2, 0, 0), Vector(2, 0, 0)));
    //constraints.push_back(new SpringConstraint(*shapes.at(0), *shapes.at(1), 0.5, 0.9999));
    //constraints.push_back(new SpringConstraint(*shapes.at(0), *shapes.at(2), 0.5, 0.9999));
    //constraints.push_back(new SpringConstraint(*shapes.at(0), *shapes.at(3), 0.5, 0.9999));
    //constraints.push_back(new SpringConstraint(*shapes.at(1), *shapes.at(2), 0.5, 0.9999));
    //constraints.push_back(new SpringConstraint(*shapes.at(1), *shapes.at(3), 0.5, 0.9999));
    //constraints.push_back(new SpringConstraint(*shapes.at(2), *shapes.at(3), 0.5, 0.9999));
    for (int i = 0; i < shapes.size(); i ++) {
        for (int j = i+1; j < shapes.size(); j++) {
            constraints.push_back(new SpringConstraint(*shapes.at(i), *shapes.at(j), 0.7, 0.9995));
        }
    }


    // Main loop
    bool isRunning = true;
    while (isRunning) {
        // iFrame increment
        iFrame += 1;
        
        clock_t t2;
        t2 = clock();
        dT = (double)(t2-t1) / CLOCKS_PER_SEC - iTime;
        if (dT < 0.001) { dT = 0.001; }
        iTime = (double)(t2-t1) / CLOCKS_PER_SEC;

        // Setup gl environment
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Background color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        
        // Update
        update(iFrame, iTime, dT, &shapes, &constraints);

        // Draw
        render(window, iFrame, iTime, &shapes);

        //cin.ignore();
    }

    // Free resources
    cleanUp(window, glContext);
}

/**
 * Initialize SDL window and define OpenGL version (4.2)
 * @return int representing the exit state of the function
 */
int Kernel::initSDL() {
    if (SDL_Init(SDL_INIT_NOPARACHUTE) && SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return -1;
    } else {
        //Specify OpenGL Version (4.2)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_Log("SDL Initialized");
    }
}

/**
 * Creates a window with the defined specifications
 * @param windowTitle title of the window
 * @param width width of the window in pixels (px)
 * @param height height of the window in pixels (px)
 * @return a pointer to an SDL_Window object with the assigned specifications, and a centered window position
 */
SDL_Window* Kernel::createWindow(const char* windowTitle, int width, int height) {
    // Create instance
    SDL_Window* window = SDL_CreateWindow(
        windowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    //Check that the window was succesfully created
    if(window == NULL)
    {
        //Print error, if null
        SDL_Log("Could not create window: %s\n", SDL_GetError());
    }
    else
        SDL_Log("Window Successful Generated");

    return window;
}

/**
 * Update the windowframe with relevant variables for the OpenGL environment, as well as apply updates to the objects within the frame
 * @param iFrame the number frame that the program is rendering
 * @param iTime the time since the program has begun running in seconds
 * @param shapes the shapes that the program is going to render and simulate
 */
void Kernel::update(int iFrame, double iTime, double dT, vector<Shape*>* shapes, vector<Constraint*>* constraints) {
    // User Updates:
    double theta = (double)iFrame/10000;
    
    cout << "\rFrame: " << iFrame << "\tTime Passed (sec): " << iTime << "\tdT: " << std::fixed << std::setprecision(5) << dT << "\tFPS: " << std::fixed << std::setprecision(5) << 1 / dT << "                 ";

    for (int i = 0; i < shapes->size(); i ++) {
        for (int j = i+1; j < shapes->size(); j ++) {
            Collision obj = shapes->at(i)->collideWith(*shapes->at(j));

            if (obj.collide) {
                shapes->at(i)->updateCollision(obj, shapes->at(j));
            }
        }
    }

    for (int i = 0; i < constraints->size(); i ++) {
        //cout << "\nConstraint Address: " << constraints->at(i);// << " Shape A Address: " << constraints->at(i)->A << " Shape B Address: " << constraints->at(i)->B;
        constraints->at(i)->update(0.001);//dT);
    }

    for (int i = 0; i < shapes->size(); i ++) {
        //shapes->at(i)->update(dT);
        
        
        shapes->at(i)->smartUpdate(0.001, shapes);//dT);


    }
}

/**
 * Render the window and shapes within the window
 * @param window the window to draw upon
 * @param iFrame the number frame that the program is rendering
 * @param iTime the itme since the program has begun running in seconds
 * @param shapes the shapes that the program is going to render
 */
void Kernel::render(SDL_Window* window, int iFrame, double iTime, vector<Shape*>* shapes) {
    double theta = (double)iFrame/10000;
    glBegin(GL_POLYGON);
        
    // draw shapes
    for (int i = 0; i < shapes->size(); i ++) {
        //shapes->at(i)->draw2D();
            glColor3f(0, 0, 1); glVertex3f(shapes->at(i)->com.getAt(0), shapes->at(i)->com.getAt(1), 0);
    }    
    glEnd();
    
    
    // flush gl context to screen
    glFlush();

    SDL_GL_SwapWindow(window);
}

/**
 * Cleans up gl context and deletes the SDL window pane
 * @param window the SDL window to delete
 * @param glContext the open gl context to delete
 */
void Kernel::cleanUp(SDL_Window* window, SDL_GLContext &glContext) {
    // Clean up resources
   SDL_GL_DeleteContext(glContext);
   SDL_DestroyWindow(window); 
}