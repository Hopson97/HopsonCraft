#ifndef WATER_RENDERER_H
#define WATER_RENDERER_H

#include <vector>
#include <SFML/System/Clock.hpp>

#include "Water_Shader.h"

class Chunk;
class Camera;

class Water_Renderer
{
    public:
        Water_Renderer();

        void addChunk       ( const Chunk& chunk );

        void render         ( const Camera& camera );

    private:
        void prepareWater   ( const Chunk& chunk );

        std::vector<const Chunk*> m_chunks;

        Shader::Water_Shader m_shader;

        sf::Clock m_timer;
};

#endif // WATER_RENDERER_H
