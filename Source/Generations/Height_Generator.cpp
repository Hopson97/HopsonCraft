#include "Height_Generator.h"

#include <iostream>
#include <cmath>


#include "Utilities/Random.h"
#include "Chunk/Chunk.h"

Height_Generator :: Height_Generator()
{
    seed = Random::integer ( 1, 32000 ) * Random::integer ( 1, 32000 ); //Random seems to go from 0->32000, so any higher aint possible

    std::cout << seed << std::endl;
    srand ( seed );
}








int Height_Generator :: generateHeight ( int x, int z )
{
    return getInterpolatedNoise( x, z ) * (Chunk::HEIGHT) + 60;
}

float Height_Generator :: getNoise ( int x, int z )
{
    return Random::decimalD( 1.0f, 2.0f, 1 );
}

float Height_Generator :: getSmoothNoise ( int x, int z )
{
    float cornerValues = (  getNoise( x - 1, z - 1  ) +
                            getNoise( x + 1, z - 1  ) +
                            getNoise( x - 1, z + 1  ) +
                            getNoise( x + 1, z + 1  )   )   / 16.0f;

    float sideValues =  (  getNoise( x - 1, z       ) +
                           getNoise( x + 1, z       ) +
                           getNoise( x,     z + 1   ) +
                           getNoise( x,     z + 1   )   ) / 8.0f;

    float middle = getNoise( x, z ) / 4.0f;

    return (middle * sideValues * cornerValues) / 3;
}

float Height_Generator::getInterpolatedNoise(float x, float z)
{
    int intX = x;
    int intZ = z;

    float fracX = x - intX;
    float fracZ = z - intZ;

    float v1 = getSmoothNoise( intX,        intZ );
    float v2 = getSmoothNoise( intX + 1,    intZ );
    float v3 = getSmoothNoise( intX,        intZ + 1 );
    float v4 = getSmoothNoise( intX + 1,    intZ + 1 );

    float i1 = interpolate( v1, v2, fracX );
    float i2 = interpolate( v3, v4, fracX );

    return interpolate( i1, i2, fracZ );
}


float Height_Generator :: interpolate ( float a, float b, float blend )
{
    double angle = blend * 3.14159;
    float f = (float)(1.0f - std::cos( angle ) ) * 0.5f;
    return  a * ( 1.0f - f ) + b * f;
}

