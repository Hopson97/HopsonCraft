#include "Height_Generator.h"

#include <iostream>
#include <cmath>


#include "Random.h"
#include "Chunk/Chunk.h"

namespace Height_Generator
{
    //http://webstaff.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
    int grad3[12][3] = {{1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0},
                    {1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1},
                    {0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1}};

    int p[] = {151,160,137,91,90,15,
        131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
        190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
        88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
        77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
        102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
        135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
        5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
        223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
        129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
        251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
        49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
        138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
    };

     int perm[512];

     void makePerm ()
     {
          for(int i=0; i<512; i++) perm[i]=p[i & 255];
     }


  int fastfloor(double x) {
    return x>0 ? (int)x : (int)x-1;
  }
  double dot(int g[], double x, double y) {
    return g[0]*x + g[1]*y; }
  double dot(int g[], double x, double y, double z) {
    return g[0]*x + g[1]*y + g[2]*z; }
  double dot(int g[], double x, double y, double z, double w) {
    return g[0]*x + g[1]*y + g[2]*z + g[3]*w; }



    double simplex ( int x, int y, int gridX, int gridY )
    {
        static bool permMade = false;
        if ( permMade )
        {
            permMade = true;
            makePerm();
        }
        double xin = x + gridX;
        double yin = y + gridY;
        double n0, n1, n2;
    // Noise contributions from the three corners
        // Skew the input space to determine which simplex cell we're in
        double F2 = 0.5*(sqrt(3.0)-1.0);
        double s = (xin+yin)*F2;
    // Hairy factor for 2D
        int i = fastfloor(xin+s);
        int j = fastfloor(yin+s);
        double G2 = (3.0-sqrt(3.0))/6.0;
        double t = (i+j)*G2;
        double X0 = i-t;
    // Unskew the cell origin back to (x,y) space
        double Y0 = j-t;
        double x0 = xin-X0;
    // The x,y distances from the cell origin
        double y0 = yin-Y0;
        // For the 2D case, the simplex shape is an equilateral triangle.
        // Determine which simplex we are in.
        int i1, j1;
    // Offsets for second (middle) corner of simplex in (i,j) coords
        if(x0>y0) {i1=1; j1=0;}
    // lower triangle, XY order: (0,0)->(1,0)->(1,1)
        else {i1=0; j1=1;}
    // upper triangle, YX order: (0,0)->(0,1)->(1,1)
        // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
        // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
        // c = (3-sqrt(3))/6
        double x1 = x0 - i1 + G2;
    // Offsets for middle corner in (x,y) unskewed coords
        double y1 = y0 - j1 + G2;
        double x2 = x0 - 1.0 + 2.0 * G2;
    // Offsets for last corner in (x,y) unskewed coords
        double y2 = y0 - 1.0 + 2.0 * G2;
        // Work out the hashed gradient indices of the three simplex corners
        int ii = i & 255;
        int jj = j & 255;
        int gi0 = perm[ii+perm[jj]] % 12;
        int gi1 = perm[ii+i1+perm[jj+j1]] % 12;
        int gi2 = perm[ii+1+perm[jj+1]] % 12;
        // Calculate the contribution from the three corners
        double t0 = 0.5 - x0*x0-y0*y0;
        if(t0<0) n0 = 0.0;
        else {
        t0 *= t0;
        n0 = t0 * t0 * dot(grad3[gi0], x0, y0);
    // (x,y) of grad3 used for 2D gradient
        }
        double t1 = 0.5 - x1*x1-y1*y1;
        if(t1<0) n1 = 0.0;
        else {
        t1 *= t1;
        n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
        }
        double t2 = 0.5 - x2*x2-y2*y2;
        if(t2<0) n2 = 0.0;
        else {
        t2 *= t2;
        n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
        }
        // Add contributions from each corner to get the final noise value.
        // The result is scaled to return values in the interval [-1,1].
        double noise = 70.0 * (n0 + n1 + n2);

        std::cout << ((noise + 1) / 20) * 64 << std::endl;

        return ((noise + 1) / 20) * Chunk::WATER_LEVEL + Chunk::WATER_LEVEL;
    }










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
        gen_roughness = 0.4;//roughness;

        if ( seed == -1 ) {
            setRandSeed();
        } else {
            gen_seed = seed;
        }

        std::cout <<    "Amplitude: " << gen_amplitude  << "\n"
                  <<    "Roughness: " << gen_roughness  << "\n"
                  <<    "Octaves:   " << gen_ocataves   << "\n"
                  <<    "Seed:      " << gen_seed       << "\n" << "\n";
    }

    int getHeight ( double x, double z, double gridX, double gridZ )
    {
        if ( gen_seed == -1 )
        {
            setRandSeed();
        }

        double xOffset = gridX * ( Chunk::WIDTH );
        double zOffset = gridZ * ( Chunk::WIDTH );

        double total = 0;
        double value = std::pow ( 2, gen_ocataves) - 1.0;

        for ( int i = 0 ; i < gen_ocataves ; i++ )
        {
            double frequency = std::pow( 2, i ) / value;
            double amps      = std::pow ( gen_roughness, i ) * gen_amplitude;

            total += getInterpolatedNoise(  ( x + xOffset ) * frequency,
                                            ( z + zOffset ) * frequency ) * amps;
        }
        int ret = total + 20;
        return ret < Chunk::HEIGHT - 3 ? ret : Chunk::HEIGHT - 3;
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
