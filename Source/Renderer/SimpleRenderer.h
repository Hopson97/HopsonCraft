#ifndef SIMPLE_RENDER_H_INCLUDED
#define SIMPLE_RENDER_H_INCLUDED

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/SimpleShader.h"
#include "../Model.h"

class Cube;
struct Camera;

class SimpleRenderer
{
    public:
        SimpleRenderer();

        void draw (const Cube& cube);
        void update(const Camera& camera);

    private:
        void prepare(const Cube& cube);

    private:
        std::vector<const Cube*> m_cubes;

        SimpleShader m_shader;

        Model m_cubeModel;
};

#endif // SIMPLE_H_INCLUDED
