#ifndef _KERNEL_H
#define _KERNEL_H

#include "../../common.h"

class Kernel {
    public:
        int start();
    private:
        static bool isRunning;

        int initSDL();
        SDL_Window* createWindow(const char* windowTitle, int width, int height);
        void update(int iFrame, double iTime, double dT, vector<Shape*>* shapes, vector<Constraint*>* constraints);
        void render(SDL_Window* window, int iFrame, double iTime, vector<Shape*>* shapes);
        void cleanUp(SDL_Window* window, SDL_GLContext &glContext);
};

bool Kernel::isRunning = true;

#include "kernel.cpp"

#endif