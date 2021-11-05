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
    
    int iterator = 0;
    while (iterator < 1) {
        Vector pos(2,0,0);//-0.5+iterator,0.5);    //position (2,x,y)
        Vector rot(1,0);                    //rotation (1,theta)
        double mass = 5;                    //mass (kg)
        Color fill(1.,0.,0.);               //fillcolor
        Color stroke(1.,0.,0.);             //strokecolor
        Vector dim(2,0.25,0.25);            //dimensions (2,w,h)
        Vector velocity(2,0,(iterator-0.5)*2 / 1000);
        Vector accel(2,0,-.000005);
        Vector jerk(2,0,0);
        double halfLine = 0.1;
        //vector<Vector> edge;
        //vector<Vector> vert;

        //Rectangle* rect = new Rectangle(pos, rot, mass, fill, stroke, velocity, accel, jerk, dim);
        //Circle* circle = new Circle(pos, rot, mass, fill, stroke, velocity, accel, jerk, 0.25);
        Capsule* capsule = new SCapsule(pos, rot, mass, fill, stroke, velocity, accel, jerk, halfLine, 0.1);

        shapes.push_back(capsule);
        
        iterator += 1;
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


        // Update
        update(iFrame, iTime, dT, &shapes);

        // Draw
        render(window, iFrame, iTime, &shapes);
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
void Kernel::update(int iFrame, double iTime, double dT, vector<Shape*>* shapes) {
    // User Updates:
    double theta = (double)iFrame/10000;
    
    cout << "\rFrame: " << iFrame << "\tTime Passed (sec): " << iTime << "\tdT: " << std::fixed << std::setprecision(5) << dT << "\tFPS: " << std::fixed << std::setprecision(5) << 1 / dT << "                 ";

    for (int i = 0; i < shapes->size(); i ++) {
        shapes->at(i)->update(dT);
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
    
    // Setup gl environment
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // draw shapes
    for (int i = 0; i < shapes->size(); i ++) {
        shapes->at(i)->draw2D();
    }
    
    
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