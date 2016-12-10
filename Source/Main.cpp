#include "Application.h"
#include "Util/Display.h"

#include "Util/Noise_Generator.h"

#include<iostream>

int main()
{/*
    Noise::Generator g;
    g.setSeed(354443252);
    g.setNoiseFunction(Noise::Data(6, 250, 0.5, 150, 0));

*/
    Display::create("MattCraft");

    Application app;
/*
    int size = 150;

    double min = 1;
    double max = -1;

    for (int x = 0; x < size ; x++)
    {
        for (int z = 0; z < size ; z++)
        {
            int n = g.getValue(x, z, x, z);
            if (n < min) min = n;
            if (n > max) max = n;
        }
    }

    std::cout << min << std::endl;
    std::cout << max << std::endl;

*/
    app.runMainLoop();

    return EXIT_SUCCESS;
}











