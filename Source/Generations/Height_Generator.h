#ifndef HEIGHT_GENERATOR_H
#define HEIGHT_GENERATOR_H


namespace Height_Generator
{
    void setUp( double amplitude,
                double roughness    = 0.3,
                int ocataves        = 3,
                int seed            = -1 );

    int getHeight ( double x, double z, double gridX, double gridZ );
}

#endif // HEIGHT_GENERATOR_H
