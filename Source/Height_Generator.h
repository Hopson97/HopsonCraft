#ifndef HEIGHT_GENERATOR_H
#define HEIGHT_GENERATOR_H


class Height_Generator
{
    public:
        Height_Generator();

        int getPerlin ( int x, int z );

        int generateHeight ( int x, int z );

    private:
        float getNoise          ( int x, int z );

        float getSmoothNoise    ( int x, int z);

        float interpolate       ( float a, float b, float blend );

        float getInterpolatedNoise ( float x, float z );

        int seed;

        int m_octaves           = 3.0f;     //Octaves are just how many times over the noise functions are used.
        float m_roughness       = 0.3f;     //On the tin.
        float m_frequency       = 4.0f;    //Determines the smoothness, higher = smoother
};

#endif // HEIGHT_GENERATOR_H
