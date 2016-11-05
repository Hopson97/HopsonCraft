#include "Height_Generator.h"

#include <iostream>
#include <cmath>


#include "Random.h"
#include "Chunk/Chunk.h"

namespace Height_Generator
{
    /* Decent Seeds:
     *   112175343 , with default args and chunk height / 2
     *
     */
    namespace
    {
        int gen_seed            = -1;

        double gen_amplitude    = 230;
        double gen_roughness    = 0.5;
        int    gen_ocataves     = 5;


        double getNoise             ( double x, double z );
        double getSmoothNoise       ( double x, double z );
        double getInterpolatedNoise ( double x, double z );
        double interpolate          ( double a, double b, double blend );

        void setRandSeed ()
        {
            gen_seed = Random::integer( 0, 32000 ) * Random::integer( 0, 32000 );
            srand( gen_seed );
        }
    }

    void setUp( double amplitude,
                double roughness,
                int ocataves,
                int seed        )
    {
        gen_amplitude = 240;//amplitude;
        gen_ocataves  = 4;//ocataves;
        gen_roughness = 0.5;//roughness;

        if ( seed == -1 )
        {
            setRandSeed();
        } else
        {
            gen_seed = seed;
        }

        std::cout <<    "Amplitude: " << gen_amplitude  << "\n"
                  <<    "Roughness: " << gen_roughness  << "\n"
                  <<    "Octaves:   " << gen_ocataves   << "\n"
                  <<    "Seed:      " << gen_seed       << "\n" << "\n";
    }

    int getHeight ( double x, double z, double gridX, double gridZ )
    {
        //return 140;
        if ( gen_seed == -1 )
        {
            setRandSeed();
        }

        double xOffset = gridX * ( Chunk::SIZE - 1 );
        double zOffset = gridZ * ( Chunk::SIZE - 1 );

        double total = 0;
        double value = std::pow ( 2, gen_ocataves) - 1.0;

        for ( int i = 0 ; i < gen_ocataves ; i++ )
        {
            double frequency = std::pow( 2, i ) / value;
            double amps      = std::pow ( gen_roughness, i ) * gen_amplitude;

            total += getInterpolatedNoise(  ( x + xOffset ) * frequency,
                                            ( z + zOffset ) * frequency ) * amps;
        }
        return total + 10;
    }

    int getSeed()
    {
        return gen_seed;
    }

    void setOctave ( int octave )
    {
        gen_ocataves = octave;
    }

    void setRoughness ( double roughness )
    {
        gen_roughness = roughness;
    }

    void setAmplitude ( double amplitude )
    {
        gen_amplitude = amplitude;
    }


    namespace
    {
        double getNoise ( double x, double z )
        {
            srand( x * 5232 + z * 4545737 + gen_seed );
            double noise = Random::decimalD( 0, 1, 2 );
            //srand( gen_seed );
            return noise;
        }

        //Gets average noise from corners
        double getSmoothNoise   ( double x, double z )
        {
            double corners = (  ( getNoise( x - 1, z - 1 ) ) +
                                ( getNoise( x + 1, z + 1 ) ) +
                                ( getNoise( x + 1, z - 1 ) ) +
                                ( getNoise( x - 1, z + 1 ) ) )  / 32;

            double sides = (    ( getNoise( x - 1,    z ) ) +
                                ( getNoise( x + 1,    z ) ) +
                                ( getNoise( x,        z - 1 ) ) +
                                ( getNoise( x,        z + 1 ) ) ) / 16;

            double middle = getNoise( x, z ) / 8;

            return corners + sides + middle;
        }

        double interpolate ( double a, double b, double blend )
        {
            double theta = blend * 3.14159;

            double f = 1.0 - std::cos( theta ) * 0.5;

            return a * ( 1.0 - f ) + b * f;
        }

        double getInterpolatedNoise ( double x, double z )
        {
            int intX = int( x );
            int intZ = int( z );

            double fracX = x - intX;
            double fracZ = z - intZ;

            double v1 = getSmoothNoise( intX,       intZ        );
            double v2 = getSmoothNoise( intX + 1.0, intZ        );
            double v3 = getSmoothNoise( intX,       intZ + 1.0  );
            double v4 = getSmoothNoise( intX + 1.0, intZ + 1.0  );

            double i1 = interpolate( v1, v2, fracX );
            double i2 = interpolate( v3, v4, fracX );

            return interpolate( i1, i2, fracZ );
        }
    }

}
