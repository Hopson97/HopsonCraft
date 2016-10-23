#include "Display.h"
#include "Application.h"
#include "OpenGL/GLEW/glew.h"
#include <iostream>

#include <cstdlib>

int main ()
{
    Display::create("GL");

    Application app;
    app.runMainLoop();

    return EXIT_SUCCESS;
}
