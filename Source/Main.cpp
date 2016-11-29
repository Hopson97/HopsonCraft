#include "Application.h"
#include "Util/Display.h"

int main()
{
    Display::create("MattCraft");

    Application app;
    app.runMainLoop();

    return EXIT_SUCCESS;
}











