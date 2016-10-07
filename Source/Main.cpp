#include <cstdlib>

#include "Application.h"
#include "Window.h"

int main()
{
    srand ( time ( nullptr ) );
    Window::create();

    Application app;
    app.runLoop();
    return EXIT_SUCCESS;
}













