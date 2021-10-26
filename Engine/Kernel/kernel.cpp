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
    clock_t t1;
    t1 = clock();

    // Define shapes
    vector<Rectangle> shapes;

    shapes.push_back(Rectangle(
        Vector(2,0,0.5),          //position (2,x,y)
        Vector(1,0),            //rotation (1,theta)
        5,                      //mass (kg)
        Color(255., 0., 0.),    //fillcolor
        Color(255., 0., 0.),    //strokecolor
        Vector(2,0.5,0.25)      //dimensions (2,w,h)
    ));
    
    // Main loop
    bool isRunning = true;
    while (isRunning) {
        // iFrame increment
        iFrame += 1;

        // Update
        update(iFrame, t1);

        // Draw
        render(window, iFrame, shapes);
    }

    // Free resources
    cleanUp(window, glContext);
}

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

void Kernel::update(int iFrame, clock_t iClock) {
    // User Updates:
    double theta = (double)iFrame/10000;
    
    clock_t t2;
    t2 = clock();
    float diff = ((float)t2-(float)iClock) / CLOCKS_PER_SEC;
    
    cout << "\rFrame: " + patch::to_string(iFrame) + "\tTime Passed (sec): " + patch::to_string(diff);
}

void Kernel::render(SDL_Window* window, int iFrame, vector<Rectangle> &shapes) {
    double theta = (double)iFrame/10000;
    
    // Setup gl environment
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // draw shapes
    for (Rectangle shape : shapes) {
        shape.draw2D();
    }

    
    // flush gl context to screen
    glFlush();

    SDL_GL_SwapWindow(window);
}

void Kernel::cleanUp(SDL_Window* window, SDL_GLContext &glContext) {
    // Clean up resources
   SDL_GL_DeleteContext(glContext);
   SDL_DestroyWindow(window); 
}